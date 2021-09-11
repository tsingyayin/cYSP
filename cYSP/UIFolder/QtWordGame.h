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
using namespace std;

class uFirstPage :public QWidget
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
        int gX, gY;
        uFirstPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            gX = X;
            gY = Y;
            BackC = QPalette();
            BackC.setColor(BackC.Background, QColor(0, 0, 0));
            this->setAutoFillBackground(TRUE);
            this->setPalette(BackC);
            UIModeTextLabel = new QLabel(this);
            UIModeTextLabel->setGeometry(QRect(X * 0.5208, Y * 0.44, Y * 0.648148, Y * 0.10185185));
            UIModeTextLabel->setAlignment(Qt::AlignCenter);
            UIModeTextLabel->setText(msg("UI_Msg_Current_Mode"));
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
                    background-image:url('./Visual/source/BaseUI/Button/StartButton_N.png');\
                }\
                #ChooseFileButton:hover{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('./Visual/source/BaseUI/Button/StartButton_P.png');\
                }\
                #ChooseFileButton:pressed{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('./Visual/source/BaseUI/Button/StartButton_C.png');\
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
                    background-image:url('./Visual/source/BaseUI/Button/ExitButton_N.png');\
                }\
                #ExitButton:hover{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('./Visual/source/BaseUI/Button/ExitButton_P.png');\
                }\
                #ExitButton:pressed{\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('./Visual/source/BaseUI/Button/ExitButton_C.png');\
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
};

class uTitlePage :public QWidget
{
    Q_OBJECT
    public:
        int gX, gY;
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

        uTitlePage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            gX = X;
            gY = Y;
            QFile SplashFile;
            QStringList SplashList;
            SplashFile.setFileName("./text/splashes.txt");
            SplashFile.open(QIODevice::ReadOnly | QIODevice::Text);
            if (SplashFile.isOpen()) {
                QTextStream SplashFileText(&SplashFile);
                SplashFileText.setCodec("UTF-8");
                for (;;) {
                    SplashList.append(SplashFileText.readLine());
                    if (SplashFileText.atEnd()) { break; }             
                }       
            }
            gSplashList = SplashList;
            this->setParent(parent);

            QString Fontsize90 = QString::number(Y * 0.083333) + "px";
            QString Fontsize60 = QString::number(Y * 0.055555) + "px";
            QString Fontsize45 = QString::number(Y * 0.041666) + "px";
            QString Fontsize30 = QString::number(Y * 0.027777) + "px";

            TitleBackgroundLabel = new QLabel(this);
            TitleBackgroundLabel->setGeometry(QRect(0, 0, X, Y));
            OPTitleBackgroundLabel = new QGraphicsOpacityEffect();
            OPTitleBackgroundLabel->setOpacity(0);
            TitleBackgroundLabel->setGraphicsEffect(OPTitleBackgroundLabel);

            BGRaw = QImage();

            BlackHideLabel = new QLabel(this);
            BlackHideLabel->setGeometry(QRect(0, 0, X, Y));
            BlackHide = QImage(X, Y, QImage::Format_ARGB32);
            BlackHide.fill(QColor(0, 0, 0, 255));
            BlackHideLabel->setPixmap(QPixmap::fromImage(BlackHide));
            OPBlackHideLabel = new QGraphicsOpacityEffect();
            OPBlackHideLabel->setOpacity(0);
            BlackHideLabel->setGraphicsEffect(OPBlackHideLabel);

            LogoLabel = new QLabel(this);
            LogoLabel->setGeometry(QRect(X * 0.3671875, Y * 0.222222, Y * 0.4722222, Y * 0.4722222));

            LogoRaw = QImage();

