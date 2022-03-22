#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <ctime>
#include <stdlib.h>
#include <QtMultimedia>
#include "effect.h"
#include "../langcontrol.h"
#include "../global_value.h"
#include "../core/core_T.h"
#include <QTest>
using namespace std;

class SingleInfo :public QFrame
{
	Q_OBJECT
signals:
	void needEnter();
	void willExit();
	void gTicker();
	void disConnect();
public:
	QWidget* parent;
	QLabel* InfoLabel;
	QLabel* IconLabel;
	QImage Image;
	float FrameIn = 0.0;
	float FrameOut = 0.0;
	int gStep = 0;
	float FrameTo = 0.7;
	float FrameFlash = 0.0;
	tick AliveTick = 0;
	tick waitTick = 0;
	enum class Status {
		wait = 0,
		moveIn = 1,
		moveTo = 2,
		moveOut = 3,
	};
	Status CurrentStatus;
	int r = 0;
	int g = 0;
	int b = 0;
	SingleInfo(int Y, QString Title, QString SubTitle = "", QString RawInfo = "", EIFL E_IFL = EIFL::URE, QWidget* gparent = Q_NULLPTR) :parent(gparent) {
		switch (E_IFL) {
		case EIFL::SSE:
			r = 235; g = 113; b = 33;
			break;
		case EIFL::PRE:
			r = 153; g = 17; b = 0;
			break;
		case EIFL::GFE:
			r = 217; g = 2; b = 111;
			break;
		case EIFL::URE:
			r = 128; g = 128; b = 128;
			break;
		case EIFL::SRI:
			r = 0; r = 147; b = 219;
			break;
		case EIFL::PRI:
			r = 0; g = 219; b = 14;
			break;
		case EIFL::GRI:
			r = 3; g = 219; b = 174;
			break;
		case EIFL::NWI:
			r = 217; g = 219; b = 0;
			break;
		}
		this->setStyleSheet("QFrame#SingleInfo{border:4px solid rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) +
			");border-radius:10px;background-color:rgb(" +
			QString::number(r) + "," + QString::number(g) + "," + QString::number(b) + ")}");
		this->setObjectName("SingleInfo");
		this->setParent(parent);
		this->setGeometry(QRect(parent->width(), 0.8 * parent->height(), parent->width(), parent->height() * 0.12));

		InfoLabel = new QLabel(this);
		InfoLabel->setText("<style>fontset{color:#FFFFFF;}</style><fontset><font size='" + QString::number(Y / 180) + "'>" + Title + "</font><br><font size='" + QString::number(Y / 360) + "'>" + SubTitle + "<br>" + RawInfo + "</font></fontset>");
		Image = QImage(PROPATH::Users + "/source/BaseUI/Button/LogButton_N.png");
		Image = Image.scaled(QSize(50, 50), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		IconLabel = new QLabel(this);
		IconLabel->setPixmap(QPixmap::fromImage(Image));
		IconLabel->setMaximumWidth(60);
		IconLabel->move(10, (this->height() - 50) / 2);
		InfoLabel->setGeometry(QRect(70, this->height() * 0.03, this->width() * 0.9, this->height() * 0.94));
		connect(this, SIGNAL(gTicker()), this, SLOT(tickslot()));
		CurrentStatus = Status::moveIn;
	}
public slots:
	void tickslot() {
		AliveTick++;
		//ProtectTick++;
		if (AliveTick >= 400) { moveOut(); }
		if (waitTick > 0) {
			waitTick++;
			if (waitTick > (gStep + 1) * 5 + 50) {
				waitTick = 0;
				if (CurrentStatus == Status::wait) { moveTo(); }
			}
		}
		flashThis();
		switch (CurrentStatus) {
		case Status::wait:
			break;
		case Status::moveIn:
			moveIn();
			break;
		case Status::moveTo:
			_moveTo();
			break;
		case Status::moveOut:
			_moveOut();
			break;
		}
	}
	void flashThis() {
		this->setStyleSheet("QFrame#SingleInfo{border:4px solid rgb(" + QString::number(r) + "," + QString::number(g) + "," + QString::number(b) +
			");border-radius:10px;background-color:rgb(" +
			QString::number(abs(qCos(FrameFlash)) * r) + "," +
			QString::number(abs(qCos(FrameFlash)) * g) + "," +
			QString::number(abs(qCos(FrameFlash)) * b) + ")}");
		FrameFlash += 0.02;
		if (FrameFlash >= 6.28) {
			FrameFlash = 0.0;
		}
	}
	void moveIn() {
		if (FrameIn < 0.5) {
			this->move((1.05 - qSin(FrameIn * 1.5708)) * parent->width(), 0.8 * parent->height());
		}
		else {
			this->move((1.05 - qSin(FrameIn * 1.5708)) * parent->width(), (0.8 - (FrameIn - 0.5) * 0.2) * parent->height());
		}
		if (FrameIn >= 1.0) {
			CurrentStatus = Status::wait;
			emit needEnter();
		}
		FrameIn += 0.01;
	}
	void moveTo(int Step) {
		gStep = Step;
		CurrentStatus = Status::moveTo;
	}
	void moveTo() {
		CurrentStatus = Status::moveTo;
	}
	void _moveTo() {
		double transY = qCos((double)(1.0 - FrameTo * 1.4286) * 1.5708) * 0.7;
		this->move(this->pos().x(), transY * parent->height());
		if (transY <= (0.15 * gStep + 0.05)) {
			CurrentStatus = Status::wait;
		}
		FrameTo -= 0.01;
	}
	void waitForward(int Step) {
		gStep = Step;
		waitTick = 1;
	}
	void moveOut() {
		emit willExit();
		CurrentStatus = Status::moveOut;
	}
	void exitNow() {
		emit willExit();
		CurrentStatus = Status::moveOut;
	}
	void _moveOut() {
		this->move((1.05 - qSin(FrameOut * 1.5708 + 1.5708)) * parent->width(), this->pos().y());
		if (FrameOut >= 1.05) {
			emit disConnect();
			this->hide();
			this->deleteLater();
		}
		FrameOut += 0.01;
	}
};

class uInfoWidget :public QWidget
{
	Q_OBJECT
signals:
	void timeout();
public:
	QTimer* Ticker;
	QQueue<SingleInfo*> InfoList;
	int gY;
	uInfoWidget(int X, int Y, QWidget* parent = Q_NULLPTR) {
		gY = Y;
		this->setParent(parent);
		connect(this, SIGNAL(timeout()), this, SLOT(tickslot()));
	}
public slots:
	void tickslot() {
	}
	void addNewInfo(QString Title, QString Subtitle, QString RawInfo, EIFL E_IFL) {
		SingleInfo* NewInfo = new SingleInfo(gY, Title, Subtitle, RawInfo, E_IFL, this);
		connect(this, SIGNAL(timeout()), NewInfo, SIGNAL(gTicker()));
		connect(NewInfo, SIGNAL(needEnter()), this, SLOT(tellStep()));
		connect(NewInfo, SIGNAL(willExit()), this, SLOT(moveForward()));
		connect(NewInfo, SIGNAL(disConnect()), this, SLOT(disConnectSignals()));
		NewInfo->show();
		while (InfoList.length() >= 4) {
			InfoList[0]->moveOut();
		}
	}
	void disConnectSignals() {
		SingleInfo* RawObject = static_cast<SingleInfo*>(this->sender());
		disconnect(this, SIGNAL(timeout()), RawObject, SIGNAL(gTicker()));
	}
	void tellStep() {
		SingleInfo* RawObject = static_cast<SingleInfo*>(this->sender());
		InfoList.append(RawObject);
		RawObject->moveTo(InfoList.length() - 1);
	}
	void moveForward() {
		if (InfoList.length() >= 2) {
			for (int i = 1; i < InfoList.length(); i++) {
				//InfoList[i]->moveTo(i - 1);
				InfoList[i]->waitForward(i - 1);
			}
		}
		if (!InfoList.isEmpty()) {
			disconnect(InfoList[0], SIGNAL(needEnter()), this, SLOT(tellStep()));
			disconnect(InfoList[0], SIGNAL(willExit()), this, SLOT(moveForward()));
			disconnect(InfoList[0], SIGNAL(disConnect()), this, SLOT(disConnectSignals()));
			InfoList.removeFirst();
		}
	}
};

class uFirstPage :public QFrame
{
	Q_OBJECT
signals:
	void chooseFileClicked(void);
	void exitProgramClicked(void);
public:
	QPalette BackC;
	QLabel* UIModeTextLabel;
	QGraphicsOpacityEffect* OPUIModeTextLabel;
	QPushButton* ChooseFileButton;
	QGraphicsOpacityEffect* OPChooseFileButton;
	QPushButton* ExitButton;
	QGraphicsOpacityEffect* OPExitButton;
	QTextBrowser* LoadingInfo;
	QGraphicsOpacityEffect* OPLoadingInfo;
	int gX, gY;
	uFirstPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
		this->setParent(parent);
		gX = X;
		gY = Y;
		//BackC = QPalette();
		//BackC.setColor(BackC.Background, QColor(0, 0, 0));
		//this->setAutoFillBackground(TRUE);
		//this->setPalette(BackC);
		this->setObjectName("FirstPage");
		this->setStyleSheet("QFrame#FirstPage{background-color:#000000;}");
		QString Fontsize30 = QString::number((int)(Y * 0.026)) + "px";

