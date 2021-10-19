#pragma once
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "../core/core0_6_5_T.h"
#include "QtWordGame.h"
#include "../loadsettings.h"
#include "../global_value.h"
#include "../Aaspcommand/aaspcommand.h"
#include "../Aaspcommand/UICoreLauncher.h"
using namespace std;


class ChangeWake :public QObject
{
	Q_OBJECT
public:
	bool STOPUNLOCK = TRUE;
	ChangeWake() {};
public slots:
	void willStop(void) {
		STOPUNLOCK = FALSE;
	}
	void lastContinue(void) {
		STOPUNLOCK = TRUE;
	}
};

class TickThread :public QThread
{
	Q_OBJECT
signals:
	void timeout(void);
public:
	int gTime;
	bool Active = FALSE;
	TickThread() {		
	}
	void setInterval(int time) {
		gTime = time;
	}
	void run() {
		Active = TRUE;
		while (TRUE) {
			Sleep(gTime);
			if (!Active) { break; }
			emit timeout();
		}
		this->deleteLater();
	}
	void stop() {
		Active = FALSE;
	}
};

class PlayerDef :public QWidget
{
	Q_OBJECT
	public:
		uFirstPage* FirstPage;
		uTitlePage* TitlePage;
		uPlayerPage* PlayerPage;
		uSoundService* PlayMusic;
		ChangeWake* changeWAKE=new ChangeWake();
		ReciveUserControl* userControl = new ReciveUserControl();
		void setupUI(int X,int Y,int L,int T) {
			this->setGeometry(100, 100, X, Y);
			this->setFixedSize(this->width(), this->height());
			this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
			FirstPage = new uFirstPage(X, Y, this);
			FirstPage->setGOpacity(1);
			connect(FirstPage->ChooseFileButton, SIGNAL(clicked()), this, SLOT(RUNCORE()));
			connect(FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));

			TitlePage = new uTitlePage(X, Y, this);

			PlayerPage = new uPlayerPage(X, Y, this);
			connect(this->PlayerPage, SIGNAL(UserChooseWhich(QString)), this->userControl, SLOT(ChooseWhichBranch(QString)));
			connect(this->PlayerPage, SIGNAL(UserSpeedSet(float)), this->userControl, SLOT(SpeedNow(float)));
			connect(this->PlayerPage->LogPage, SIGNAL(EmitJumpLine(int)), this->userControl, SLOT(LineNumNow(int)));
			connect(this->PlayerPage, SIGNAL(NeedWakeUp()), this, SLOT(Wakeup()));

			PlayMusic = new uSoundService();
		
			PlayerPage->raise();
			TitlePage->raise();
			FirstPage->raise();

			connect(this, SIGNAL(stopNow()), userControl, SLOT(ExitNow()));
		};
};