            TopTitle = new QLabel(this);
            TopTitle->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize45 + ";font-family:'Microsoft YaHei'}");
            TopTitle->setGeometry(QRect(X * 0.333333, Y * 0.30, X * 0.333333, Y * 0.1666666));
            TopTitle->setAlignment(Qt::AlignCenter);
            TopTitle->setText("SPOL STORY");
            OPTopTitle = new QGraphicsOpacityEffect();
            OPTopTitle->setOpacity(0);
            TopTitle->setGraphicsEffect(OPTopTitle);

            MainTitle = new QLabel(this);
            MainTitle->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize90 + ";font-family:'Microsoft YaHei'}");
            MainTitle->setGeometry(QRect(X * 0.333333, Y * 0.40, X * 0.333333, Y * 0.1666666));
            MainTitle->setAlignment(Qt::AlignCenter);
            OPMainTitle = new QGraphicsOpacityEffect();
            OPMainTitle->setOpacity(0);
            MainTitle->setGraphicsEffect(OPMainTitle);

            SubTitle = new QLabel(this);
            SubTitle->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize60 + ";font-family:'Microsoft YaHei'}");
            SubTitle->setGeometry(QRect(X * 0.333333, Y * 0.5, X * 0.333333, Y * 0.1666666));
            SubTitle->setAlignment(Qt::AlignCenter);
            OPSubTitle = new QGraphicsOpacityEffect();
            OPSubTitle->setOpacity(0);
            SubTitle->setGraphicsEffect(OPSubTitle);

            Splashes_Label = new QLabel(this);
            Splashes_Label->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize30 + ";font-family:'SimHei';font-weight:bold}");
            Splashes_Label->setAlignment(Qt::AlignCenter);
            Splashes_Label->setGeometry(QRect(0, Y * 0.85, X, Y * 0.02777));
            OPSplashes_Label = new QGraphicsOpacityEffect();
            OPSplashes_Label->setOpacity(0);
            Splashes_Label->setGraphicsEffect(OPSplashes_Label);
        }
        void setTitleInfo(QString Main_Title, QString Sub_Title, QString Background, QString Logo) {
            MainTitle->setText(Main_Title);
            SubTitle->setText(Sub_Title);
            BGRaw.load("./Visual/source/BGP/" + Background + ".png");
            BGRaw = BGRaw.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            TitleBackgroundLabel->setPixmap(QPixmap::fromImage(BGRaw));
            LogoRaw.load("./Visual/source/Logo/" + Logo + ".png");
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
            for (int i = 0; i <= 21; i++) {
                OPBlackHideLabel->setOpacity(i / 20);
                BlackHideLabel->repaint();
            }
            TitleBackgroundLabel->setPixmap(QPixmap(""));
            BlackHideLabel->setPixmap(QPixmap(""));
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
    int gX, gY;
    uScrollPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
        gX = X;
        gY = Y;
        QString Fontsize60 = QString::number(Y * 0.055555) + "px";
        QString Fontsize40 = QString::number(Y * 0.037037) + "px";
        QString Fontsize30 = QString::number(Y * 0.027777) + "px";

        BlackCover = new QLabel(this);
        BlackCoverPixmap = QImage(X, Y, QImage::Format_ARGB32);
        BlackCoverPixmap.fill(QColor(0, 0, 0, 128));
        BlackCover->setPixmap(QPixmap::fromImage(BlackCoverPixmap));

        StoryBigPad = new QLabel(this);
        StoryBigPad->setText("");
        StoryBigPad->setAlignment(Qt::AlignLeft);
        StoryBigPad->setGeometry(QRect(X * 0.05, Y * 0, X * 0.9, Y * 1));
        StoryBigPad->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize30 + ";font-family:'SimHei';}");

        StoryLineNum = new QLabel(this);
        StoryLineNum->setAlignment(Qt::AlignCenter);
        StoryLineNum->setGeometry(QRect(X * 0.027, Y * 0.3, X * 0.07, Y * 0.11111));
        StoryLineNum->setText(msg("Ui_Current_Line") + "\n" + "0");
        StoryLineNum->setStyleSheet("QLabel{color:#DDDDDD;font-size:" + Fontsize60 + ";font-family:'SimHei'}");

        ToLineNum = new QLabel(this);
        ToLineNum->setAlignment(Qt::AlignCenter);
        ToLineNum->setGeometry(QRect(X * 0.027, Y * 0.6, X * 0.07, Y * 0.11111));
        ToLineNum->setText(msg("Ui_To_Which_Line") + "\n" + "0");
        ToLineNum->setStyleSheet("QLabel{color:#DDDDDD;font-size:" + Fontsize60 + ";font-family:'SimHei'}");

        JumpEmitButton = new QPushButton(this);
        JumpEmitButton->setObjectName("JumpEmitButton");
        JumpEmitButton->setGeometry(QRect(X * 0.027, Y * 0.71, X * 0.07, Y * 0.11111));
        JumpEmitButton->setText(msg("Ui_Msg_Yes"));
        QSSJumpEmitButton = "\
                #JumpEmitButton{\
                    background-color:rgba(0,0,0,0);\
                    color:#DDDDDD;\
                    font-size:" + Fontsize40 + ";\
                    font-family:'SimHei';\
                    font-weight:bold;\
                    text-align:centre;\
                }\
                #JumpEmitButton:hover{\
                    background-color:rgba(0,0,0,0);\
                    color:#66CCFF;\
                    font-size:" + Fontsize40 + ";\
                    font-family:'SimHei';\
                    font-weight:bold;\
                    text-align:centre;\
                    }";
        JumpEmitButton->setStyleSheet(QSSJumpEmitButton);
        connect(JumpEmitButton, SIGNAL(clicked()), this, SLOT(EmitLineNum()));

        StoryScroll = new QScrollBar(Qt::Vertical, this);
        StoryScroll->setGeometry(QRect(X * 0.983, Y * 0, X * 0.015, Y));
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
        SaveLineList = {};
        LineListForDisplay = "";
    }
    void initObject(void) {
        SaveLineList = {};
        LineListForDisplay = "";
    }
    void setLineList(QStringList StoryLine) {
        SaveLineList.append(StoryLine);
    }
    void setScroll(void) {
        StoryScroll->setMinimum(0);
        StoryScroll->setMaximum(SaveLineList.length() - 1);
        StoryScroll->setSingleStep(1);

        QString LineListForDisplay = "";
        for (int i = 0; i < SaveLineList.length(); i++) {
            LineListForDisplay.append(QString::number(i) + "\t" + SaveLineList[i][1] + "\n\n");
        }
        StoryBigPad->setText(LineListForDisplay);
        StoryBigPad->setGeometry(QRect(gX * 0.12, gY * 0.675, gX * 0.8, (int)(SaveLineList.length() * gY * 0.06111111)));
        connect(StoryBigPad, SIGNAL(valueChanged()), this, SLOT(MoveBigPad()));
    }