		LoadingInfo = new QTextBrowser(this);
		LoadingInfo->setGeometry(QRect(X * 0.1, Y * 0.1, X * 0.8, Y * 0.8));
		OPLoadingInfo = new QGraphicsOpacityEffect();
		OPLoadingInfo->setOpacity(0);
		LoadingInfo->setGraphicsEffect(OPLoadingInfo);

		LoadingInfo->setStyleSheet("\
                QTextBrowser{\
                    color:#FFFFFF;\
                    background-color:#000000;\
                    \
                    border:5px solid white;\
                    border-radius:10px;\
                    font-size:" + Fontsize30 + "}");

		UIModeTextLabel = new QLabel(this);
		UIModeTextLabel->setGeometry(QRect(X * 0.5208, Y * 0.44, Y * 0.648148, Y * 0.10185185));
		UIModeTextLabel->setAlignment(Qt::AlignCenter);
		UIModeTextLabel->setText("Yayin Story Player");
		UIModeTextLabel->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + QString::number((int)(Y * 0.074074)) + "px;font-family:'Microsoft YaHei'}");
		OPUIModeTextLabel = new QGraphicsOpacityEffect();
		OPUIModeTextLabel->setOpacity(0);
		UIModeTextLabel->setGraphicsEffect(OPUIModeTextLabel);

		ChooseFileButton = new QPushButton(this);
		ChooseFileButton->setObjectName("ChooseFileButton");
		ChooseFileButton->setGeometry(QRect(X * 0.2083, Y * 0.3703, 260, 260));
		ChooseFileButton->setStyleSheet("\
                #ChooseFileButton{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('" + PROPATH::Users + "/source/BaseUI/Button/StartButton_N.png');\
                }\
                #ChooseFileButton:hover{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('" + PROPATH::Users + "/source/BaseUI/Button/StartButton_P.png');\
                }\
                #ChooseFileButton:pressed{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('" + PROPATH::Users + "/source/BaseUI/Button/StartButton_C.png');\
                    }");
		OPChooseFileButton = new QGraphicsOpacityEffect();
		OPChooseFileButton->setOpacity(0);
		ChooseFileButton->setGraphicsEffect(OPChooseFileButton);

		ExitButton = new QPushButton(this);
		ExitButton->setObjectName("ExitButton");
		ExitButton->setGeometry(QRect(X * 0.4818, Y * 0.8564, 70, 70));
		ExitButton->setStyleSheet("\
                #ExitButton{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('" + PROPATH::Users + "/source/BaseUI/Button/ExitButton_N.png');\
                }\
                #ExitButton:hover{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('" + PROPATH::Users + "/source/BaseUI/Button/ExitButton_P.png');\
                }\
                #ExitButton:pressed{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('" + PROPATH::Users + "/source/BaseUI/Button/ExitButton_C.png');\
                    }");
		OPExitButton = new QGraphicsOpacityEffect();
		OPExitButton->setOpacity(1);
		ExitButton->setGraphicsEffect(OPExitButton);

		connect(this->ChooseFileButton, SIGNAL(clicked()), this, SIGNAL(chooseFileClicked()));
		connect(this->ExitButton, SIGNAL(clicked()), this, SIGNAL(exitProgramClicked()));
	}

	void setGOpacity(float Opacity_Float) {
		OPChooseFileButton->setOpacity(Opacity_Float);
		OPUIModeTextLabel->setOpacity(Opacity_Float);
		OPExitButton->setOpacity(Opacity_Float);
	}

public slots:
	void getLoadingInfo(QString Info) {
		LoadingInfo->setHtml(LoadingInfo->toHtml() + "\n" + Info);
		LoadingInfo->moveCursor(QTextCursor::End);
		qDebug().noquote() << Info.toHtmlEscaped();
	}
};

class uTitlePage :public QWidget
{
	Q_OBJECT
signals:
	void timeout();
public:
	float gX, gY;
	QLabel* TitleBackgroundLabel;
	QGraphicsOpacityEffect* OPTitleBackgroundLabel;
	QGraphicsBlurEffect* BLTitleBackgroundLabel;
	QImage BGRaw;
	QLabel* BlackHideLabel;
	QGraphicsOpacityEffect* OPBlackHideLabel;
	QImage BlackHide;
	QLabel* LogoLabel;
	QImage LogoRaw;

