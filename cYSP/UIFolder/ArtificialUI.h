#pragma once
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include "../core/core_T.h"
#include "QtWordGame.h"
#include "../loadsettings.h"
#include "../global_value.h"
#include "../Aaspcommand/aaspcommand.h"
#include "../Aaspcommand/UICoreLauncher.h"
#include <QTest>
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
			QTest::qSleep(gTime);
			if (!Active) { 
				//qDebug().noquote() << "Ticker Stop";
				break; 
			}
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
		uInfoWidget* InfoWidget;
		uSoundService* PlayMusic;
		ChangeWake* changeWAKE = new ChangeWake();
		ReciveUserControl* userControl = new ReciveUserControl();
		void setupUI(int X,int Y,int L,int T) {
			this->setGeometry(100, 100, X, Y);
			this->setFixedSize(this->width(), this->height());
			this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
			InfoWidget = new uInfoWidget(X, Y, this);
			InfoWidget->setGeometry(QRect(0.70 * X, 0.07 * Y, 0.31 * X, 0.86 * Y));
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
		tick AnimationTick = 0;
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
			this->setWindowIcon(QIcon(PROPATH::Users+"/source/WinICO/Story.ico"));
			this->setWindowTitle("Yayin Story Player");
			this->setParent(parent);
			InfoWidget->raise();
			Ticker = new TickThread();
			Ticker->setInterval(10);
			Ticker->start();
			connect(this->Ticker, SIGNAL(timeout()), this, SLOT(tickslot()));
			connect(this->PlayerPage, SIGNAL(UserChooseWhich(QString)), this->userControl, SLOT(ChooseWhichBranch(QString)));
			connect(this, SIGNAL(stopNow()), this->userControl, SLOT(ExitNow()));
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
			QString ChooseStory = QFileDialog::getOpenFileName(this, msg("Player_ChooseFilePage_Text_Title"), PROPATH::Users + "/story", "Story File(*.spol)");
			//qDebug().noquote() << "StoryName" + ChooseStory;
			if (ChooseStory != "") {
				InfoWidget->addNewInfo("׼������������", "����Ԥ����ģ��", "Ŀ���ļ�"+ChooseStory.section("/",-1,-1), EIFL::SRI);
				Interpreter = new SPAWN(ChooseStory);
				
				FirstPage->LoadingInfo->setText("");
				connect(Interpreter->signalName, SIGNAL(send_kernal_info(QString)), this->FirstPage, SLOT(getLoadingInfo(QString)));
				connect(Interpreter->signalName, SIGNAL(send_EIFL_info(QString, QString, QString, EIFL)), this->InfoWidget, SLOT(addNewInfo(QString, QString, QString, EIFL)));
				connect(Interpreter->signalName, SIGNAL(can_hide_hello(int)), this, SLOT(hideHello(int)));
				connect(Interpreter->signalName, SIGNAL(can_reprint_hello(int)), this, SLOT(reprintHello(int)));
				connect(Interpreter->signalName, SIGNAL(need_to_choose(QStringList)), this->PlayerPage, SLOT(setBranchButton(QStringList)));
				connect(Interpreter->signalName, SIGNAL(can_set_title(QStringList)), this, SLOT(setTitle(QStringList)));
				connect(Interpreter->signalName, SIGNAL(can_show_title(void)), this, SLOT(showTitle(void)));
				connect(Interpreter->signalName, SIGNAL(can_hide_title(void)), this, SLOT(hideTitle(void)));
				connect(Interpreter->signalName, SIGNAL(can_prepare_play(void)), this, SLOT(hideTitleLast(void)));
				connect(Interpreter->signalName, SIGNAL(can_update_bg(Controller::Backdrop::Data)), this->PlayerPage, SLOT(setCurrentBGP(Controller::Backdrop::Data)));
				connect(Interpreter->signalName, SIGNAL(update_num_bg(float, Controller::Backdrop::Data)), this->PlayerPage, SLOT(updateCurrentBGP(float, Controller::Backdrop::Data)));
				connect(Interpreter->signalName, SIGNAL(set_cover_status(bool)), this->PlayerPage, SLOT(setCurrentFrame(bool)));
				connect(Interpreter->signalName, SIGNAL(can_update_chara(QList<QStringList>, int)), this->PlayerPage, SLOT(setCurrentAvg(QList<QStringList>, int)));
				connect(Interpreter->signalName, SIGNAL(update_avg_num(QString, float)), this->PlayerPage, SLOT(updateCurrentAvg(QString, float)));
				connect(Interpreter->signalName, SIGNAL(update_chara_num(QString, QString, bool)), this->PlayerPage, SLOT(updateCurrentWords(QString, QString, bool)));
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
				

				PlayerPage->initObject();
				Interpreter->start();
			}
			else {
				InfoWidget->addNewInfo("��δѡ���ļ���", "����Ҫѡ��һ���ļ�������������", "", EIFL::NWI);
			}
		}
		void tickslot() {
			if (StoryShow) {
				this->PlayerPage->repaintAutoButton();
				this->TitlePage->timeout();
			}
			this->InfoWidget->timeout();
		}
		//��ҳ������
		void hideHello(int num) {
			AnimationTick = 0;
			StoryShow = TRUE;
			connect(Ticker, SIGNAL(timeout()), this, SLOT(_hideHello()));
			disconnect(FirstPage->ChooseFileButton, SIGNAL(clicked()), this, SLOT(RUNCORE()));
			disconnect(FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));
		}
		void _hideHello() {	
			if (AnimationTick > 99) { 
				disconnect(Ticker, SIGNAL(timeout()), this, SLOT(_hideHello())); 
				FirstPage->OPLoadingInfo->setOpacity(1);				
			}
			FirstPage->setGOpacity(1 - (float)AnimationTick / 100);
			AnimationTick++;
		}
		//��ҳ�渴��
		void reprintHello(int num) {
			AnimationTick = 0;
			StoryShow = FALSE;
			PlayerPage->clearAll();
			FirstPage->raise();
			InfoWidget->raise();
			if (OneBGMIsPlaying) { PlayMusic->fadeMedia(); }
			disconnectInterpreter();
			Interpreter->wait();
			delete Interpreter;
			FirstPage->OPLoadingInfo->setOpacity(0);
			connect(Ticker, SIGNAL(timeout()), this, SLOT(_reprintHello()));
			connect(FirstPage->ChooseFileButton, SIGNAL(clicked()), this, SLOT(RUNCORE()));
			connect(FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));
		}
		void _reprintHello(){
			if (AnimationTick > 99) {	
				disconnect(Ticker, SIGNAL(timeout()), this, SLOT(_reprintHello()));
			}
			FirstPage->setGOpacity((float)AnimationTick / 100);
			FirstPage->repaint();
			AnimationTick++;
		}

		//����չʾ����-ǰ���
		void setTitle(QStringList titlesetList) {
			TitlePage->setTitleInfo(titlesetList[0], titlesetList[1], titlesetList[2], titlesetList[3]);
		}
		void showTitle(void){
			FirstPage->OPLoadingInfo->setOpacity(0);
			TitlePage->showPage();
			TitlePage->raise();
			InfoWidget->raise();
		}

		//����չʾ����-�а��
		void hideTitle(void) {
			TitlePage->playAnimation();
		}

		//����չʾ����-����
		void hideTitleLast(void) {
			TitlePage->hidePage();
			PlayerPage->raise();
			InfoWidget->raise();
			PlayerPage->showPlayerPage();
			PlayerPage->Working = TRUE;
		}

		//���ֿ�����-��Ƶ��������
		void playBGM(QString filename, int volume) {
			QString FilePath = PROPATH::Users + "/source/BGM/" + filename + ".mp3";
			if (filename == "����") {
				if (OneBGMIsPlaying) { PlayMusic->fadeMedia(); }
			}else if (QFile(FilePath).exists()) {
				if (OneBGMIsPlaying) { PlayMusic->fadeMedia(); }
				PlayMusic->loadFile(FilePath, volume, TRUE);
				PlayMusic->playMedia();
				OneBGMIsPlaying = TRUE;
			}
			else {
				InfoWidget->addNewInfo("�Ҳ���Ŀ��", "δ�ܴ����ֿ�����ָ�����ļ�", filename + ".mp3", EIFL::PRE);
			}
		}

		//��Ч������-��Ч��������
		void playSound(QString filename, int volume) {
			QString FilePath = PROPATH::Users + "/source/Sound/" + filename + ".mp3";
			if (filename == "����") {
				None;
			}
			else if (QFile(FilePath).exists()) {
				musicThreadList.append(new uSoundService());
				musicThreadList[musicThreadList.length() - 1]->loadFile(FilePath, volume, FALSE);
				musicThreadList[musicThreadList.length() - 1]->playMedia();
			}
			else {
				InfoWidget->addNewInfo("�Ҳ���Ŀ��", "δ�ܴ���Ƶ������ָ�����ļ�", filename + ".mp3", EIFL::PRE);
			}
		}

		//��ݼ�����
		void keyPressEvent(QKeyEvent* event) {
			if (event->key() == Qt::Key_Escape) {
				if (StoryShow == FALSE) {
					exitProgram();
				}
				else {
					if (PlayerPage->searchParameter("InLogPage") == 0) {					
						if (PlayerPage->Working) {
							InfoWidget->addNewInfo("���ڵȴ�������ֹͣ", "�Ѿ�����ֹ�ź��ύ��������", "����ɱ��еĽ��ͺ����������ֹ����", EIFL::SRI);
							if (PlayerPage->searchParameter("Auto")) {
								emit stopNow();
								StoryShow = FALSE;
							}
							else {
								PlayerPage->Auto = TRUE;
								emit stopNow();
								PlayerPage->_ToNext();
								StoryShow = FALSE;
							}
						}else{
							InfoWidget->addNewInfo("�������о��棺", "�ڽ����������׶Σ���Ҫ���԰���Esc��", "�������̲��ɴ��", EIFL::NWI);
						}					
					}
					else if (PlayerPage->searchParameter("InLogPage") == 1) {
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
			connect(Ticker, SIGNAL(timeout()), this, SLOT(wakeInterpreter()));
		}
		void wakeInterpreter() {
			Interpreter->wake();
			if (changeWAKE->STOPUNLOCK) {
				disconnect(Ticker, SIGNAL(timeout()), this, SLOT(wakeInterpreter()));
			}
		}
		//�����������������˳�����
		//���ǰɣ����������Ļ��ศ����ϵ��ɶ���Լ���Ե��������˳�������Ҹ㲻����
		//���������Ͷ���
		void exitProgram(void) {
			StoryShow = FALSE;
			Ticker->stop();
			if (OneBGMIsPlaying) { PlayMusic->fadeMedia(); }
			QApplication::instance()->quit();
		}

		void closeEvent(QCloseEvent* event) {
			Ticker->stop();
			if (OneBGMIsPlaying) { PlayMusic->fadeMedia(); }
			emit stopNow();
		}

		void disconnectInterpreter() {
			Interpreter->disconnect();
		}
};