public slots:
    void UpdateLineNum(QString LineInfo) {
        for (int i = 0; i < SaveLineList.length(); i++) {
            if (LineInfo == SaveLineList[i][0]) {
                StoryLineNum->setText(msg("Ui_Current_Line") + "\n" + QString::number(i + 1));
                StoryScroll->setValue(i + 1);
            }
        }
    }
    void MoveBigPad(void) {
        StoryBigPad->setGeometry(QRect(gX * 0.12, (int)(gY * 0.675 - StoryScroll->value() * gY * 0.06111111), gX * 0.8, (int)(SaveLineList.length() * gY * 0.06111111)));
        ToLineNum->setText(msg("Ui_To_Which_Line") + "\n" + QString::number(StoryScroll->value()));
    }
    void EmitLineNum(void) {
        emit EmitJumpLine(SaveLineList[StoryScroll->value()][0].toInt() - 2);
    }
};

class uPlayerPage :public QWidget
{
    Q_OBJECT
    signals:
        void UserSpeedSet(QString);
        void UserChooseWhich(QString);
        void NowInBranch(void);
        void NeedWakeUp(void);
        void NowInLog(void);

    public:
        int gX, gY;
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
        uPlayerPage(int X, int Y, QWidget* parent = Q_NULLPTR, bool UseLogPage = 1) {
            this->setParent(parent);
            gX = X;
            gY = Y;
            gUseLogPage = UseLogPage;

            QString Fontsize90 = QString::number(Y * 0.083333) + "px";
            QString Fontsize80 = QString::number(Y * 0.074074) + "px";
            QString Fontsize60 = QString::number(Y * 0.055555) + "px";
            QString Fontsize45 = QString::number(Y * 0.041666) + "px";
            QString Fontsize40 = QString::number(Y * 0.037037) + "px";
            QString Fontsize35 = QString::number(Y * 0.032407) + "px";
            QString Fontsize30 = QString::number(Y * 0.027777) + "px";
           
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

            AVG_L->setGeometry(QRect(X * -0.068229, Y * 0.12, X * 0.74635, X * 0.75635));
            AVG_M->setGeometry(QRect(X * 0.127083, Y * 0.12, X * 0.74635, X * 0.75635));
            AVG_R->setGeometry(QRect(X * 0.321354, Y * 0.12, X * 0.74635, X * 0.75635));

            Frame = new QLabel(this);
            Frame->setGeometry(QRect(0, 0, X, Y));
            Frame_R.load("./Visual/source/BaseUI/Frame/frame.png");
            Frame_R = Frame_R.scaled(X, Y, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            Frame->setPixmap(QPixmap::fromImage(Frame_R));
            OPFrame = new QGraphicsOpacityEffect();
            OPFrame->setOpacity(0);
            Frame->setGraphicsEffect(OPFrame);

            NameLabel = new QLabel(this);
            WordLabel = new QLabel(this);
            NameLabel->setStyleSheet("QLabel{color:#AAAAAA;font-size:" + Fontsize45 + ";font-family:'SimHei';font-weight:bold}");
            NameLabel->setAlignment(Qt::AlignRight);
            NameLabel->setGeometry(QRect(0, Y * 0.86944, X * 0.2078125, Y * 0.042));
            WordLabel->setStyleSheet("QLabel{color:#FFF5F5;font-size:" + Fontsize35 + ";font-family:'SimHei';font-weight:bold}");
            WordLabel->setAlignment(Qt::AlignLeft);
            WordLabel->setGeometry(QRect(X * 0.2609375, Y * 0.87685, X * 0.6875, Y * 0.105));

            //如果必要，这是一层用于盖住除了自由文本和按钮之外其他所有部件的灰色层
            BlackCover = new QLabel(this);
            BlackCoverPixmap = QImage(X, Y, QImage::Format_ARGB32);
            BlackCoverPixmap.fill(QColor(0, 0, 0, 128));
            BlackCover->setPixmap(QPixmap::fromImage(BlackCoverPixmap));
            OPBlackCover = new QGraphicsOpacityEffect();
            OPBlackCover->setOpacity(0);
            BlackCover->setGraphicsEffect(OPBlackCover);

            FreeLabel = new QLabel(this);
            FreeLabel->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + Fontsize35 + ";font-family:'SimHei';font-weight:bold}");
            FreeLabel->setAlignment(Qt::AlignCenter);
            FreeLabel->setGeometry(QRect(-X * 0.76, -Y * 0.033, X * 0.75, Y * 0.0324074));
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
            
            QSSBranchButton="\
                #BranchButton{\
                    color:#FFFFFF;\
                    font-size:25px;\
                    font-family:'SimHei';\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('./Visual/source/BaseUI/Button/BranchButton_N.png');\
                }\
                #BranchButton:hover{\
                    color:#FFFFFF;\
                    font-size:25px;\
                    font-family:'SimHei';\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('./Visual/source/BaseUI/Button/BranchButton_P.png');\
                }\
                #BranchButton:Pressed{\
                    color:#FFFFFF;\
                    font-size:25px;\
                    font-family:'SimHei';\
                    background-color:rgba(0,0,0,0);\
                    background-image:url('./Visual/source/BaseUI/Button/BranchButton_C.png');\
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
            AutoButton->setGeometry(QRect(-X * 0.80729, -Y * 0.038, X * 0.098125, Y * 0.046296));
            AutoButton->setText(msg("Ui_AutoButton_Auto"));
            AutoButtonTick = 0;
            connect(AutoButton, SIGNAL(clicked()), this, SLOT(_AutoChange()));

            NextButton = new QPushButton(this);
            NextButton->setObjectName("NextButton");
            NextButton->setGeometry(QRect(-X * 0.902604, Y * 0.8981, X * 0.078125, Y * 0.046296));
            NextButton->setText(msg("Ui_NextButton"));
            connect(NextButton, SIGNAL(clicked()), this, SLOT(_ToNext()));

            SpeedButton = new QPushButton(this);
            SpeedButton->setObjectName("SpeedButton");
            SpeedButton->setGeometry(QRect(-X * 0.902604, -Y * 0.038, X * 0.078125, Y * 0.046296));
            SpeedButton->setText("1.0x");
            connect(SpeedButton, SIGNAL(clicked()), this, SLOT(_SpeedChange()));

            QSSNAButton = "\
                QPushButton{\
                    background-color:rgba(0,0,0,0);\
                    color:#FFFFFF;\
                    font-family:'SimHei';\
                    font-size:"+Fontsize40+";\
                    font-weight:bold;\
                    text-align:left;\
                    }";
            AutoButton->setStyleSheet(QSSNAButton);
            NextButton->setStyleSheet(QSSNAButton);

            QSSSpeedButton="\
                #SpeedButton{\
                    background-color:rgba(0,0,0,0);\
                    font-size:"+Fontsize40+";\
                    font-family:'Microsoft YaHei';\
                    text-align:left;\
                    color:#FFFFFF;\
                    }";
            SpeedButton->setStyleSheet(QSSSpeedButton);

            if (UseLogPage) {
                LogPage = new uScrollPage(X, Y, this);
                LogPage->setGeometry(QRect(-X, Y, X, Y));
                connect(LogPage->JumpEmitButton, SIGNAL(clicked()), this, SLOT(showLogPage()));
            }

            LogButton = new QPushButton(this);
            LogButtonPixRaw = QPixmap("./Visual/source/BaseUI/Button/LogButton_N.png");
            LogButtonPixRaw = LogButtonPixRaw.scaled(Y * 0.055, Y * 0.055, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            LogButton->setIcon(QIcon(LogButtonPixRaw));
            LogButton->setIconSize(QSize(Y * 0.055, Y * 0.055));
            LogButton->setGeometry(QRect(-X * 0.030416, Y * 0.033, Y * 0.055, Y * 0.055));
            LogButton->setStyleSheet("QPushButton{background-color:rgba(0,0,0,0);}");
            connect(LogButton, SIGNAL(clicked()), this, SLOT(showLogPage()));
        }
        void initObject(void) {
            changeBG = 1;
            SpeedNow = 0;
            SpeedFloat = 1.0;
            Inbranch = FALSE;
            InLogPage = FALSE;
            Auto = TRUE;
            AutoButtonTick = 0;
            effectuse = 0;
            emit UserSpeedSet("1");
            SpeedButton->setText("1.0x");

            if (gUseLogPage) { LogPage->initObject(); }
        }

        QString searchParameter(QString Parametername) {
            if (Parametername == "Auto") { return Auto; }
            else if (Parametername == "Inbranch") { return Inbranch; }
            else if (Parametername == "InLogPage") { return InLogPage; }
            else { return -1; }
        }

        void setBranchButton(QStringList BranchList) {
            Inbranch = TRUE;
            emit NowInBranch();
            int converlstlen = BranchList.length();

            if (converlstlen > 0) {
                BranchButton_1->setText(BranchList[0].section(":", -1, -1));
            }if (converlstlen > 1) {
                BranchButton_1->setText(BranchList[1].section(":", -1, -1));
            }if (converlstlen > 2) {
                BranchButton_1->setText(BranchList[2].section(":", -1, -1));
            }if (converlstlen > 3) {
                BranchButton_1->setText(BranchList[3].section(":", -1, -1));
            }
            if (converlstlen == 1) {
                BranchButton_1->setGeometry(QRect(gX / 2 - 317.5, gY * 0.402777, 635, 70));
            }if (converlstlen == 2) {
                BranchButton_1->setGeometry(QRect(gX / 2 - 317.5, gY * 0.337962963, 635, 70));
                BranchButton_2->setGeometry(QRect(gX / 2 - 317.5, gY * 0.435185, 635, 70));
            }if (converlstlen == 2) {
                BranchButton_1->setGeometry(QRect(gX / 2 - 317.5, gY * 0.273148, 635, 70));
                BranchButton_2->setGeometry(QRect(gX / 2 - 317.5, gY * 0.37037037, 635, 70));
                BranchButton_3->setGeometry(QRect(gX / 2 - 317.5, gY * 0.46759, 635, 70));
            }if (converlstlen == 2) {
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
        void setCurrentAvg(QList<QStringList> CharaPicList, int Charanum, bool BGBlack) {
            if (BGBlack) {
                OPFrame->setOpacity(1);
            }else {
                OPFrame->setOpacity(0);
                NameLabel->setText("");
                WordLabel->setText("");
                AVG_L->setPixmap(QPixmap(""));
                AVG_M->setPixmap(QPixmap(""));
                AVG_R->setPixmap(QPixmap(""));
            }

            if (Charanum == 1) {
                for (int a = 0; a < CharaPicList.length(); a++) {
                    QStringList i = CharaPicList[a];
                    if (i[0] == "") {
                        AVG_L->setPixmap(QPixmap(""));
                        AVG_M->setPixmap(QPixmap(""));
                        AVG_R->setPixmap(QPixmap(""));
                    }else {
                        AVG_L->setPixmap(QPixmap(""));
                        AVG_R->setPixmap(QPixmap(""));
                        if (i[6] == "(暗，沉默)") {
                            AVG_M_R.load("./Visual/cache/Chara/" + i[0] + "_" + i[1] + "_" + i[3] + "-Dark.png");
                        }else if (i[3] != "0") {
                            AVG_M_R.load("./Visual/cache/Chara/" + i[0] + "_" + i[1] + "_" + i[3] + ".png");
                        }else {
                            AVG_M_R.load("./Visual/source/Chara/" + i[0] + "_" + i[1] + ".png");
                        }
                        AVG_M_R = AVG_M_R.scaled(gX * 0.74635, gX * 0.74635, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                        if (*(AVG_M->pixmap()) != QPixmap::fromImage(AVG_M_R)) {
                            if (i[2] == "0") { AVG_M->setPixmap(QPixmap::fromImage(AVG_M_R)); }
                            else if (i[2] == "1") { AVG_M->setPixmap(QPixmap::fromImage(AVG_M_R.mirrored(TRUE, FALSE))); }
                        }
                    }
                }
            }
            else if (Charanum == 2) {
                AVG_M->setPixmap(QPixmap(""));
                if (CharaPicList[0][0] != "") {
                    if (CharaPicList[0][6] == "(暗，沉默)") {
                        AVG_L_R.load("./Visual/cache/Chara/" + CharaPicList[0][0] + "_" + CharaPicList[0][1] + "_" + CharaPicList[0][3] + "-Dark.png");
                    }else if (CharaPicList[0][3] != "0") {
                        AVG_L_R.load("./Visual/cache/Chara/" + CharaPicList[0][0] + "_" + CharaPicList[0][1] + "_" + CharaPicList[0][3] + ".png");
                    }else {
                        AVG_L_R.load("./Visual/source/Chara/" + CharaPicList[0][0] + "_" + CharaPicList[0][1] + ".png");
                    }
                    AVG_L_R=AVG_L_R.scaled(gX*0.74635,gX*0.74635, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    if (*(AVG_L->pixmap()) != QPixmap::fromImage(AVG_L_R)) {
                        if (CharaPicList[0][2] == "0") { AVG_L->setPixmap(QPixmap::fromImage(AVG_L_R)); }
                        else if (CharaPicList[0][2] == "1") { AVG_L->setPixmap(QPixmap::fromImage(AVG_L_R.mirrored(TRUE, FALSE))); }
                    }
                }
                if (CharaPicList[1][0] != "") {
                    if (CharaPicList[1][6] == "(暗，沉默)") {
                        AVG_R_R.load("./Visual/cache/Chara/" + CharaPicList[1][0] + "_" + CharaPicList[1][1] + "_" + CharaPicList[1][3] + "-Dark.png");
                    }else if (CharaPicList[1][3] != "0") {
                        AVG_R_R.load("./Visual/cache/Chara/" + CharaPicList[1][0] + "_" + CharaPicList[1][1] + "_" + CharaPicList[1][3] + ".png");
                    }else {
                        AVG_R_R.load("./Visual/source/Chara/" + CharaPicList[1][0] + "_" + CharaPicList[1][1] + ".png");
                    }
                    AVG_R_R = AVG_R_R.scaled(gX * 0.74635, gX * 0.74635, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                    if (*(AVG_R->pixmap()) != QPixmap::fromImage(AVG_R_R)) {
                        if (CharaPicList[1][2] == "0") { AVG_R->setPixmap(QPixmap::fromImage(AVG_R_R)); }
                        else if (CharaPicList[1][2] == "1") { AVG_R->setPixmap(QPixmap::fromImage(AVG_R_R.mirrored(TRUE, FALSE))); }
                    }
                }
            }
        }
        void updateCurrentWords(QStringList i_List, QString WordsCurrent, int Charanum, QStringList Wordset) {
            if (i_List[0] == "" && Charanum == 1) {
                NameLabel->setText("");
                WordLabel->setText(WordsCurrent);
            }else if (i_List[1] == "" && Charanum == 1) {
                NameLabel->setText(i_List[0]);
                WordLabel->setText("");
            }else if ((i_List[0] != "" && i_List[1] != "") || (i_List[0] != "" && Charanum == 1)) {
                if (NameLabel->text() != i_List[0]) {
                    NameLabel->setText(i_List[0]);
                }
                WordLabel->setText(WordsCurrent);
            }
        }
        void setCurrentBGP(QStringList BGPSetList) {
            if (BGPSetList[0] == "黑场") {
                BGR = QImage(gX, gY, QImage::Format_ARGB32);
                BGR.fill(QColor(0, 0, 0, 255));
            }else{
                if (BGPSetList[1] == "0") {
                    BGR.load("./Visual/source/BGP/" + BGPSetList[0] + ".png");
                    BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                }else if (BGPSetList[1] == "1"){
                    BGR.load("./Visual/cache/BGP/" + BGPSetList[0] + "-Dark.png");
                    BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                }else if (BGPSetList[1] == "2"){
                    BGR.load("./Visual/cache/BGP/" + BGPSetList[0] + "-Fade.png");
                    BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                }else if (BGPSetList[1] == "3"){
                    BGR.load("./Visual/cache/BGP/" + BGPSetList[0] + "-Fade-Dark.png");
                    BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                }else if (BGPSetList[1] == "4"){
                    BGR.load("./Visual/cache/BGP/" + BGPSetList[0] + "-BAW.png");
                    BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                }else if (BGPSetList[1] == "5") {
                    BGR.load("./Visual/cache/BGP/" + BGPSetList[0] + "-BAW-Dark.png");
                    BGR = BGR.scaled(gX, gY, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
                }
            }
        }
        void updateCurrentBGP(float Opacity_Float, QStringList BGSetList) {
            if (changeBG == 1) {
                if (Opacity_Float == 0) {
                    BG1->setPixmap(QPixmap::fromImage(BGR));
                    OPBG1->setOpacity(0);
                }else if (Opacity_Float != 0 && Opacity_Float != 1) {
                    OPBG1->setOpacity(Opacity_Float);
                }else if (Opacity_Float >= 1) {
                    OPBG1->setOpacity(1);
                    changeBG = 2;
                }
            }else if (changeBG == 2) {
                if (Opacity_Float == 0) {
                    BG2->setPixmap(QPixmap::fromImage(BGR));
                    OPBG1->setOpacity(1);
                }else if (Opacity_Float != 0 && Opacity_Float != 1) {
                    OPBG1->setOpacity(1 - Opacity_Float);
                }else if (Opacity_Float >= 1) {
                    OPBG1->setOpacity(0);
                    changeBG = 1;
                }
            }

            if (BGSetList[2] == "1") {
                ShakeFUNC = new ShakeFunc(SpeedFloat);
                connect(ShakeFUNC, SIGNAL(shakeXY(int, int, int)), this, SLOT(_ShakeRect(int, int, int)));
                ShakeFUNC->start();
            }else if (BGSetList[2] == "2") {
                effectuse = 2;
                FlashFUNCFast = new FlashFuncFast(SpeedFloat);
                connect(FlashFUNCFast, SIGNAL(FlashOPint(float, int)), this, SLOT(_FlashWhite(float, int)));
                FlashFUNCFast->start();
            }else if (BGSetList[2] == "3") {
                effectuse = 3;
                FlashFUNCSlow = new FlashFuncSlow(SpeedFloat);
                connect(FlashFUNCSlow, SIGNAL(FlashOPint(float, int)), this, SLOT(_FlashWhite(float, int)));
                FlashFUNCSlow->start();
            }else{
                showNext();
            }
        }
        void setCurrentFree(QStringList textsetlst, QStringList wordset) {
            FreeLabel->setText("");
            OPFreeLabel->setOpacity(0);
            FreeLabel->setGeometry(QRect(gX * textsetlst[0].toFloat(), gY * textsetlst[1].toFloat(), gX * 0.75, gY * 0.0324074));
            if (textsetlst[2] == "L") {
                FreeLabel->setAlignment(Qt::AlignLeft);
            }else if (textsetlst[2] == "M") {
                FreeLabel->setAlignment(Qt::AlignCenter);
            }else if (textsetlst[2] == "R") {
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
    public slots:
        void _ShakeRect(int sX, int sY, int end) {
            if (changeBG == 2) {
                BG1->setGeometry(QRect((int)(gY / 1080) * sX, (int)(gY / 1080) * sY, gX, gY));
                BG1->repaint();
            }else if (changeBG == 1) {
                BG2->setGeometry(QRect((int)(gY / 1080) * sX, (int)(gY / 1080) * sY, gX, gY));
                BG2->repaint();
            }
            if (end == 1) {
                delete ShakeFUNC;
                showNext();
            }
        }
        void _FlashWhite(float Opacity_Float, int end) {
            if (end == 0) {
                OPWhiteFlash->setOpacity(0);
            }else if (end == 1) {
                OPWhiteFlash->setOpacity(Opacity_Float);
                WhiteFlash->repaint();
            }else if (end == 2) {
                OPWhiteFlash->setOpacity(0);
                if (effectuse == 2) {
                    FlashFUNCFast->wait();
                    delete FlashFUNCFast;
                    effectuse = 0;
                }else if (effectuse == 3) {
                    FlashFUNCSlow->wait();
                    delete FlashFUNCSlow;
                    effectuse = 0;
                }
            }
        }
        void _AutoChange(void) {
            if (Auto) {
                Auto = FALSE;
                AutoButton->setText(msg("Ui_AutoButton_Auto_Off"));
            }else {
                Auto = TRUE;
                AutoButton->setText(msg("Ui_AutoButton_Auto"));
            }
        }

        void repaintAutoButton(void) {
            if (Auto) {
                if (AutoButtonTick == 0) { 
                    AutoButton->setText(msg("Ui_AutoButton_Auto") + ""); 
                    AutoButtonTick += 1;
                }else if (AutoButtonTick == 1) {
                    AutoButton->setText(msg("Ui_AutoButton_Auto") + "▶");
                    AutoButtonTick += 1;
                }else if (AutoButtonTick == 1) {
                    AutoButton->setText(msg("Ui_AutoButton_Auto") + "▶▶");
                    AutoButtonTick += 1;
                }else if (AutoButtonTick == 1) {
                    AutoButton->setText(msg("Ui_AutoButton_Auto") + "▶▶▶");
                    AutoButtonTick += 1;
                }
            }
        }

        void _SpeedChange(void) {
            SpeedNow += 1;
            if (SpeedNow % 4 == 1) {
                emit UserSpeedSet("0.666");
                SpeedButton->setText("1.5x");
                SpeedFloat = 0.666;
            }else if (SpeedNow % 4 == 2) {
                emit UserSpeedSet("0.5");
                SpeedButton->setText("2.0x");
                SpeedFloat = 0.5;
            }else if (SpeedNow % 4 == 3) {
                emit UserSpeedSet("2");
                SpeedButton->setText("0.5x");
                SpeedFloat = 2;
            }else if (SpeedNow % 4 == 4) {
                emit UserSpeedSet("1");
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
            showNext();
        }

        void showNext(void) {
            if (Auto) {
                emit NeedWakeUp();
            }else {
                NextButton->setGeometry(QRect(gX * 0.902604, gY * 0.8981, gX * 0.078125, gY * 0.046296));
            }
        }
        void _ToNext(void) {
            emit NeedWakeUp();
            NextButton->setGeometry(QRect(-gX * 0.902604, -gY * 0.8981, gX * 0.078125, gY * 0.046296));
        }
        void showLogPage(void) {
            if (!InLogPage) {
                emit NowInLog();
                if (Auto) {
                    _AutoChange();
                    }
                LogPage->setGeometry(QRect(0, 0, gX, gY));
                InLogPage = TRUE;
            }else {
                if (!Auto) {
                    _AutoChange();
                }
                if (NextButton->geometry() == QRect(-gX, -gY, gX, gY)) {
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
        uSoundService() {   
        }
        void loadFile(QString Filename, int Volume) {
            MediaPlayer = new QMediaPlayer();
            MediaPlayer->setMedia(QMediaContent(QUrl::fromLocalFile(Filename)));
            MediaPlayer->setVolume(Volume);
        }
        void playMedia(void) {
            MediaPlayer->play();
        }
        void fadeMedia(void) {
            for (int i = MediaPlayer->volume(); i > 0; i--) {
                MediaPlayer->setVolume(i);
                Sleep(10);
            }
            MediaPlayer->stop();
            this->deleteLater();
        }
       
};