	QLabel* TopTitle;
	QGraphicsOpacityEffect* OPTopTitle;
	QLabel* MainTitle;
	QGraphicsOpacityEffect* OPMainTitle;
	QLabel* SubTitle;
	QGraphicsOpacityEffect* OPSubTitle;
	QLabel* Splashes_Label;
	QGraphicsOpacityEffect* OPSplashes_Label;
	QStringList gSplashList;
	tick AnimationTick = 0;
	uTitlePage(int X, int Y, QWidget* parent = Q_NULLPTR) {
		gX = X;
		gY = Y;
		QFile SplashFile;
		QStringList SplashList;
		SplashFile.setFileName(PROPATH::Users + "/text/splashes.txt");
		SplashFile.open(QIODevice::ReadOnly | QIODevice::Text);
		if (SplashFile.isOpen()) {
			QTextStream SplashFileText(&SplashFile);
			SplashFileText.setCodec("UTF-8");
			for (;;) {
				SplashList.append(SplashFileText.readLine());
				if (SplashFileText.atEnd()) { break; }
			}
		}
		else {
			SplashList.append("CAN NOT FIND SPLASHES FILE !");
		}
		gSplashList = SplashList;
		this->setParent(parent);

		QString Fontsize90 = QString::number((int)(gY * 0.082)) + "px";
		QString Fontsize60 = QString::number((int)(gY * 0.054)) + "px";
		QString Fontsize45 = QString::number((int)(gY * 0.040)) + "px";
		QString Fontsize30 = QString::number((int)(gY * 0.026)) + "px";

		TitleBackgroundLabel = new QLabel(this);
		TitleBackgroundLabel->setGeometry(QRect(0, 0, gX, gY));
		OPTitleBackgroundLabel = new QGraphicsOpacityEffect();
		OPTitleBackgroundLabel->setOpacity(0);
		TitleBackgroundLabel->setGraphicsEffect(OPTitleBackgroundLabel);

		BGRaw = QImage();

		BlackHideLabel = new QLabel(this);
		BlackHideLabel->setGeometry(QRect(0, 0, gX, gY));
		BlackHide = QImage(gX, gY, QImage::Format_ARGB32);
		BlackHide.fill(QColor(0, 0, 0, 255));
		BlackHideLabel->setPixmap(QPixmap::fromImage(BlackHide));
		OPBlackHideLabel = new QGraphicsOpacityEffect();
		OPBlackHideLabel->setOpacity(0);
		BlackHideLabel->setGraphicsEffect(OPBlackHideLabel);

		LogoLabel = new QLabel(this);
		LogoLabel->setGeometry(QRect(gX * 0.3671875, gY * 0.222222, gY * 0.4722222, gY * 0.4722222));

		LogoRaw = QImage();

		TopTitle = new QLabel(this);
		TopTitle->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize45 + ";}");
		TopTitle->setGeometry(QRect(gX * 0.333333, gY * 0.30, gX * 0.333333, gY * 0.1666666));
		TopTitle->setAlignment(Qt::AlignCenter);
		TopTitle->setText("SPOL STORY");
		OPTopTitle = new QGraphicsOpacityEffect();
		OPTopTitle->setOpacity(0);
		TopTitle->setGraphicsEffect(OPTopTitle);

		MainTitle = new QLabel(this);
		MainTitle->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize90 + ";}");
		MainTitle->setGeometry(QRect(gX * 0.333333, gY * 0.40, gX * 0.333333, gY * 0.1666666));
		MainTitle->setAlignment(Qt::AlignCenter);
		OPMainTitle = new QGraphicsOpacityEffect();
		OPMainTitle->setOpacity(0);
		MainTitle->setGraphicsEffect(OPMainTitle);

		SubTitle = new QLabel(this);
		SubTitle->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize60 + ";}");
		SubTitle->setGeometry(QRect(gX * 0.333333, gY * 0.5, gX * 0.333333, gY * 0.1666666));
		SubTitle->setAlignment(Qt::AlignCenter);
		OPSubTitle = new QGraphicsOpacityEffect();
		OPSubTitle->setOpacity(0);
		SubTitle->setGraphicsEffect(OPSubTitle);

		Splashes_Label = new QLabel(this);
		Splashes_Label->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize30 + ";font-weight:bold}");
		Splashes_Label->setAlignment(Qt::AlignCenter);
		Splashes_Label->setGeometry(QRect(0, gY * 0.85, gX, gY * 0.02777));
		OPSplashes_Label = new QGraphicsOpacityEffect();
		OPSplashes_Label->setOpacity(0);
		Splashes_Label->setGraphicsEffect(OPSplashes_Label);
	}
public slots:
	void setTitleInfo(QString Main_Title, QString Sub_Title, QString Background, QString Logo) {
		MainTitle->setText(Main_Title);
		SubTitle->setText(Sub_Title);
		BGRaw.load(PROPATH::Users + "/source/BGP/" + Background + ".png");
		BGRaw = BGRaw.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		TitleBackgroundLabel->setPixmap(QPixmap::fromImage(BGRaw));
		LogoRaw.load(PROPATH::Users + "/source/Logo/" + Logo + ".png");
		LogoRaw = LogoRaw.scaled(int(gY * 0.4722222), int(gY * 0.4722222), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		LogoLabel->setPixmap(QPixmap::fromImage(LogoRaw));
		int Splashlenth = gSplashList.length();
		int Splashwhich = randint(0, Splashlenth - 1);
		Splashes_Label->setText(gSplashList[Splashwhich]);
	}

	void showPage(void) {
		BLTitleBackgroundLabel = new QGraphicsBlurEffect();
		BLTitleBackgroundLabel->setBlurRadius(5);
		TitleBackgroundLabel->setGraphicsEffect(BLTitleBackgroundLabel);

		OPTopTitle->setOpacity(1);
		OPSubTitle->setOpacity(1);
		OPMainTitle->setOpacity(1);
		OPSplashes_Label->setOpacity(1);
		OPBlackHideLabel->setOpacity(0);
	}

	void playAnimation(void) {
		OPSplashes_Label->setOpacity(0);
		Splashes_Label->repaint();
		Splashes_Label->setText("");
		AnimationTick = 0;
		connect(this, SIGNAL(timeout()), this, SLOT(_playAnimation()));
	}
	void _playAnimation(void) {
		if (AnimationTick > 39) {
			disconnect(this, SIGNAL(timeout()), this, SLOT(_playAnimation()));
			TitleBackgroundLabel->setPixmap(QPixmap(""));
			BlackHideLabel->setPixmap(QPixmap(""));
		}
		OPBlackHideLabel->setOpacity((float)AnimationTick / 40);
		AnimationTick++;
	}

	void hidePage(void) {
		OPTitleBackgroundLabel = new QGraphicsOpacityEffect();
		OPTitleBackgroundLabel->setOpacity(0);
		TitleBackgroundLabel->setGraphicsEffect(OPTitleBackgroundLabel);

		OPTopTitle->setOpacity(0);
		OPMainTitle->setOpacity(0);
		OPSubTitle->setOpacity(0);
		OPSplashes_Label->setOpacity(0);
		OPBlackHideLabel->setOpacity(0);
	}
};

//自选剧情大板子
class uScrollPage :public QWidget
{
	Q_OBJECT
signals:
	void EmitJumpLine(int);
public:
	QLabel* BlackCover;
	QImage BlackCoverPixmap;
	QLabel* StoryBigPad;
	QLabel* StoryLineNum;
	QLabel* ToLineNum;
	QPushButton* JumpEmitButton;
	QString QSSJumpEmitButton;
	QScrollBar* StoryScroll;
	QString QSSStoryScroll;
	QList<QList<QString>> SaveLineList;
	QString LineListForDisplay;
	double gX, gY;
	uScrollPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
		gX = X;
		gY = Y;
		QString Fontsize60 = QString::number((int)(Y * 0.054)) + "px";
		QString Fontsize40 = QString::number((int)(Y * 0.036)) + "px";
		QString Fontsize30 = QString::number((int)(Y * 0.026)) + "px";
		this->setParent(parent);

		BlackCover = new QLabel(this);
		BlackCoverPixmap = QImage(X, Y, QImage::Format_ARGB32);
		BlackCoverPixmap.fill(QColor(0, 0, 0, 128));
		BlackCover->setPixmap(QPixmap::fromImage(BlackCoverPixmap));

