#pragma execution_character_set("utf-8")
#include "UIFolder/TopWindow.h"
#include "UIFolder/ArtificialUI.h"
#include "UIFolder/LoadingPage.h"
#include "global_value.h"
#include "loadsettings.h"
#include "Aaspcommand/aaspcommand.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <exception>
#include "langcontrol.h"
#include "UIFolder/WindowsWarn.h"
#include <QTest>
using namespace std;

#if DEPLOY == 1
#include <stdlib.h>
#include <Windows.h>
#include <shellapi.h>
#endif

int main(int argc, char* argv[])
{
	qRegisterMetaType<EIFL>("EIFL");
	qRegisterMetaType<Controller::Backdrop::Data>("Controller::Backdrop::Data");
	qRegisterMetaType<QList<QStringList>>("QList<QStringList>");
	qRegisterMetaType<QMediaPlayer::MediaStatus>("QMediaPlayer::MediaStatus");
#if DEPLOY == 2
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
#endif
	qsrand((unsigned)time(NULL));
	QApplication app(argc, argv);
	////将字体文件名传给addApplicationFont,得到字体的Id
	int fontId = QFontDatabase::addApplicationFont(":/IRC/InsiderSource/Fonts/SourceHanSansCN-Regular.ttf");
	////将字体Id传给applicationFontFamilies,得到一个QStringList,其中的第一个元素为新添加字体的family
	qDebug() << fontId;
	QString msyh = QFontDatabase::applicationFontFamilies(fontId).at(0);
	qDebug() << msyh;
	QFont font(msyh, 10);
	////将此字体设为QApplication的默认字体
	QApplication::setFont(font);

	//qDebug().noquote() << "The kernel is checking startup parameters. Some information may not be displayed when the program is not in Forced Debugging Mode";
	//sDebug("DebugInfo→Start path : " + QDir::currentPath());
	//cout << argv[0] << endl;
	//sDebug("DebugInfo→Program path : " + QString::fromLocal8Bit(argv[0]).section("\\", 0, -2));
	if (QString(argv[1]) != "Launcher") {
		QDir::setCurrent(QString::fromLocal8Bit(argv[0]).section("\\", 0, -2));
		setCurrentPath(QString::fromLocal8Bit(argv[0]));
	}
	else {
		setCurrentPath(QString::fromLocal8Bit(argv[0]), QString::fromLocal8Bit(argv[2]), TRUE);
		QApplication::addLibraryPath(QDir::currentPath());
		//qDebug() << QApplication::libraryPaths();
	}
	//qDebug() << QDir::currentPath();

	LoadingPage* win = new LoadingPage();
	win->show();
	int i = app.exec();
	win->deleteLater();

	if (Program_Settings("First_Start") != "False") {
		WindowsWarnSPOL_6 SPOL_6_Window;
		SPOL_6_Window.show();
		int i = app.exec();
		writesettings("First_Start", "False");
	}

	int DirectOpen = 0;
	string Usript;
	if (argv[1] != "") {
		DirectOpen = 1;
		Usript = "ui";
	}
	else {
		DirectOpen = 1;
		Usript = "window";
	}
	Usript = "window";

	bool programme_run = TRUE;
	while (programme_run) {
		if (Usript == "ui") {
			PlayerWindow UIWindow(argc, argv);
			if (Program_Settings("Window_DisplayMode") == "Full") {
				UIWindow.gshowFullScreen();
			}elif(Program_Settings("Window_DisplayMode") == "Window") {
				UIWindow.gshow();
			}
			else {
				UIWindow.gshowFullScreen();
			}
			int a = app.exec();
			Usript = "window";
			DirectOpen = 1;
		}elif(Usript == "window") {
			TopWindow* MainWindow = new TopWindow();
			MainWindow->show();
			int a = app.exec();
			delete MainWindow;

			DirectOpen = 1;
			if (a == 1) {
				Usript = "ui";
			}
			else {
				return 0;
			}
		}
	}
}