class PlayerWindow :public PlayerDef
{
	Q_OBJECT
	signals:
		void stopNow(void);
	public:
		int gX, gY;
		bool StoryShow = FALSE;
		bool OneBGMIsPlaying = FALSE;
		QDesktopWidget* desktop;
		QList<uSoundService*> musicThreadList;
		SPAWN* Interpreter;
		TickThread* Ticker;
		PlayerWindow(int argc, char* argv[], QWidget* parent = Q_NULLPTR) {
			//��ʼ��ʱȷ��Ŀ���С
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
			//װ��UI

			this->setupUI(gX, gY, 100, 100);
			this->setWindowIcon(QIcon(".\\Visual\\source\\WinICO\\Story.ico"));
			this->setWindowTitle("Yayin Story Player");
			
		}
	public slots:
		//����show�����ı��֡����Ա�����
		void gshow(void) {
			this->show();	
		}
		void gshowFullScreen(void) {
			this->showFullScreen();
		}
		//������������
		void RUNCORE(void) {
			QString ChooseStory = QFileDialog::getOpenFileName(this, msg("Player_ChooseFilePage_Text_Title"), "./story", "Story File(*.spol)");
			Interpreter = new SPAWN(ChooseStory);
			Ticker = new TickThread();
			Ticker->setInterval(750);

			connect(Interpreter->signalName, SIGNAL(can_hide_hello(int)), this, SLOT(hideHello(int)));
			connect(Interpreter->signalName, SIGNAL(can_reprint_hello(int)), this, SLOT(reprintHello(int)));
			
			connect(Interpreter->signalName, SIGNAL(need_to_choose(QStringList)), this->PlayerPage, SLOT(setBranchButton(QStringList)));
			connect(this->PlayerPage, SIGNAL(UserChooseWhich(QString)), this->userControl, SLOT(ChooseWhichBranch(QString)));

			connect(Interpreter->signalName, SIGNAL(can_show_title(QStringList)), this, SLOT(showTitle(QStringList)));
			connect(Interpreter->signalName, SIGNAL(can_hide_title(void)), this, SLOT(hideTitle(void)));
			connect(Interpreter->signalName, SIGNAL(can_prepare_play(void)), this, SLOT(hideTitleLast(void)));

			connect(Interpreter->signalName, SIGNAL(can_update_bg(QStringList)), this->PlayerPage, SLOT(setCurrentBGP(QStringList)));
			connect(Interpreter->signalName, SIGNAL(update_num_bg(float, QStringList)), this->PlayerPage, SLOT(updateCurrentBGP(float, QStringList)));

			connect(Interpreter->signalName, SIGNAL(can_update_chara(QList<QStringList>, int, bool)) , this->PlayerPage, SLOT(setCurrentAvg(QList<QStringList>, int, bool)));
			connect(Interpreter->signalName, SIGNAL(update_chara_num(QStringList, QString, int, QStringList)), this->PlayerPage, SLOT(updateCurrentWords(QStringList, QString, int, QStringList)));

			connect(Interpreter->signalName, SIGNAL(can_update_freedom(QStringList, QStringList)), this->PlayerPage, SLOT(setCurrentFree(QStringList, QStringList)));
			connect(Interpreter->signalName, SIGNAL(update_num_freedom(QString)), this->PlayerPage, SLOT(updateCurrentFree(QString)));
			connect(Interpreter->signalName, SIGNAL(can_clear_freedom(int)), this->PlayerPage, SLOT(clearCurrentFree(int)));

			connect(Interpreter->signalName, SIGNAL(can_update_bgm(QString, int)), this, SLOT(playBGM(QString, int)));
			connect(Interpreter->signalName, SIGNAL(can_update_sound(QString, int)), this, SLOT(playSound(QString, int)));

			connect(Interpreter->signalName, SIGNAL(show_next()), this->PlayerPage, SLOT(showNext()));
			connect(Interpreter->signalName, SIGNAL(willstop()), this->changeWAKE, SLOT(willStop()));
			connect(Interpreter->signalName, SIGNAL(inrunning()), this->changeWAKE, SLOT(lastContinue()));

			connect(Interpreter->signalName, SIGNAL(clr_line_list()), this->PlayerPage->LogPage, SLOT(initObject()));
			connect(Interpreter->signalName, SIGNAL(save_line_list(QStringList)), this->PlayerPage->LogPage, SLOT(setLineList(QStringList)));
			connect(Interpreter->signalName, SIGNAL(set_scroll_info()), this->PlayerPage->LogPage, SLOT(setScroll()));
			connect(Interpreter->signalName, SIGNAL(now_which_line(int)), this->PlayerPage->LogPage, SLOT(UpdateLineNum(int)));

			connect(this, SIGNAL(stopNow()), this->userControl, SLOT(ExitNow()));
			connect(this->Ticker, SIGNAL(timeout()), this->PlayerPage, SLOT(repaintAutoButton()));
			
			PlayerPage->initObject();
			Ticker->start();
			Interpreter->start();
		}