		StoryBigPad = new QLabel(this);
		StoryBigPad->setText("");
		StoryBigPad->setAlignment(Qt::AlignLeft);
		StoryBigPad->setGeometry(QRect(X * 0.12, Y * 0, X * 0.8, Y * 1));
		StoryBigPad->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize30 + ";}");

		StoryLineNum = new QLabel(this);
		StoryLineNum->setAlignment(Qt::AlignCenter);
		StoryLineNum->setGeometry(QRect(X * 0.027, Y * 0.3, X * 0.07, Y * 0.11111));
		StoryLineNum->setText(msg("Player_Playing_Current_Line") + "\n" + "0");
		StoryLineNum->setStyleSheet("QLabel{color:#DDDDDD;font-size:" + Fontsize60 + ";font-family:'SimHei'}");

		ToLineNum = new QLabel(this);
		ToLineNum->setAlignment(Qt::AlignCenter);
		ToLineNum->setGeometry(QRect(X * 0.027, Y * 0.6, X * 0.07, Y * 0.11111));
		ToLineNum->setText(msg("Player_Playing_Jump_Line") + "\n" + "0");
		ToLineNum->setStyleSheet("QLabel{color:#DDDDDD;font-size:" + Fontsize60 + ";font-family:'SimHei'}");

		JumpEmitButton = new QPushButton(this);
		JumpEmitButton->setObjectName("JumpEmitButton");
		JumpEmitButton->setGeometry(QRect(X * 0.027, Y * 0.71, X * 0.07, Y * 0.11111));
		JumpEmitButton->setText(msg("Ui_Text_Common_Yes"));
		QSSJumpEmitButton = "\
                #JumpEmitButton{\
                    background-color:rgba(0,0,0,0);\
                    color:#DDDDDD;\
                    font-size:" + Fontsize40 + ";\
                    \
                    font-weight:bold;\
                    text-align:centre;\
                }\
                #JumpEmitButton:hover{\
                    background-color:rgba(0,0,0,0);\
                    color:#66CCFF;\
                    font-size:" + Fontsize40 + ";\
                    \
                    font-weight:bold;\
                    text-align:centre;\
                    }";
		JumpEmitButton->setStyleSheet(QSSJumpEmitButton);
		connect(JumpEmitButton, SIGNAL(clicked()), this, SLOT(EmitLineNum()));

		StoryScroll = new QScrollBar(Qt::Vertical, this);
		StoryScroll->setGeometry(QRect(X * 0.1, Y * 0, X * 0.015, Y));
		QSSStoryScroll = "\
                QScrollBar:vertical{\
                    background-color:rgba(0,0,0,0);\
                    margin:0px,0px,0px,0px;\
                    padding-top:0px;\
                    padding-bottom:0px;\
                }\
                QScrollBar::handle:vertical{\
                    background-color:rgba(255,255,255,1);\
                    border-radius:" + QString::number(X * 0.005) + "px;\
                }\
                QScrollBar::handle:vertical:hover{\
                    background-color:rgba(200,200,200,1);\
                    border-radius:" + QString::number(X * 0.005) + "px;\
                }\
                QScrollBar::add-page:vertical,QScrollBar::sub-page:vertical{\
                    background-color:rgba(0,0,0,0);\
                }\
                QScrollBar::add-line:vertical{\
                    height:0px;\
                    width:0px;\
                    subcontrol-position:bottom;\
                }\
                QScrollBar::sub-line:vertical{\
                    height:0px;\
                    width:0px;\
                    subcontrol-position:top;\
                    }";
		StoryScroll->setStyleSheet(QSSStoryScroll);
		connect(StoryScroll, SIGNAL(valueChanged(int)), this, SLOT(MoveBigPad(int)));
		SaveLineList.clear();
		LineListForDisplay = "";
	}
public slots:
	void initObject(void) {
		SaveLineList.clear();
		LineListForDisplay = "";
	}

	void setLineList(QStringList StoryLine) {
		SaveLineList.append(StoryLine);
	}

	void setScroll(void) {
		if (SaveLineList.isEmpty()) { SaveLineList.append({ "0",">>>:" }); }
		StoryScroll->setMinimum(0);
		StoryScroll->setMaximum(SaveLineList.length() - 1);
		StoryScroll->setSingleStep(1);
		QString LineListForDisplay = "";
		for (int i = 0; i < SaveLineList.length(); i++) {
			LineListForDisplay.append(QString::number(i) + "\t" + SaveLineList[i][1] + "\n\n");
		}
		StoryBigPad->setText(LineListForDisplay);
		StoryBigPad->setGeometry(QRect(gX * 0.12, gY * 0.675, gX * 0.8, (double)SaveLineList.length() * gY * 0.0612));
		StoryBigPad->adjustSize();
	}

	void UpdateLineNum(int LineInfo) {
		for (int i = 0; i < SaveLineList.length(); i++) {
			if (LineInfo == SaveLineList[i][0].toInt()) {
				StoryLineNum->setText(msg("Player_Playing_Current_Line") + "\n" + QString::number(i + 1));
				StoryScroll->setValue(i + 1);
			}
		}
	}

	void MoveBigPad(int num) {
		StoryBigPad->setGeometry(QRect(gX * 0.12, (gY * 0.675 - (float)StoryScroll->value() * (float)StoryBigPad->geometry().height() / ((float)SaveLineList.length())), gX * 0.8, StoryBigPad->geometry().height()));
		ToLineNum->setText(msg("Player_Playing_Jump_Line") + "\n" + QString::number(StoryScroll->value()));
	}

	void EmitLineNum(void) {
		emit EmitJumpLine(SaveLineList[StoryScroll->value()][0].toInt() - 1);
	}
};

