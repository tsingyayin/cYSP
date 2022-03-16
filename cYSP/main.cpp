#pragma execution_character_set("utf-8")
#include "UIFolder/TopWindow.h"
#include "UIFolder/ArtificialUI.h"
#include "UIFolder/LoadingPage.h"
#include "UIFolder/FirstPage.h"
#include "UIFolder/NewProjectPage.h"
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
#include "core/GSS.h"
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
	/*GPOLSubInterpreterForSPOL* GI = new GPOLSubInterpreterForSPOL();
	while (TRUE) {
		string input;
		cin >> input;
		qDebug()<< (GI->Interpreter(QString::fromStdString(input)));
	}*/
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

	if (i == 0) {
		//应用主功能循环
		while (TRUE) {
			if (argc == 1) {
				uProjectPage* win = new uProjectPage();
				win->show();
				i = app.exec();
				win->deleteLater();
			}
			else {
				GlobalValue::CurrentProject = QString::fromLocal8Bit(argv[1]).section("\\", -2, -2);
				i = 1;
			}
			if (i == 0) {
				if (GlobalValue::NewWhichProject == "Empty") {
					uNewProjectPage* win = new uNewProjectPage(uNewProjectPage::InitProject::Empty);
					win->show();
					i = app.exec();
					win->deleteLater();
				}
				else {
					uNewProjectPage* win = new uNewProjectPage(uNewProjectPage::InitProject::Default);
					win->show();
					i = app.exec();
					win->deleteLater();
				}
			}
			if (i == 1) {
				while (i == 1) {
					TopWindow* MainWindow = new TopWindow();
					MainWindow->show();
					i = app.exec();
					MainWindow->deleteLater();
					if (i == 1) {
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
					}
				}
			}
			if (i == 233) {
				break;
			}
		}
	}
}