		//��ҳ������
		void hideHello(int num) {
			StoryShow = TRUE;
			if (num == 1) {
				for (int i = 1; i < 100; i++) {
					FirstPage->setGOpacity(1 - (float)i / 100);
					FirstPage->repaint();
					Sleep(10);
				}
				disconnect(FirstPage->ChooseFileButton, SIGNAL(clicked()), this, SLOT(RUNCORE()));
				disconnect(FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));
			}
		}

		//��ҳ�渴��
		void reprintHello(int num) {
			StoryShow = FALSE;
			PlayerPage->clearAll();
			FirstPage->raise();
			Ticker->stop();
			if (num == 1) {
				try {
					if (OneBGMIsPlaying) {
						PlayMusic->fadeMedia();
					}
				}
				catch (...) {}
				Interpreter->wait();
				delete Interpreter;
				for (int i = 1; i < 100; i++) {
					FirstPage->setGOpacity((float)i / 100);
					FirstPage->repaint();
					Sleep(10);
				}
				connect(FirstPage->ChooseFileButton, SIGNAL(clicked()), this, SLOT(RUNCORE()));
				connect(FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));
			}
		}

		//����չʾ����-ǰ���
		void showTitle(QStringList titlesetList) {
			TitlePage->setTitleInfo(titlesetList[0], titlesetList[1], titlesetList[2], titlesetList[3]);
			TitlePage->showPage();
			TitlePage->raise();
		}

		//����չʾ����-�а��
		void hideTitle(void) {
			TitlePage->playAnimation();
		}

		//����չʾ����-����
		void hideTitleLast(void) {
			TitlePage->hidePage();
			PlayerPage->raise();
			PlayerPage->showPlayerPage();
		}

		//���ֿ�����-��Ƶ��������
		void playBGM(QString filename, int volume) {
			if (OneBGMIsPlaying) { PlayMusic->fadeMedia(); }
			PlayMusic->loadFile(".//Visual//source//BGM//" + filename + ".mp3", volume);
			PlayMusic->playMedia();
			OneBGMIsPlaying = TRUE;
		}

		//��Ч������-��Ч��������
		void playSound(QString filename, int volume) {
			musicThreadList.append(new uSoundService());
			musicThreadList[musicThreadList.length() - 1]->loadFile(".//Visual//source//Sound//" + filename + ".mp3", volume);
			musicThreadList[musicThreadList.length() - 1]->playMedia();
		}

		//��ݼ�����
		void keyPressEvent(QKeyEvent *event) {
			if (event->key() == Qt::Key_Escape) {
				if (StoryShow == FALSE) {
					exitProgram();
				}
				else {
					if (PlayerPage->searchParameter("InLogPage") == 0) {
						StoryShow = FALSE;
						Ticker->stop();
						emit stopNow();
					}else if (PlayerPage->searchParameter("InLogPage") == 1) {
						PlayerPage->showLogPage();
					}
				}
			}
			else if (event->key() == Qt::Key_Q && StoryShow) {
				if (PlayerPage->gUseLogPage == TRUE && PlayerPage->searchParameter("Inbranch") == 0) {
					PlayerPage->showLogPage();
				}	
			}
			else if (event->key() == Qt::Key_Return) {
				if (StoryShow) {
					if (PlayerPage->searchParameter("InLogPage") == 0) {
						if (PlayerPage->searchParameter("Inbranch") == 0) {
							PlayerPage->_ToNext();
						}						
					}
					else if (PlayerPage->searchParameter("InLogPage") == 1) {
						PlayerPage->LogPage->EmitLineNum();
						PlayerPage->showLogPage();
					}
				}
			}
			else if (event->key() == Qt::Key_W && StoryShow) {
				if (PlayerPage->searchParameter("InLogPage") == 0) {
					PlayerPage->_SpeedChange();
				}
			}
			else if (event->key() == Qt::Key_A && StoryShow) {
				if (PlayerPage->searchParameter("InLogPage") == 0) {
					PlayerPage->_AutoChange();
				}
			}
		}

		//���������Ѻ���
		void Wakeup(void) {
			while (TRUE) {			
				if (changeWAKE->STOPUNLOCK == FALSE) {	
					Interpreter->wake();		
					break;
				}
			}
		}

		//�����������������˳�����
		//���ǰɣ����������Ļ��ศ����ϵ��ɶ���Լ���Ե��������˳�������Ҹ㲻����
		//���������Ͷ���
		void exitProgram(void) {
			StoryShow = FALSE;
			QApplication::instance()->quit();	
		}

		void closeEvent(QCloseEvent *event) {
			if (StoryShow) { 
				Ticker->stop(); 
			}
			if (OneBGMIsPlaying) { PlayMusic->fadeMedia(); }
			
			emit stopNow();
			
		}

};