class uPlayerPage :public QWidget
{
	Q_OBJECT
signals:
	void UserSpeedSet(float);
	void UserChooseWhich(QString);
	void NowInBranch(void);
	void NeedWakeUp(void);
	void NowInLog(void);

public:
	float gX, gY;
	bool gUseLogPage;
	QLabel* BG2;
	QLabel* BG1;
	QGraphicsOpacityEffect* OPBG1;
	QLabel* WhiteFlash;
	QImage WhiteFlashPixmap;
	QGraphicsOpacityEffect* OPWhiteFlash;
	QLabel* AVG_L;
	QLabel* AVG_M;
	QLabel* AVG_R;
	QGraphicsOpacityEffect* OPAVG_L;
	QGraphicsOpacityEffect* OPAVG_M;
	QGraphicsOpacityEffect* OPAVG_R;
	QImage BGR;
	QImage AVG_L_R;
	QImage AVG_M_R;
	QImage AVG_R_R;
	QLabel* Frame;
	QImage Frame_R;
	QGraphicsOpacityEffect* OPFrame;
	QLabel* NameLabel;
	QLabel* WordLabel;
	QLabel* BlackCover;
	QImage BlackCoverPixmap;
	QGraphicsOpacityEffect* OPBlackCover;
	QLabel* FreeLabel;
	QGraphicsOpacityEffect* OPFreeLabel;
	QPushButton* BranchButton_4;
	QPushButton* BranchButton_3;
	QPushButton* BranchButton_2;
	QPushButton* BranchButton_1;
	QString QSSBranchButton;
	QPushButton* AutoButton;
	QPushButton* NextButton;
	QPushButton* SpeedButton;
	int AutoButtonTick = 0;
	QString QSSNAButton;
	QString QSSSpeedButton;
	uScrollPage* LogPage;
	QPushButton* LogButton;
	QPixmap LogButtonPixRaw;
	int changeBG = 1;
	int SpeedNow = 0;
	float SpeedFloat = 1.0;
	bool Inbranch = FALSE;
	bool InLogPage = FALSE;
	bool Auto = TRUE;
	int effectuse = 0;
	ShakeFunc* ShakeFUNC;
	FlashFuncFast* FlashFUNCFast;
	FlashFuncSlow* FlashFUNCSlow;
	tick AutoTick = 0;
	bool Working = FALSE;
	uPlayerPage(int X, int Y, QWidget* parent = Q_NULLPTR, bool UseLogPage = 1) {
		this->setParent(parent);
		gX = X;
		gY = Y;
		gUseLogPage = UseLogPage;

		QString Fontsize90 = QString::number((int)(gY * 0.082)) + "px";
		QString Fontsize80 = QString::number((int)(gY * 0.073)) + "px";
		QString Fontsize60 = QString::number((int)(gY * 0.054)) + "px";
		QString Fontsize45 = QString::number((int)(gY * 0.040)) + "px";
		QString Fontsize40 = QString::number((int)(gY * 0.036)) + "px";
		QString Fontsize35 = QString::number((int)(gY * 0.031)) + "px";
		QString Fontsize30 = QString::number((int)(gY * 0.026)) + "px";

		BG2 = new QLabel(this);
		BG1 = new QLabel(this);

		BG2->setGeometry(QRect(0, 0, X, Y));
		BG1->setGeometry(QRect(0, 0, X, Y));

		OPBG1 = new QGraphicsOpacityEffect();
		OPBG1->setOpacity(0);
		BG1->setGraphicsEffect(OPBG1);

		WhiteFlash = new QLabel(this);
		WhiteFlashPixmap = QImage(X, Y, QImage::Format_ARGB32);
		WhiteFlashPixmap.fill(QColor(255, 255, 255, 255));
		WhiteFlash->setPixmap(QPixmap::fromImage(WhiteFlashPixmap));

		OPWhiteFlash = new QGraphicsOpacityEffect();
		OPWhiteFlash->setOpacity(0);
		WhiteFlash->setGraphicsEffect(OPWhiteFlash);

		AVG_L = new QLabel(this);
		AVG_M = new QLabel(this);
		AVG_R = new QLabel(this);

		AVG_L->setGeometry(QRect(gX * -0.068229, gY * 0.12, gX * 0.74635, gX * 0.75635));
		AVG_M->setGeometry(QRect(gX * 0.127083, gY * 0.12, gX * 0.74635, gX * 0.75635));
		AVG_R->setGeometry(QRect(gX * 0.321354, gY * 0.12, gX * 0.74635, gX * 0.75635));

		OPAVG_L = new QGraphicsOpacityEffect();
		OPAVG_M = new QGraphicsOpacityEffect();
		OPAVG_R = new QGraphicsOpacityEffect();

		OPAVG_L->setOpacity(0);
		OPAVG_M->setOpacity(0);
		OPAVG_R->setOpacity(0);

		AVG_L->setGraphicsEffect(OPAVG_L);
		AVG_M->setGraphicsEffect(OPAVG_M);
		AVG_R->setGraphicsEffect(OPAVG_R);

		Frame = new QLabel(this);
		Frame->setGeometry(QRect(0, 0, X, Y));
		Frame_R.load(PROPATH::Users + "/source/BaseUI/Frame/frame.png");
		Frame_R = Frame_R.scaled(X, Y, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		Frame->setPixmap(QPixmap::fromImage(Frame_R));
		OPFrame = new QGraphicsOpacityEffect();
		OPFrame->setOpacity(0);
		Frame->setGraphicsEffect(OPFrame);

		NameLabel = new QLabel(this);
		WordLabel = new QLabel(this);
		NameLabel->setStyleSheet("QLabel{color:#AAAAAA;font-size:" + Fontsize45 + ";font-weight:bold}");
		NameLabel->setAlignment(Qt::AlignRight);
		NameLabel->setGeometry(QRect(0, gY * 0.865, gX * 0.2078125, gY * 0.07));
		WordLabel->setStyleSheet("QLabel{color:#FFF5F5;font-size:" + Fontsize35 + ";font-weight:bold}");
		WordLabel->setAlignment(Qt::AlignLeft);
		WordLabel->setGeometry(QRect(gX * 0.2609375, gY * 0.87685, gX * 0.6875, gY * 0.105));

		//如果必要，这是一层用于盖住除了自由文本和按钮之外其他所有部件的灰色层
		BlackCover = new QLabel(this);
		BlackCoverPixmap = QImage(X, Y, QImage::Format_ARGB32);
		BlackCoverPixmap.fill(QColor(0, 0, 0, 128));
		BlackCover->setPixmap(QPixmap::fromImage(BlackCoverPixmap));
		OPBlackCover = new QGraphicsOpacityEffect();
		OPBlackCover->setOpacity(0);
		BlackCover->setGraphicsEffect(OPBlackCover);

		FreeLabel = new QLabel(this);
		FreeLabel->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize35 + ";font-weight:bold}");
		FreeLabel->setAlignment(Qt::AlignCenter);
		FreeLabel->setGeometry(QRect(gX * 2, -gY * 0.034, gX * 0.75, gY * 0.033));
		OPFreeLabel = new QGraphicsOpacityEffect();
		OPFreeLabel->setOpacity(0);
		FreeLabel->setGraphicsEffect(OPFreeLabel);

		BranchButton_4 = new QPushButton(this);
		BranchButton_3 = new QPushButton(this);
		BranchButton_2 = new QPushButton(this);
		BranchButton_1 = new QPushButton(this);

		BranchButton_1->setObjectName("BranchButton");
		BranchButton_2->setObjectName("BranchButton");
		BranchButton_3->setObjectName("BranchButton");
		BranchButton_4->setObjectName("BranchButton");

		QSSBranchButton = "\
                #BranchButton{\
                    color:#FFFFFF;\
                    font-size:25px;\
                    \
                    background-color:rgba(0,0,0,0);\
                    border-image:url('" + PROPATH::Users + "/source/BaseUI/Button/BranchButton_N.png');\
                }\
                #BranchButton:hover{\
                    color:#FFFFFF;\
                    font-size:25px;\
                    \
                    background-color:rgba(0,0,0,0);\
                    border-image:url('" + PROPATH::Users + "/source/BaseUI/Button/BranchButton_P.png');\
                }\
                #BranchButton:Pressed{\
                    color:#FFFFFF;\
                    font-size:25px;\
                    \
                    background-color:rgba(0,0,0,0);\
                    border-image:url('" + PROPATH::Users + "/source/BaseUI/Button/BranchButton_C.png');\
                    }";
		BranchButton_1->setStyleSheet(QSSBranchButton);
		BranchButton_2->setStyleSheet(QSSBranchButton);
		BranchButton_3->setStyleSheet(QSSBranchButton);
		BranchButton_4->setStyleSheet(QSSBranchButton);

		BranchButton_1->setGeometry(QRect(-640, -80, 635, 70));
		BranchButton_2->setGeometry(QRect(-640, -80, 635, 70));
		BranchButton_3->setGeometry(QRect(-640, -80, 635, 70));
		BranchButton_4->setGeometry(QRect(-640, -80, 635, 70));

		connect(BranchButton_1, SIGNAL(clicked()), this, SLOT(_Chooselabel()));
		connect(BranchButton_2, SIGNAL(clicked()), this, SLOT(_Chooselabel()));
		connect(BranchButton_3, SIGNAL(clicked()), this, SLOT(_Chooselabel()));
		connect(BranchButton_4, SIGNAL(clicked()), this, SLOT(_Chooselabel()));

		AutoButton = new QPushButton(this);
		AutoButton->setObjectName("AutoButton");
		AutoButton->setGeometry(QRect(-gX * 0.80729, -gY * 0.038, gX * 0.098125, gY * 0.046296));
		AutoButton->setText(msg("Player_Playing_Text_Auto"));
		AutoButtonTick = 0;
		connect(AutoButton, SIGNAL(clicked()), this, SLOT(_AutoChange()));

		NextButton = new QPushButton(this);
		NextButton->setObjectName("NextButton");
		NextButton->setGeometry(QRect(-gX * 0.902604, gY * 0.8981, gX * 0.078125, gY * 0.046296));
		NextButton->setText(msg("Player_Playing_Text_Next"));
		connect(NextButton, SIGNAL(clicked()), this, SLOT(_ToNext()));

		SpeedButton = new QPushButton(this);
		SpeedButton->setObjectName("SpeedButton");
		SpeedButton->setGeometry(QRect(-gX * 0.902604, -gY * 0.038, gX * 0.078125, gY * 0.046296));
		SpeedButton->setText("1.0x");
		connect(SpeedButton, SIGNAL(clicked()), this, SLOT(_SpeedChange()));

		QSSNAButton = "\
                QPushButton{\
                    background-color:rgba(0,0,0,0);\
                    color:#FFFFFF;\
                    font-family:'SimHei';\
                    font-size:" + Fontsize40 + ";\
                    font-weight:bold;\
                    text-align:left;\
                    }";
		AutoButton->setStyleSheet(QSSNAButton);
		NextButton->setStyleSheet(QSSNAButton);

		QSSSpeedButton = "\
                #SpeedButton{\
                    background-color:rgba(0,0,0,0);\
                    font-size:" + Fontsize40 + ";\
                    \
                    text-align:left;\
                    color:#FFFFFF;\
                    }";
		SpeedButton->setStyleSheet(QSSSpeedButton);

		if (UseLogPage) {
			LogPage = new uScrollPage(X, Y, this);
			LogPage->setGeometry(QRect(X, Y, X, Y));
			connect(LogPage->JumpEmitButton, SIGNAL(clicked()), this, SLOT(showLogPage()));
		}

		LogButton = new QPushButton(this);
		LogButtonPixRaw = QPixmap(PROPATH::Users + "/source/BaseUI/Button/LogButton_N.png");
		LogButtonPixRaw = LogButtonPixRaw.scaled(gY * 0.055, gY * 0.055, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		LogButton->setIcon(QIcon(LogButtonPixRaw));
		LogButton->setIconSize(QSize(gY * 0.055, gY * 0.055));
		LogButton->setGeometry(QRect(-gX * 0.030416, gY * 0.033, gY * 0.055, gY * 0.055));
		LogButton->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
		connect(LogButton, SIGNAL(clicked()), this, SLOT(showLogPage()));
	}

public slots:
	void initObject(void) {
		changeBG = 1;
		SpeedNow = 0;
		SpeedFloat = 1.0;
		Inbranch = FALSE;
		InLogPage = FALSE;
		Auto = TRUE;
		AutoButtonTick = 0;
		AutoTick = 0;
		effectuse = 0;
		emit UserSpeedSet(1);
		SpeedButton->setText("1.0x");
		AVG_L->setPixmap(QPixmap());
		AVG_M->setPixmap(QPixmap());
		AVG_R->setPixmap(QPixmap());
		OPAVG_L->setOpacity(0);
		OPAVG_M->setOpacity(0);
		OPAVG_R->setOpacity(0);
		OPFrame->setOpacity(0);
		if (gUseLogPage) { LogPage->initObject(); }
	}

	int searchParameter(QString Parametername) {
		if (Parametername == "Auto") { return Auto; }
		else if (Parametername == "Inbranch") { return Inbranch; }
		else if (Parametername == "InLogPage") { return InLogPage; }
		else { return -1; }
	}

	void setBranchButton(QStringList BranchList) {
		Inbranch = TRUE;
		emit NowInBranch();
		int converlstlen = BranchList.length();
		qDebug() << "SETBRANCHBUTTON";
		if (gUseLogPage) { LogButton->setGeometry(QRect(-gX * 0.030416, gY * 0.033, gY * 0.055, gY * 0.055)); }

		if (converlstlen > 0) {
			BranchButton_1->setText(BranchList[0].section(":", -1, -1));
		}if (converlstlen > 1) {
			BranchButton_2->setText(BranchList[1].section(":", -1, -1));
		}if (converlstlen > 2) {
			BranchButton_3->setText(BranchList[2].section(":", -1, -1));
		}if (converlstlen > 3) {
			BranchButton_4->setText(BranchList[3].section(":", -1, -1));
		}
		if (converlstlen == 1) {
			BranchButton_1->setGeometry(QRect(gX / 2 - 317.5, gY * 0.402777, 635, 70));
		}if (converlstlen == 2) {
			BranchButton_1->setGeometry(QRect(gX / 2 - 317.5, gY * 0.337962963, 635, 70));
			BranchButton_2->setGeometry(QRect(gX / 2 - 317.5, gY * 0.435185, 635, 70));
		}if (converlstlen == 3) {
			BranchButton_1->setGeometry(QRect(gX / 2 - 317.5, gY * 0.273148, 635, 70));
			BranchButton_2->setGeometry(QRect(gX / 2 - 317.5, gY * 0.37037037, 635, 70));
			BranchButton_3->setGeometry(QRect(gX / 2 - 317.5, gY * 0.46759, 635, 70));
		}if (converlstlen == 4) {
			BranchButton_1->setGeometry(QRect(gX / 2 - 317.5, gY * 0.2574074, 635, 70));
			BranchButton_2->setGeometry(QRect(gX / 2 - 317.5, gY * 0.3546296, 635, 70));
			BranchButton_3->setGeometry(QRect(gX / 2 - 317.5, gY * 0.45185185, 635, 70));
			BranchButton_4->setGeometry(QRect(gX / 2 - 317.5, gY * 0.549074, 635, 70));
		}
	}

	void showPlayerPage(void) {
		AutoButton->setGeometry(QRect(gX * 0.80729, gY * 0.038, gX * 0.098125, gY * 0.046296));
		SpeedButton->setGeometry(QRect(gX * 0.902604, gY * 0.038, gX * 0.078125, gY * 0.046296));
		if (gUseLogPage) { LogButton->setGeometry(QRect(gX * 0.030416, gY * 0.033, gY * 0.055, gY * 0.055)); }
	}

	void setCurrentFrame(bool FrameOpacity) {
		qDebug() << FrameOpacity;
		if (FrameOpacity) {
			OPFrame->setOpacity(1);
		}
		else {
			OPFrame->setOpacity(0);
		}
	}

	void setCurrentAvg(QList<QStringList> CharaPicList, int Charanum) {
		NameLabel->setText("");
		WordLabel->setText("");
		AVG_L->setPixmap(QPixmap());
		AVG_M->setPixmap(QPixmap());
		AVG_R->setPixmap(QPixmap());

		if (Charanum == 1) {
			for (int a = 0; a < CharaPicList.length(); a++) {
				QStringList i = CharaPicList[a];
				if (i[0] == "") {
					AVG_L->setPixmap(QPixmap());
					AVG_M->setPixmap(QPixmap());
					AVG_R->setPixmap(QPixmap());
				}
				else {
					AVG_L->setPixmap(QPixmap());
					AVG_R->setPixmap(QPixmap());
					QString Addname = "";
					if (i[3] == "0") { Addname = ""; }
					else { Addname += "_" + i[3]; }
					if (i[6] == "(暗，沉默)") { Addname += "_6"; }
					if (Addname != "") {
						if (i[1] == "") {
							AVG_M_R.load(PROPATH::Users + "/cache/Chara/" + i[0] + Addname + ".png");
						}
						else {
							AVG_M_R.load(PROPATH::Users + "/cache/Chara/" + i[0] + "_" + i[1] + Addname + ".png");
						}
					}
					else {
						if (i[1] == "") {
							AVG_M_R.load(PROPATH::Users + "/source/Chara/" + i[0] + ".png");
						}
						else {
							AVG_M_R.load(PROPATH::Users + "/source/Chara/" + i[0] + "_" + i[1] + ".png");
						}
					}
					if (!AVG_M_R.isNull()) {
						AVG_M_R = AVG_M_R.scaled(gX * 0.74635, gX * 0.74635, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
					}
					if (AVG_M->pixmap()->cacheKey() != QPixmap::fromImage(AVG_M_R).cacheKey()) {
						if (i[2] == "0") { AVG_M->setPixmap(QPixmap::fromImage(AVG_M_R)); }
						else if (i[2] == "1") { AVG_M->setPixmap(QPixmap::fromImage(AVG_M_R.mirrored(TRUE, FALSE))); }
					}
				}
			}
		}
		else if (Charanum == 2) {
			AVG_M->setPixmap(QPixmap());
			if (CharaPicList[0][0] != "") {
				QString Addname = "";
				if (CharaPicList[0][3] == "0") { Addname = ""; }
				else { Addname += "_" + CharaPicList[0][3]; }
				if (CharaPicList[0][6] == "(暗，沉默)") { Addname += "_6"; }
				if (Addname != "") {
					if (CharaPicList[0][1] == "") {
						AVG_L_R.load(PROPATH::Users + "/cache/Chara/" + CharaPicList[0][0] + Addname + ".png");
					}
					else {
						AVG_L_R.load(PROPATH::Users + "/cache/Chara/" + CharaPicList[0][0] + "_" + CharaPicList[0][1] + Addname + ".png");
					}
				}
				else {
					if (CharaPicList[0][1] == "") {
						AVG_L_R.load(PROPATH::Users + "/source/Chara/" + CharaPicList[0][0] + ".png");
					}
					else {
						AVG_L_R.load(PROPATH::Users + "/source/Chara/" + CharaPicList[0][0] + "_" + CharaPicList[0][1] + ".png");
					}
				}
				if (!AVG_L_R.isNull()) {
					AVG_L_R = AVG_L_R.scaled(gX * 0.74635, gX * 0.74635, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
				}
				if (AVG_L->pixmap()->cacheKey() != QPixmap::fromImage(AVG_L_R).cacheKey()) {
					if (CharaPicList[0][2] == "0") { AVG_L->setPixmap(QPixmap::fromImage(AVG_L_R)); }
					else if (CharaPicList[0][2] == "1") { AVG_L->setPixmap(QPixmap::fromImage(AVG_L_R.mirrored(TRUE, FALSE))); }
				}
			}
			if (CharaPicList[1][0] != "") {
				QString Addname = "";
				if (CharaPicList[1][3] == "0") { Addname = ""; }
				else { Addname += "_" + CharaPicList[1][3]; }
				if (CharaPicList[1][6] == "(暗，沉默)") { Addname += "_6"; }
				if (Addname != "") {
					if (CharaPicList[1][1] == "") {
						AVG_R_R.load(PROPATH::Users + "/cache/Chara/" + CharaPicList[1][0] + Addname + ".png");
					}
					else {
						AVG_R_R.load(PROPATH::Users + "/cache/Chara/" + CharaPicList[1][0] + "_" + CharaPicList[1][1] + Addname + ".png");
					}
				}
				else {
					if (CharaPicList[1][1] == "") {
						AVG_R_R.load(PROPATH::Users + "/source/Chara/" + CharaPicList[1][0] + ".png");
					}
					else {
						AVG_R_R.load(PROPATH::Users + "/source/Chara/" + CharaPicList[1][0] + "_" + CharaPicList[1][1] + ".png");
					}
				}
				if (!AVG_R_R.isNull()) {
					AVG_R_R = AVG_R_R.scaled(gX * 0.74635, gX * 0.74635, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
				}
				if (AVG_R->pixmap()->cacheKey() != QPixmap::fromImage(AVG_R_R).cacheKey()) {
					if (CharaPicList[1][2] == "0") { AVG_R->setPixmap(QPixmap::fromImage(AVG_R_R)); }
					else if (CharaPicList[1][2] == "1") { AVG_R->setPixmap(QPixmap::fromImage(AVG_R_R.mirrored(TRUE, FALSE))); }
				}
			}
		}
	}

	void updateCurrentAvg(QString whichAvg, float OpFloat) {
		if (whichAvg.contains("M")) {
			OPAVG_M->setOpacity(OpFloat);
		}
		if (whichAvg.contains("L")) {
			OPAVG_L->setOpacity(OpFloat);
		}
		if (whichAvg.contains("R")) {
			OPAVG_R->setOpacity(OpFloat);
		}
	}

	void updateCurrentWords(QString Name, QString WordsCurrent, bool FirstSet) {
		if (FirstSet) {
			if (Name != NameLabel->text()) { NameLabel->setText(Name); }
		}
		else {
			WordLabel->setText(WordsCurrent);
		}
	}

	void setCurrentBGP(Controller::Backdrop::Data SetList) {
		if (SetList.Backdrop == "黑场") {
			BGR = QImage(gX, gY, QImage::Format_ARGB32);
			BGR.fill(QColor(0, 0, 0, 255));
		}
		else {
			if (SetList.Filter == "0") {
				BGR.load(PROPATH::Users + "/source/BGP/" + SetList.Backdrop + ".png");
				BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			}
			else {
				BGR.load(PROPATH::Users + "/cache/BGP/" + SetList.Backdrop + "_" + SetList.Filter + ".png");
				BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
			}
		}
	}

	void updateCurrentBGP(float Opacity_Float, Controller::Backdrop::Data SetList) {
		if (changeBG == 1) {
			if (Opacity_Float == 0) {
				BG1->setPixmap(QPixmap::fromImage(BGR));
				OPBG1->setOpacity(0);
			}
			else if (Opacity_Float != 0 && Opacity_Float != 1) {
				OPBG1->setOpacity(Opacity_Float);
			}
			else if (Opacity_Float >= 1) {
				OPBG1->setOpacity(1);
				changeBG = 2;
			}
		}
		else if (changeBG == 2) {
			if (Opacity_Float == 0) {
				BG2->setPixmap(QPixmap::fromImage(BGR));
				OPBG1->setOpacity(1);
			}
			else if (Opacity_Float != 0 && Opacity_Float != 1) {
				OPBG1->setOpacity(1 - Opacity_Float);
			}
			else if (Opacity_Float >= 1) {
				OPBG1->setOpacity(0);
				changeBG = 1;
			}
		}
		if (Opacity_Float >= 1) {
			if (SetList.Effect == 1) {
				ShakeFUNC = new ShakeFunc(SpeedFloat);
				connect(ShakeFUNC, SIGNAL(shakeXY(int, int, int)), this, SLOT(_ShakeRect(int, int, int)));
				ShakeFUNC->start();
			}
			else if (SetList.Effect == 2) {
				effectuse = 2;
				FlashFUNCFast = new FlashFuncFast(SpeedFloat);
				connect(FlashFUNCFast, SIGNAL(FlashOPint(float, int)), this, SLOT(_FlashWhite(float, int)));
				FlashFUNCFast->start();
			}
			else if (SetList.Effect == 3) {
				effectuse = 3;
				FlashFUNCSlow = new FlashFuncSlow(SpeedFloat);
				connect(FlashFUNCSlow, SIGNAL(FlashOPint(float, int)), this, SLOT(_FlashWhite(float, int)));
				FlashFUNCSlow->start();
			}
			else {
				QTest::qSleep(5);
				showNext();
			}
		}
	}

	void setCurrentFree(QStringList textsetlst, QStringList wordset) {
		FreeLabel->setText("");
		OPFreeLabel->setOpacity(0);
		FreeLabel->setGeometry(QRect(gX * textsetlst[0].toFloat(), gY * textsetlst[1].toFloat(), gX * 0.75, gY * 0.04));
		if (textsetlst[2] == "L") {
			FreeLabel->setAlignment(Qt::AlignLeft);
		}
		else if (textsetlst[2] == "M") {
			FreeLabel->setAlignment(Qt::AlignCenter);
		}
		else if (textsetlst[2] == "R") {
			FreeLabel->setAlignment(Qt::AlignRight);
		}
		OPFreeLabel->setOpacity(1);
	}

	void updateCurrentFree(QString Words) {
		FreeLabel->setText(Words);
	}

	void clearCurrentFree(int end) {
		FreeLabel->setText("");
		OPFreeLabel->setOpacity(0);
	}

	void clearAll(void) {
		Working = FALSE;
		NameLabel->setText("");
		WordLabel->setText("");
		FreeLabel->setText("");
		AVG_L->setPixmap(QPixmap(""));
		AVG_M->setPixmap(QPixmap(""));
		AVG_R->setPixmap(QPixmap(""));
		BG1->setPixmap(QPixmap(""));
		BG2->setPixmap(QPixmap(""));

		AutoButton->setGeometry(QRect(-gX * 0.80729, -gY * 0.038, gX * 0.098125, gY * 0.046296));
		SpeedButton->setGeometry(QRect(-gX * 0.902604, -gY * 0.038, gX * 0.078125, gY * 0.046296));
		NextButton->setGeometry(QRect(-gX * 0.902604, gY * 0.8981, gX * 0.078125, gY * 0.046296));
		if (gUseLogPage) {
			LogButton->setGeometry(QRect(-gX * 0.030416, gY * 0.033, gY * 0.055, gY * 0.055));
		}
	}

	void wheelEvent(QWheelEvent* event) {
		if (InLogPage) {
			LogPage->StoryScroll->setValue(LogPage->StoryScroll->value() - (int)(event->angleDelta().y() / 120));
		}
	}

	void _ShakeRect(int sX, int sY, int end) {
		if (changeBG == 2) {
			BG1->setGeometry(QRect(gY / 1080 * sX, gY / 1080 * sY, gX, gY));
			BG1->repaint();
		}
		else if (changeBG == 1) {
			BG2->setGeometry(QRect(gY / 1080 * sX, gY / 1080 * sY, gX, gY));
			BG2->repaint();
		}
		if (end == 1) {
			QTest::qSleep(5);
			showNext();
		}
	}

	void _FlashWhite(float Opacity_Float, int end) {
		if (end == 0) {
			OPWhiteFlash->setOpacity(0);
		}
		else if (end == 1) {
			OPWhiteFlash->setOpacity(Opacity_Float);
			WhiteFlash->repaint();
		}
		else if (end == 2) {
			OPWhiteFlash->setOpacity(0);
			if (effectuse == 2) {
				FlashFUNCFast->wait();
				effectuse = 0;
			}
			else if (effectuse == 3) {
				FlashFUNCSlow->wait();
				effectuse = 0;
			}
			QTest::qSleep(5);
			showNext();
		}
	}

	void _AutoChange(void) {
		if (Auto) {
			Auto = FALSE;
			AutoButton->setText(msg("Player_Playing_Text_Auto") + " OFF");
		}
		else {
			Auto = TRUE;
			AutoButton->setText(msg("Player_Playing_Text_Auto"));
		}
	}

	void repaintAutoButton(void) {
		AutoTick++;
		if (AutoTick > SpeedFloat * 50) {
			AutoTick = 0;
			if (Auto) {
				if (AutoButtonTick == 0) {
					AutoButton->setText(msg("Player_Playing_Text_Auto"));
					AutoButtonTick += 1;
				}
				else {
					AutoButton->setText(AutoButton->text() + "▶");
					if (AutoButtonTick == 3) { AutoButtonTick = 0; }
					else { AutoButtonTick += 1; }
				}
			}
		}
	}

	void _SpeedChange(void) {
		SpeedNow += 1;
		if (SpeedNow % 4 == 1) {
			emit UserSpeedSet(0.666);
			SpeedButton->setText("1.5x");
			SpeedFloat = 0.666;
		}
		else if (SpeedNow % 4 == 2) {
			emit UserSpeedSet(0.5);
			SpeedButton->setText("2.0x");
			SpeedFloat = 0.5;
		}
		else if (SpeedNow % 4 == 3) {
			emit UserSpeedSet(2);
			SpeedButton->setText("0.5x");
			SpeedFloat = 2;
		}
		else if (SpeedNow % 4 == 0) {
			emit UserSpeedSet(1);
			SpeedButton->setText("1.0x");
			SpeedFloat = 0.666;
			SpeedNow = 0;
		}
	}

	void _Chooselabel(void) {
		QPushButton* WhichButtonSend = static_cast<QPushButton*>(this->sender());
		emit UserChooseWhich(WhichButtonSend->text());

		BranchButton_1->setGeometry(QRect(-640, -80, 635, 70));
		BranchButton_2->setGeometry(QRect(-640, -80, 635, 70));
		BranchButton_3->setGeometry(QRect(-640, -80, 635, 70));
		BranchButton_4->setGeometry(QRect(-640, -80, 635, 70));

		BranchButton_1->setText("");
		BranchButton_2->setText("");
		BranchButton_3->setText("");
		BranchButton_4->setText("");

		Inbranch = FALSE;
		if (gUseLogPage) { LogButton->setGeometry(QRect(gX * 0.030416, gY * 0.033, gY * 0.055, gY * 0.055)); }
		showNext();
	}

	void showNext(void) {
		if (Auto) {
			emit NeedWakeUp();
		}
		else {
			NextButton->setGeometry(QRect(gX * 0.868, gY * 0.925, gX * 0.078125, gY * 0.046296));
		}
	}

	void _ToNext(void) {
		emit NeedWakeUp();
		NextButton->setGeometry(QRect(-gX * 0.902604, -gY * 0.8981, gX * 0.078125, gY * 0.046296));
	}

	void showLogPage(void) {
		if (InLogPage == FALSE) {
			emit NowInLog();
			if (Auto) {
				_AutoChange();
			}
			LogPage->setGeometry(QRect(0, 0, gX, gY));
			InLogPage = TRUE;
		}
		else if (InLogPage == TRUE) {
			if (!Auto) {
				_AutoChange();
			}
			if (NextButton->geometry() == QRect(gX * 0.868, gY * 0.925, gX * 0.078125, gY * 0.046296)) {
				_ToNext();
			}
			LogPage->setGeometry(QRect(-gX, -gY, gX, gY));
			InLogPage = FALSE;
		}
	}
};

//音频放送服务
class uSoundService :public QObject
{
	Q_OBJECT
public:
	QMediaPlayer* MediaPlayer;
	QMediaPlaylist* PlayList;
	uSoundService() {
		MediaPlayer = new QMediaPlayer();
		PlayList = new QMediaPlaylist();
		MediaPlayer->setPlaylist(PlayList);
	}
	void loadFile(QString Filename, int Volume, bool Loop) {
		PlayList->clear();
		PlayList->addMedia(QUrl::fromLocalFile(Filename));
		if (Loop) { PlayList->setPlaybackMode(QMediaPlaylist::Loop); }
		//MediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(Filename)));
		MediaPlayer->setVolume(Volume);
	}

	void playMedia(void) {
		PlayList->setCurrentIndex(0);
		MediaPlayer->play();
	}

	void fadeMedia(void) {
		for (int i = MediaPlayer->volume(); i > 0; i--) {
			MediaPlayer->setVolume(i);
			QTest::qSleep(10);
		}
		MediaPlayer->stop();
	}
};