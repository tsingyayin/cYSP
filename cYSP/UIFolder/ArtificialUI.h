#pragma once
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "QtWordGame.h"
#include "../loadsettings.h"
#include "../global_value.h"
#include "../Aaspcommand/aaspcommand.h"
#include "../Aaspcommand/UICoreLauncher.h"
using namespace std;

class PlayerDef :public QWidget
{
	Q_OBJECT
	public:
		uFirstPage* FirstPage;
		uTitlePage* TitlePage;
		uPlayerPage* PlayerPage;
		uSoundService* PlayMusic;
		void setupUI(int X,int Y,int L,int T) {
			this->setGeometry(100, 100, X, Y);
			this->setFixedSize(this->width(), this->height());
			this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
			FirstPage = new uFirstPage(X, Y, this);
			FirstPage->setGOpacity(1);

			TitlePage = new uTitlePage(X, Y, this);

			PlayerPage = new uPlayerPage(X, Y, this);

			PlayMusic = new uSoundService();
		
			PlayerPage->raise();
			TitlePage->raise();
			FirstPage->raise();
		};
};

class PlayerWindow :public PlayerDef
{
	Q_OBJECT
	public:
		int gX, gY;
		bool StoryShow = FALSE;
		QDesktopWidget* desktop;
		PlayerWindow(int argc, char* argv[], QWidget* parent = Q_NULLPTR) {
			//初始化时确认目标大小
			if (Program_Settings("Window_DisplayMode") == "Full") {
				desktop = new QDesktopWidget();
				int current_monitor = desktop->screenNumber();
				QRect Display = desktop->screenGeometry(current_monitor);
				int X = Display.width();
				int Y = Display.height();
				gX = X; gY = Y;
			}elif (Program_Settings("Window_DisplayMode") == "Window") {
				gX = Program_Settings("Window_Geometry").section("_", 0, 0).toInt();
				gY = Program_Settings("Window_Geometry").section("_", -1, -1).toInt();
				if (gX <= 800) { gX = 800; }
				if (gY <= 600) { gY = 600; }
			}else{
				desktop = new QDesktopWidget();
				int current_monitor = desktop->screenNumber();
				QRect Display = desktop->screenGeometry(current_monitor);
				int X = Display.width();
				int Y = Display.height();
				gX = X; gY = Y;
			}
			//装载UI
			this->setupUI(gX, gY, 100, 100);
			connect(FirstPage->ChooseFileButton, SIGNAL(clicked()), this, SLOT(RUNCORE()));
			connect(FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));
		}
	public slots:
		//两个show函数的变种——以备后用
		void gshow(void) {
			this->show();	
		}
		void gshowFullScreen(void) {
			this->showFullScreen();
		}
		//核心启动函数
		void RUNCORE(void) {
			QString ChooseStory = QFileDialog::getOpenFileName(this, msg("Choose_File"), "./story", "Story File(*.spol)");
			SPAWN* Interpreter = new SPAWN(ChooseStory);
			connect(Interpreter->signalName, SIGNAL(can_hide_hello(int)), this, SLOT(hideHello(int)));

			Interpreter->start();
		}
		//主页面隐藏
		void hideHello(int num) {
			if (num == 1) {
				for (int i = 1; i < 100; i++) {
					FirstPage->setGOpacity(1 - (float)i / 100);
					FirstPage->repaint();
					Sleep(10);
				}
			}
		}
		void exitProgram(void) {
			StoryShow = FALSE;
			QApplication::instance()->quit();
		
		}
};