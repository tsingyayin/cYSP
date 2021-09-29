#pragma once
#include "..\langcontrol.h"
#include "..\global_value.h"
#include "..\loadsettings.h"
#include "ProgramSettings.h"
#include "..\Aaspcommand\aaspcommand.h"
#include "SPOLDev.h"
#include <math.h>
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <ctype.h>
using namespace std;

static QString urlGithub = "https://github.com/tsingyayin/YSP-Yayin_Story_Player";
static QString urlAFD = "https://afdian.net/@ysp_Dev?tab=home";

//GCP对话框
class hGCPDialog :public QWidget
{
    Q_OBJECT
    signals:
        void chooseEnd(void);
    public:
        QPushButton* YesButton;
        QPushButton* NoButton;
        QLabel* EnableGCPDialogLabel;

        QFrame* frame;
        QHBoxLayout* hl;
        QGraphicsDropShadowEffect* SelfEffect;
        hGCPDialog(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(500, 400, 900, 300));
            this->setWindowFlags(Qt::FramelessWindowHint);
            this->setAttribute(Qt::WA_TranslucentBackground);
            this->setAttribute(Qt::WA_DeleteOnClose);
            frame = new QFrame();
            hl = new QHBoxLayout();
            hl->setContentsMargins(10, 10, 10, 10);
            SelfEffect = new QGraphicsDropShadowEffect();
            SelfEffect->setOffset(4, 4);
            SelfEffect->setColor(QColor(0, 0, 0, 127));
            SelfEffect->setBlurRadius(15);
            frame->setGraphicsEffect(SelfEffect);
            hl->addWidget(frame);
            this->setLayout(hl);

            this->setStyleSheet(
                "QWidget{"
                "background-color:rgba(230,230,230,230);"
                "border:1px solid rgb(15,77,240);"
                "border-radius:10px;"
                "}");
            EnableGCPDialogLabel = new QLabel(this);
            EnableGCPDialogLabel->setText(msg("Ui_Msg_EnsureGCPMode"));
            EnableGCPDialogLabel->setGeometry(QRect(50, 80, 800, 40));
            EnableGCPDialogLabel->setAlignment(Qt::AlignCenter);
            EnableGCPDialogLabel->setStyleSheet("\
                QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#BB0000;\
                    font-family:'Microsoft YaHei';\
                    font-size:25px;\
                    }");
            YesButton = new QPushButton(this);
            YesButton->setText(msg("Ui_Msg_Yes"));
            YesButton->setGeometry(QRect(50, 190, 350, 50));
            YesButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,220,220,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    border:1px solid rgb(228, 39, 44); \
                }\
                QPushButton:hover{\
                    color:#FFFFFF;\
                    background-color:rgba(255,230,230,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                    border:1px solid rgb(228, 39, 44); \
                }\
                QPushButton:Pressed{\
                    color:#FF0000;\
                    background-color:rgba(240,200,200,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    border:1px solid rgb(228, 39, 44); \
                    }");
            NoButton = new QPushButton(this);
            NoButton->setText(msg("Ui_Msg_Back"));
            NoButton->setGeometry(QRect(500, 190, 350, 50));
            NoButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,200);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                    QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                    QPushButton:pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
            connect(YesButton, SIGNAL(clicked()), this, SLOT(yesclose()));
            connect(NoButton, SIGNAL(clicked()), this, SLOT(noclose()));
        }
        void mousePressEvent(QMouseEvent * event) {
                QWidget* pWindow = this->window();
                ReleaseCapture();
                SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
                event->ignore();
        }
    public slots:
        void yesclose(void) {     
            writesettings("GCPMode", "True");
            emit chooseEnd();
            close();
        }
        void noclose(void) {
            emit chooseEnd();
            close();
        }
};

//更新页面对话框
class hUpdateDialog :public QWidget
{
    Q_OBJECT
    signals:
        void windowIsClosed(void);
    public:
        QFrame* frame;
        QHBoxLayout* hl;
        QGraphicsDropShadowEffect* SelfEffect;
        QLabel* OopsLabel;
        QLabel* NewVersionLabel;
        QLabel* UpdateInfoLabel;
        QPushButton* BackButton;
        QString Preurl="https://pan.baidu.com/s/1P2HXW0Y5G4piA7XUKXWWzg";
        QString Puburl="https://pan.baidu.com/s/1Zo_lZzEjpIaEsM4LdCohYQ";
        QString gVersionName;
        QString gDialogLink;
        int gX, gY;
        hUpdateDialog(int X, int Y, QString VersionName,QString DialogLink,QWidget* parent = Q_NULLPTR) {
            gVersionName = VersionName;
            gDialogLink = DialogLink;
            this->setParent(parent);
            this->setGeometry(QRect(500, 400, 900, 300));
            this->setWindowFlags(Qt::FramelessWindowHint);
            this->setAttribute(Qt::WA_TranslucentBackground);
            this->setAttribute(Qt::WA_DeleteOnClose);
            frame = new QFrame();
            hl = new QHBoxLayout();
            hl->setContentsMargins(10, 10, 10, 10);
            SelfEffect = new QGraphicsDropShadowEffect();
            SelfEffect->setOffset(4, 4);
            SelfEffect->setColor(QColor(0, 0, 0, 127));
            SelfEffect->setBlurRadius(15);
            frame->setGraphicsEffect(SelfEffect);
            hl->addWidget(frame);
            this->setLayout(hl);

            this->setStyleSheet(
                "QWidget{"
                "background-color:rgba(230,230,230,230);"
                "border:1px solid rgb(100,100,100);"
                "border-radius:10px;"
                "}");

            OopsLabel = new QLabel(this);
            OopsLabel->setText(msg("Ui_Msg_Can_Update")+"UYXA");
            OopsLabel->setGeometry(QRect(50, 50, 800, 40));
            OopsLabel->setAlignment(Qt::AlignCenter);
            OopsLabel->setStyleSheet("\
                QLabel{\
                background-color:rgba(255, 255, 255, 0);\
                border:none;\
                border-radius:0px;\
                color:#4488FF;\
                font-family:'Microsoft YaHei';\
                font-size:30px;\
                }");
            
            NewVersionLabel = new QLabel(this);
            if (VersionName.contains("Pre")) {
                NewVersionLabel->setText("<A href='" + Preurl + "'>" + VersionName + "</a>");
            }
            else {
                NewVersionLabel->setText("<A href='" + Puburl + "'>" + VersionName + "</a>");
            }
            NewVersionLabel->setOpenExternalLinks(TRUE);
            NewVersionLabel->setGeometry(QRect(50, 120, 800, 40));
            NewVersionLabel->setAlignment(Qt::AlignCenter);
            NewVersionLabel->setStyleSheet("\
                QLabel{\
                background-color:rgba(255, 255, 255, 0);\
                border:none;\
                border-radius:0px;\
                color:#000000;\
                font-family:'Microsoft YaHei';\
                font-size:20px;\
                }");

            BackButton = new QPushButton(this);
            BackButton->setGeometry(QRect(50, 180, 800, 50));
            BackButton->setText(msg("Ui_Msg_Back"));
            BackButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,220,220,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#FFFFFF;\
                    background-color:rgba(255,230,230,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#FF0000;\
                    background-color:rgba(240,200,200,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }");
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(close()));

            UpdateInfoLabel = new QLabel(this);
            UpdateInfoLabel->setGeometry(QRect(50, 250, 800, 30));
            UpdateInfoLabel->setAlignment(Qt::AlignCenter);
            UpdateInfoLabel->setStyleSheet("\
                QLabel{\
                background-color:rgba(255, 255, 255, 0);\
                border:none;\
                border-radius:0px;\
                color:#CC2211;\
                font-family:'Microsoft YaHei';\
                font-size:20px;\
                }");
            if (DialogLink != "NONELINK") {
                UpdateInfoLabel->setOpenExternalLinks(TRUE);
                UpdateInfoLabel->setText("<A href='" + DialogLink + "'>" + msg("Ui_Msg_Update_Log") + "</a>");
            }
            else {
                UpdateInfoLabel->setOpenExternalLinks(FALSE);
                UpdateInfoLabel->setText(msg("Ui_Msg_Update_Log_N"));
            }
        }
        void UpdateLang(void) {
            OopsLabel->setText(msg("Ui_Msg_Can_Update") + "UYXA");
            if (gVersionName.contains("Pre")) {
                NewVersionLabel->setText("<A href='" + Preurl + "'>" + gVersionName + "</a>");
            }
            else {
                NewVersionLabel->setText("<A href='" + Puburl + "'>" + gVersionName + "</a>");
            }
            BackButton->setText(msg("Ui_Msg_Back"));
            if (gDialogLink != "NONELINK") {
                UpdateInfoLabel->setOpenExternalLinks(TRUE);
                UpdateInfoLabel->setText("<A href='" + gDialogLink + "'>" + msg("Ui_Msg_Update_Log") + "</a>");
            }
            else {
                UpdateInfoLabel->setOpenExternalLinks(FALSE);
                UpdateInfoLabel->setText(msg("Ui_Msg_Update_Log_N"));
            }
        }
        void closeEvent(QCloseEvent* event) {
            emit windowIsClosed();
        }
};

//首页定义（不含图标和大标题）
class hFirstPage :public QWidget
{

	Q_OBJECT
	public:
        
        QPushButton* UIModeButton;
        QPushButton* ToolsButton;
        QPushButton* CreateButton;
        QPushButton* SettingsButton;
        QPushButton* ExitButton;
        
        QGraphicsOpacityEffect* OPUIModeButton;
        QGraphicsOpacityEffect* OPToolsButton;
        QGraphicsOpacityEffect* OPCreateButton;
        QGraphicsOpacityEffect* OPSettingsButton;
        QGraphicsOpacityEffect* OPExitButton;

        
		hFirstPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            
            UIModeButton = new QPushButton(this);
            UIModeButton->setGeometry(QRect(50, 350, 600, 50));
            UIModeButton->setText(msg("Ui_Msg_LaunchUI"));
            UIModeButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,200);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                    QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                    QPushButton:pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            ToolsButton = new QPushButton(this);
            ToolsButton->setGeometry(QRect(390, 420, 260, 50));
            ToolsButton->setText(msg("Ui_Msg_Tools"));
            ToolsButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,200);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            CreateButton = new QPushButton(this);
            CreateButton->setGeometry(QRect(50, 420, 260, 50));
            CreateButton->setText(msg("Ui_Msg_Create"));
            CreateButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255, 255, 255, 200);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                    QPushButton:pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
            SettingsButton = new QPushButton(this);
            SettingsButton->setGeometry(QRect(50, 490, 600, 50));
            SettingsButton->setText(msg("Ui_Msg_Settings"));
            SettingsButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
            ExitButton = new QPushButton(this);
            ExitButton->setGeometry(QRect(50, 560, 260, 50));
            ExitButton->setText(msg("Ui_Msg_Exit"));
            ExitButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
            /*
            SelfEffect = new QGraphicsDropShadowEffect();
            SelfEffect->setOffset(4, 4);
            SelfEffect->setColor(QColor(0, 0, 0, 30));
            SelfEffect->setBlurRadius(15);
            this->setGraphicsEffect(SelfEffect);
            */
		}
        
        //void setOpacity(float OpacityFloat) {
            
        //}
};

//程序播放设定
class hPlayerSettings :public QWidget
{
    Q_OBJECT
    public:
        int gX, gY;
        QLabel Text_SetGeometry;
        QComboBox Edit_SetGeometry;
        QPushButton* Choose_Full_Or_Not;
        hPlayerSettings(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            gX = X;
            gY = Y;
        }
};

//设定页定义
class hSettingsPage :public QWidget
{
    Q_OBJECT
    public:
        QPushButton* AboutButton;
        QPushButton* LangButton;
        QPushButton* DevButton;
        QPushButton* PlayerButton;
        QPushButton* GCPButton;
        hGCPDialog* GCPDialog;
        hDevSettings* DevPage;
        int gX=0, gY=0;
        hSettingsPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            gX = X;
            gY = Y;
            AboutButton = new QPushButton(this);
            AboutButton->setGeometry(QRect(50,420,260,50));
            AboutButton->setText(msg("Ui_Msg_About_"));
            AboutButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            LangButton = new QPushButton(this);
            LangButton->setGeometry(QRect(390,420,260,50));
            LangButton->setText(msg("Ui_Msg_Choose_Lang"));
            LangButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            PlayerButton = new QPushButton(this);
            PlayerButton->setText("播放设置");
            PlayerButton->setGeometry(QRect(50,350,260,50));
            PlayerButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            DevButton = new QPushButton(this);
            DevButton->setText("高级设定");
            DevButton->setGeometry(QRect(390, 350, 260, 50));
            DevButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            GCPButton = new QPushButton(this);
            GCPButton->setGeometry(QRect(50, 490, 260, 50));
            if (Program_Settings("GCPMode") == "True") {
                GCPButton->setText(msg("Ui_Msg_CloseGCPMode"));
            }else {
                GCPButton->setText(msg("Ui_Msg_OpenGCPMode"));
            }
            GCPButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
        }
    public slots:
        void showGCPDialog(void) {
            if (Program_Settings("GCPMode") == "True") {
                writesettings("GCPMode", "False");
                GCPButton->setText(msg("Ui_Msg_OpenGCPMode"));
            }
            else {
                GCPDialog = new hGCPDialog(gX, gY);
                GCPDialog->show();
                connect(GCPDialog, SIGNAL(chooseEnd()), this, SLOT(repaintMsg()));
            }
        }
        void showDevSetPage(void) {
            DevPage = new hDevSettings(gX, gY);
            DevPage->show(); 
        }
        void repaintMsg(void){
            if (Program_Settings("GCPMode") == "True") {
                GCPButton->setText(msg("Ui_Msg_CloseGCPMode"));
            }
            else {
                GCPButton->setText(msg("Ui_Msg_OpenGCPMode"));
            }
            
        }
};

//工具页面定义
class hToolsPage :public QWidget
{
    Q_OBJECT
    public:
        QPushButton* ToSpolButton;
        QPushButton* ClrWrongButton;
        QPushButton* ClrCacheButton;
        int gX, gY;
        hToolsPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            gX = X;
            gY = Y;

            ToSpolButton = new QPushButton(this);
            ToSpolButton->setGeometry(QRect(390,420,260,50));
            ToSpolButton->setText(msg("Ui_Msg_To_Spol"));
            ToSpolButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            ClrWrongButton = new QPushButton(this);
            ClrWrongButton->setGeometry(QRect(50,350,260,50));
            ClrWrongButton->setText(msg("Ui_Msg_Clear_Wrong"));
            ClrWrongButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            ClrCacheButton = new QPushButton(this);
            ClrCacheButton->setGeometry(QRect(390,350,260,50));
            ClrCacheButton->setText(msg("Ui_Msg_Clear_All"));
            ClrCacheButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

        }
};

//创作页面定义
class hCreatePage :public QWidget
{
    Q_OBJECT
    public:
        int gX, gY;
        QPushButton* OpenButton_Cache;
        QPushButton* OpenButton_Source;
        QPushButton* OpenButton_Story;
        QPushButton* OpenButton_Official;
        QPushButton* SPOLDevButton;
        SPOLDevWindow* DevWindow;
        hCreatePage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            gX = X;
            gY = Y;
            OpenButton_Cache= new QPushButton(this);
            OpenButton_Cache->setGeometry(QRect(50,280,260,50));
            OpenButton_Cache->setText(msg("Ui_Msg_Open_Cache"));
            OpenButton_Cache->setObjectName("OpenButton_Cache");
            OpenButton_Cache->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            OpenButton_Source= new QPushButton(this);
            OpenButton_Source->setGeometry(QRect(50,350,260,50));
            OpenButton_Source->setText(msg("Ui_Msg_Open_Source"));
            OpenButton_Source->setObjectName("OpenButton_Source");
            OpenButton_Source->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            OpenButton_Story= new QPushButton(this);
            OpenButton_Story->setGeometry(QRect(50,420,260,50));
            OpenButton_Story->setText(msg("Ui_Msg_Open_Story"));
            OpenButton_Story->setObjectName("OpenButton_Story");
            OpenButton_Story->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            OpenButton_Official= new QPushButton(this);
            OpenButton_Official->setGeometry(QRect(50,490,260,50));
            OpenButton_Official->setText(msg("Ui_Msg_Open_Official"));
            OpenButton_Official->setObjectName("OpenButton_Official");
            OpenButton_Official->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
            SPOLDevButton= new QPushButton(this);
            SPOLDevButton->setGeometry(QRect(390, 280, 260, 50));
            SPOLDevButton->setText(msg("Ui_Msg_SPOLDev"));
            SPOLDevButton->setObjectName("SPOLDevButton");
            SPOLDevButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
        }
    public slots:
        void showSPOLDevWindow(void) {
            DevWindow = new SPOLDevWindow();
            DevWindow->show();
        }
};

//关于页定义
class hAboutPage :public QWidget
{
    Q_OBJECT
    public:
        QLabel* AboutLabel_FullVer;
        QLabel* AboutLabel_MainVer;
        QLabel* AboutLabel_SubVer;
        QLabel* AboutLabel_BuildVer;
        QLabel* AboutLabel_SpolVer;
        QLabel* AboutLabel_SpolEnvVer;
        QLabel* AboutLabel_Developers;
        QLabel* AboutLabel_Support;
        QLabel* AboutLabel_Donate;
        QPushButton* MoreAboutInfo;
        QPushButton* CheckUpdateButton;
        hMoreInfo* MoreInfoPage;
        int gX, gY;
        hAboutPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            gX = X;
            gY = Y;
            AboutLabel_FullVer = new QLabel(this);
            AboutLabel_FullVer->setText(Program_Info("Edition"));
            AboutLabel_FullVer->setGeometry(QRect(25,280,650,30));
            AboutLabel_FullVer->setAlignment(Qt::AlignCenter);
            AboutLabel_FullVer->setStyleSheet("\
                QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            AboutLabel_MainVer = new QLabel(this);
            AboutLabel_MainVer->setText(msg("About_Info_Main_Ver") + Program_Info("Main"));
            AboutLabel_MainVer->setGeometry(QRect(60,320,300,30));
            AboutLabel_MainVer->setAlignment(Qt::AlignLeft);
            AboutLabel_MainVer->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            AboutLabel_SubVer= new QLabel(this);
            AboutLabel_SubVer->setText(msg("About_Info_Sub_Ver") + Program_Info("Sub"));
            AboutLabel_SubVer->setGeometry(QRect(360,320,300,30));
            AboutLabel_SubVer->setAlignment(Qt::AlignLeft);
            AboutLabel_SubVer->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            AboutLabel_BuildVer= new QLabel(this);
            AboutLabel_BuildVer->setText(msg("About_Info_Build_Ver") + Program_Info("Build"));
            AboutLabel_BuildVer->setGeometry(QRect(60,360,300,30));
            AboutLabel_BuildVer->setAlignment(Qt::AlignLeft);
            AboutLabel_BuildVer->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            AboutLabel_SpolVer= new QLabel(this);
            AboutLabel_SpolVer->setText(msg("About_Info_Spol_Ver") + Program_Info("SPOL"));
            AboutLabel_SpolVer->setGeometry(QRect(360,360,300,30));
            AboutLabel_SpolVer->setAlignment(Qt::AlignLeft);
            AboutLabel_SpolVer->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            
            /*
            AboutLabel_SpolEnvVer= new QLabel(this);
            AboutLabel_SpolEnvVer->setText(msg("About_Info_Spol_Env_Ver") + Program_Info("SPEnv"));
            AboutLabel_SpolEnvVer->setGeometry(QRect(60,400,650,30));
            AboutLabel_SpolEnvVer->setAlignment(Qt::AlignLeft);
            AboutLabel_SpolEnvVer->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            AboutLabel_Developers= new QLabel(this);
            AboutLabel_Developers->setText(msg("About_Info_Developers") + Program_Info("Developer"));
            AboutLabel_Developers->setGeometry(QRect(60,440,600,30));
            AboutLabel_Developers->setAlignment(Qt::AlignLeft);
            AboutLabel_Developers->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");
            */

            AboutLabel_Support= new QLabel(this);
            AboutLabel_Support->setText(msg("About_Info_Support") + "亿绪联合协会UYXA");
            AboutLabel_Support->setGeometry(QRect(60, 400, 600, 30));
            AboutLabel_Support->setAlignment(Qt::AlignLeft);
            AboutLabel_Support->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            AboutLabel_Donate= new QLabel(this);
            AboutLabel_Donate->setText(msg("About_Info_Donate").arg("<A href='"+urlAFD+"'>"+urlAFD+"</a>"));
            AboutLabel_Donate->setOpenExternalLinks(FALSE);
            AboutLabel_Donate->setGeometry(QRect(60, 440, 600, 30));
            AboutLabel_Donate->setAlignment(Qt::AlignLeft);
            AboutLabel_Donate->setStyleSheet("\
            QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:22px;\
                    }");

            MoreAboutInfo = new QPushButton(this);
            MoreAboutInfo->setText(msg("About_Info_More"));
            MoreAboutInfo->setGeometry(QRect(50, 490, 600, 50));
            MoreAboutInfo->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");

            CheckUpdateButton= new QPushButton(this);
            CheckUpdateButton->setGeometry(QRect(50,560,260,50));
            CheckUpdateButton->setText(msg("Ui_Msg_Check_Update"));
            CheckUpdateButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,255,255,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:hover{\
                    color:#888888;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                }\
                QPushButton:Pressed{\
                    color:#66ccff;\
                    background-color:rgba(255,255,255,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    }");
        }
        public slots:
            void showMoreInfoPage(void) {
                MoreInfoPage = new hMoreInfo(gX, gY);
                MoreInfoPage->show();
            }
};

//交互窗口控件总定义
class TopDef :public QWidget
{
	Q_OBJECT
	public:
		QDesktopWidget* desktop;
		QFrame* frame;
		QHBoxLayout* hl;
		QGraphicsDropShadowEffect* SelfEffect;
        hFirstPage* FirstPage;
        QGraphicsOpacityEffect* OPFirstPage;
        hToolsPage* ToolsPage;
        QGraphicsOpacityEffect* OPToolsPage;
        hCreatePage* CreatePage;
        QGraphicsOpacityEffect* OPCreatePage;
        hSettingsPage* SettingsPage;
        QGraphicsOpacityEffect* OPSettingsPage;
        hAboutPage* AboutPage;
        QGraphicsOpacityEffect* OPAboutPage;
        hDevSettings* DevSetPage;
        QGraphicsOpacityEffect* OPDevSetPage;
        QPushButton* BackButton;
        QGraphicsDropShadowEffect* SABackButton;
        
        hUpdateDialog* UpdateDialog;
        
        QLabel* Titlelabel;
        QLabel* Iconlabel;
        QLabel* AnyInfolabel;
        QImage LogoRaw;
        QGraphicsOpacityEffect* OPTitlelabel;
        QGraphicsOpacityEffect* OPIconlabel;
        QGraphicsOpacityEffect* OPAnyInfolabel;

		int X,  Y;
		void setupUI() {
			desktop = new QDesktopWidget();
			int Current_monitor = desktop->screenNumber();
			QRect Display = desktop->screenGeometry(Current_monitor);
			X = Display.width();
			Y = Display.height();

            //基本圆角框架和半透明效果实现
            this->setGeometry(QRect(600, 400, 700, 300));
			this->setWindowFlags(Qt::FramelessWindowHint);
			this->setAttribute(Qt::WA_TranslucentBackground);

			frame = new QFrame();
			hl = new QHBoxLayout();
			hl->setContentsMargins(10, 10, 10, 10);
            SelfEffect = new QGraphicsDropShadowEffect();
			SelfEffect->setOffset(4, 4);
			SelfEffect->setColor(QColor(0, 0, 0, 127));
			SelfEffect->setBlurRadius(15);
            frame->setGraphicsEffect(SelfEffect);
            hl->addWidget(frame);
            this->setLayout(hl);

            this->setStyleSheet(
				"QWidget{"
					"background-color:rgba(230,230,230,230);"
					"border:1px solid rgb(100,100,100);"
					"border-radius:10px;"
					"}");
               
            AnyInfolabel = new QLabel(this);
            AnyInfolabel->setText("Default Text");
            AnyInfolabel->setStyleSheet("\
                QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    text-align:center;\
                    color:#4488FF;\
                    font-family:'Microsoft YaHei';\
                    font-size:30px;\
                    }");
            AnyInfolabel->setGeometry(QRect(50, 630, 600, 40));
            AnyInfolabel->setAlignment(Qt::AlignCenter);

            OPAnyInfolabel = new QGraphicsOpacityEffect();
            OPAnyInfolabel->setOpacity(0);
            AnyInfolabel->setGraphicsEffect(OPAnyInfolabel);

            AboutPage = new hAboutPage(X, Y, this);
            OPAboutPage = new QGraphicsOpacityEffect();
            OPAboutPage->setOpacity(0);
            AboutPage->setGraphicsEffect(OPAboutPage);

            CreatePage = new hCreatePage(X, Y, this);
            OPCreatePage = new QGraphicsOpacityEffect();
            OPCreatePage->setOpacity(0);
            CreatePage->setGraphicsEffect(OPCreatePage);

            ToolsPage = new hToolsPage(X, Y, this);
            OPToolsPage = new QGraphicsOpacityEffect();
            OPToolsPage->setOpacity(0);
            ToolsPage->setGraphicsEffect(OPToolsPage);

            SettingsPage = new hSettingsPage(X, Y, this);
            OPSettingsPage = new QGraphicsOpacityEffect();
            OPSettingsPage->setOpacity(0);
            SettingsPage->setGraphicsEffect(OPSettingsPage);

            FirstPage = new hFirstPage(X,Y,this);
            OPFirstPage = new QGraphicsOpacityEffect();
            OPFirstPage->setOpacity(0);
            FirstPage->setGraphicsEffect(OPFirstPage);

            Titlelabel = new QLabel(this);
            Titlelabel->setText(msg("Ui_Msg_Title"));
            Titlelabel->setStyleSheet("\
                QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#000000;\
                    font-family:'Microsoft YaHei';\
                    font-size:50px;\
                    }");
            Titlelabel->setGeometry(QRect(300, 100, 400, 100));
            Titlelabel->setAlignment(Qt::AlignCenter);
            OPTitlelabel = new QGraphicsOpacityEffect();
            OPTitlelabel->setOpacity(0.999);
            Titlelabel->setGraphicsEffect(OPTitlelabel);

            Iconlabel = new QLabel(this);
            Iconlabel->setGeometry(QRect(50, 15, 270, 270));
            LogoRaw.load("./Visual/source/BaseUI/Image/Videotape_Win11.png");
            LogoRaw = LogoRaw.scaled(270, 270, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            Iconlabel->setPixmap(QPixmap::fromImage(LogoRaw));
            Iconlabel->setStyleSheet("QLabel{background-color:rgba(255,255,255,0);border:none;border-radius:0px;}");
            OPIconlabel = new QGraphicsOpacityEffect();
            OPIconlabel->setOpacity(1);
            Iconlabel->setGraphicsEffect(OPIconlabel);

            BackButton = new QPushButton(this);
            BackButton->setGeometry(QRect(390, 560, 260, 50));
            BackButton->setText(msg("Ui_Msg_Back"));
            BackButton->setStyleSheet("\
                QPushButton{\
                    color:#333333;\
                    background-color:rgba(255,220,220,210);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    border:1px solid rgb(228,39,44); \
                }\
                QPushButton:hover{\
                    color:#FFFFFF;\
                    background-color:rgba(255,230,230,255);\
                    text-align:center;\
                    font-size:36px;\
                    font-family:'Microsoft YaHei';\
                    border:1px solid rgb(228,39,44); \
                }\
                QPushButton:Pressed{\
                    color:#FF0000;\
                    background-color:rgba(240,200,200,255);\
                    text-align:center;\
                    font-size:32px;\
                    font-family:'Microsoft YaHei';\
                    border:1px solid rgb(228,39,44); \
                    }");

		}
};

//交互窗口功能总定义
class TopWindow :public TopDef
{
	Q_OBJECT
	public:
		int FirstEnter = 0;
        hServiceFramework* Service;
        bool UpdateDialogWindowIsShow = FALSE;
        bool GCPDialogWindowIsShow = FALSE;
		TopWindow(QWidget* parent = Q_NULLPTR){
            this->setParent(parent);
            this->setWindowTitle("YSP "+Program_Info("Main"));
            this->setWindowIcon(QIcon("./Visual/source/WinICO/Videotape_Win11.ico"));
			setupUI();
            showFirstPage();
            Service = new hServiceFramework();

            connect(Service, SIGNAL(Anyinfo(int, QString)), this, SLOT(showAnyInfo(int, QString)));
		}
		void Expand() {
			double a;
			for (int i = 0; i <= 101; i += 2) {
				a = 0.5 * (1 - cos(i * 0.0314159));
				this->setGeometry(QRect(600, (int)(400 - a * 200), 700, (int)(300 + a * 350)));
                this->OPTitlelabel->setOpacity(1 - (float)i / 100);
                this->Iconlabel->setGeometry(QRect((int)(50 + 170 * a), 15, 270, 270));
				this->repaint();
				Sleep(1);
			}
		}
		void Shrink() {
			double a;
            QRect Rect = this->geometry();
			for (int i = 100; i >= -1; i -= 1) {
				a = 0.5 * (1 - cos(i * 0.0314159));
				this->setGeometry(QRect(Rect.left(), (int)(Rect.top() + 200 - a * 200), 700, (int)(300 + a * 350)));
                this->OPTitlelabel->setOpacity(1 - (float)i / 100);
                this->Iconlabel->setGeometry(QRect((int)(50 + 170 * a), 15, 270, 270));
				this->repaint();
				Sleep(1);
			}
		}
		void enterEvent(QEvent*) {
			if (FirstEnter == 0) {
				Expand();
				FirstEnter = 1;
                checkUpdate();
                this->BackButton->show();
			}
		}
        void mousePressEvent(QMouseEvent* event) {
            if (Iconlabel->underMouse()) {
                QWidget* pWindow = this->window();
                ReleaseCapture();
                SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
                event->ignore();
            }
        }
    public slots:
        void checkUpdate() {
            QStringList UpdateInfo = Service->ui_CheckUpdate();
            if (UpdateInfo[0] != "NODIALOG" && !UpdateDialogWindowIsShow) {
                UpdateDialog = new hUpdateDialog(X, Y, UpdateInfo[0], UpdateInfo[1]);
                UpdateDialog->show();
                UpdateDialogWindowIsShow = TRUE;
                connect(this->UpdateDialog, SIGNAL(windowIsClosed()), this, SLOT(updateDialogClosed()));
            }
        }
        void updateDialogClosed(void) {
            UpdateDialogWindowIsShow = FALSE;
        }
        void chooseLangFile(void) {
            QString LangFileDialog = QFileDialog::getOpenFileName(this,msg("Ui_Msg_Choose_Lang"), "./Language", "Story Player Language(*.splang)");
            QString LangFileName = LangFileDialog.section("/",-1,-1).section(".",0,0);
            Service->ui_langset(LangFileName);

            Titlelabel->setText(msg("Ui_Msg_Title"));
            BackButton->setText(msg("Ui_Msg_Back"));
            FirstPage->ExitButton->setText(msg("Ui_Msg_Exit"));
            FirstPage->ToolsButton->setText(msg("Ui_Msg_Tools"));
            FirstPage->SettingsButton->setText(msg("Ui_Msg_Settings"));
            FirstPage->UIModeButton->setText(msg("Ui_Msg_LaunchUI"));
            FirstPage->CreateButton->setText(msg("Ui_Msg_Create"));

            ToolsPage->ToSpolButton->setText(msg("Ui_Msg_To_Spol"));
            ToolsPage->ClrCacheButton->setText(msg("Ui_Msg_Clear_All"));
            ToolsPage->ClrWrongButton->setText(msg("Ui_Msg_Clear_Wrong"));

            SettingsPage->AboutButton->setText(msg("Ui_Msg_About_"));
            SettingsPage->LangButton->setText(msg("Ui_Msg_Choose_Lang"));
            if (Program_Settings("GCPMode") == "True") {
                SettingsPage->GCPButton->setText(msg("Ui_Msg_CloseGCPMode"));
            }else {
                SettingsPage->GCPButton->setText(msg("Ui_Msg_OpenGCPMode"));
            }   
            AboutPage->AboutLabel_FullVer->setText(Program_Info("Edition"));
            AboutPage->AboutLabel_MainVer->setText(msg("About_Info_Main_Ver") + Program_Info("Main"));
            AboutPage->AboutLabel_SubVer->setText(msg("About_Info_Sub_Ver") + Program_Info("Sub"));
            AboutPage->AboutLabel_BuildVer->setText(msg("About_Info_Build_Ver") + Program_Info("Build"));
            AboutPage->AboutLabel_SpolVer->setText(msg("About_Info_Spol_Ver") + Program_Info("SPOL"));
            //AboutPage->AboutLabel_SpolEnvVer->setText(msg("About_Info_Spol_Env_Ver") + Program_Info("SPEnv"));
            //AboutPage->AboutLabel_Developers->setText(msg("About_Info_Developers") + Program_Info("Developer"));
            AboutPage->AboutLabel_Support->setText(msg("About_Info_Support") + "亿绪联合协会UYXA");
            AboutPage->AboutLabel_Donate->setText(msg("About_Info_Donate").arg("<A href='" + urlAFD + "'>" + urlAFD + "</a>"));
            AboutPage->CheckUpdateButton->setText(msg("Ui_Msg_Check_Update"));

            CreatePage->OpenButton_Cache->setText(msg("Ui_Msg_Open_Cache"));
            CreatePage->OpenButton_Source->setText(msg("Ui_Msg_Open_Source"));
            CreatePage->OpenButton_Story->setText(msg("Ui_Msg_Open_Story"));
            CreatePage->OpenButton_Official->setText(msg("Ui_Msg_Open_Official"));

            if (UpdateDialogWindowIsShow) { UpdateDialog->UpdateLang(); };
        }
        void openAnyFolder(void) {
            QObject* OAFsourceButton=this->sender();
            if (OAFsourceButton->objectName() == "OpenButton_Cache") {
                Service->ui_OpenFolder(1);
            }elif (OAFsourceButton->objectName() == "OpenButton_Source") {
                Service->ui_OpenFolder(2);
            }elif(OAFsourceButton->objectName() == "OpenButton_Official") {
                Service->ui_OpenFolder(3);
            }elif(OAFsourceButton->objectName() == "OpenButton_Story") {
                Service->ui_OpenFolder(4);
            }
        }
        void clearWrongImage(void) {
            Service->ui_DeleteEmptyMap();
        }
        void clearAllCacheImage(void) {
            Service->ui_DeleteAllCache();
        }
        void showAnyInfo(int infoGroup = 2, QString needToShow = "UNKNOWN INFO") {
            float a = 0;
            QRect Rect = this->geometry();
            for (int i = 0; i <= 101; i += 4) {
                a = 0.5 * (1 - cos(i * 0.0314159));
                this->setGeometry(QRect(Rect.left(), Rect.top(), 700, (int)(650 + a * 50)));
                this->repaint();
                Sleep(3);
            }
            if (infoGroup == 0) {
                AnyInfolabel->setStyleSheet("\
                    QLabel{\
                        background-color:rgba(255,255,255,0);\
                        border:none;\
                        border-radius:0px;\
                        text-align:center;\
                        color:#000000;\
                        font-family:'Microsoft YaHei';\
                        font-size:30px;\
                        }");
            }else if (infoGroup == 1) {
                AnyInfolabel->setStyleSheet("\
                    QLabel{\
                        background-color:rgba(255,255,255,0);\
                        border:none;\
                        border-radius:0px;\
                        text-align:center;\
                        color:#4488FF;\
                        font-family:'Microsoft YaHei';\
                        font-size:30px;\
                        }");
            }else if (infoGroup == 2) {
                AnyInfolabel->setStyleSheet("\
                    QLabel{\
                        background-color:rgba(255,255,255,0);\
                        border:none;\
                        border-radius:0px;\
                        text-align:center;\
                        color:#CC2211;\
                        font-family:'Microsoft YaHei';\
                        font-size:30px;\
                        }");
            }
            AnyInfolabel->setText(needToShow);
            OPAnyInfolabel->setOpacity(1);
            AnyInfolabel->repaint();
            Sleep(1000);
            AnyInfolabel->setText("");
            OPAnyInfolabel->setOpacity(0);
            AnyInfolabel->repaint();
            a = 0;
            for (int i = 101; i >= 2; i -= 4) {
                a = 0.5 * (1 - cos(i * 0.0314159));
                this->setGeometry(QRect(Rect.left(), Rect.top(), 700, (int)(650 + a * 50)));
                this->repaint();
                Sleep(3);
            }
        }
        void showDevSetPage(void) {
            SettingsPage->showDevSetPage();
            this->hide();
            connect(this->SettingsPage->DevPage, SIGNAL(windowIsClosed()), this, SLOT(show()));
        }
        void showMoreInfoPage(void) {
            AboutPage->showMoreInfoPage();
            this->hide();
            connect(this->AboutPage->MoreInfoPage, SIGNAL(windowIsClosed()), this, SLOT(show()));
        }
        void showFirstPage(void) {
            OPFirstPage->setOpacity(1);
            FirstPage->raise();
            Iconlabel->raise();
            BackButton->raise();
            connect(this->FirstPage->UIModeButton, SIGNAL(clicked()), this, SLOT(launchUIPage()));
            connect(this->FirstPage->CreateButton, SIGNAL(clicked()), this, SLOT(showCreatePage()));
            connect(this->FirstPage->CreateButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            connect(this->FirstPage->ToolsButton, SIGNAL(clicked()), this, SLOT(showToolsPage()));
            connect(this->FirstPage->ToolsButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            connect(this->FirstPage->SettingsButton, SIGNAL(clicked()), this, SLOT(showSettingsPage()));
            connect(this->FirstPage->SettingsButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            
            connect(this->FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(exitPage()));
        }
        void hideFirstPage(void) {
            OPFirstPage->setOpacity(0);
            disconnect(this->FirstPage->UIModeButton, SIGNAL(clicked()), this, SLOT(launchUIPage()));
            disconnect(this->FirstPage->CreateButton, SIGNAL(clicked()), this, SLOT(showCreatePage()));
            disconnect(this->FirstPage->CreateButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            disconnect(this->FirstPage->ToolsButton, SIGNAL(clicked()), this, SLOT(showToolsPage()));
            disconnect(this->FirstPage->ToolsButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            disconnect(this->FirstPage->SettingsButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            disconnect(this->FirstPage->SettingsButton, SIGNAL(clicked()), this, SLOT(showSettingsPage()));
            disconnect(this->FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(exitPage()));
        }
        void showCreatePage(void) {
            OPCreatePage->setOpacity(1);
            CreatePage->raise();
            Iconlabel->raise();
            BackButton->raise();
            connect(this->CreatePage->SPOLDevButton, SIGNAL(clicked()), this->CreatePage, SLOT(showSPOLDevWindow()));
            connect(this->CreatePage->OpenButton_Story, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            connect(this->CreatePage->OpenButton_Cache, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            connect(this->CreatePage->OpenButton_Official, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            connect(this->CreatePage->OpenButton_Source, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideCreatePage()));
        }
        void hideCreatePage(void) {
            OPCreatePage->setOpacity(0);
            disconnect(this->CreatePage->SPOLDevButton, SIGNAL(clicked()), this->CreatePage, SLOT(showSPOLDevWindow()));
            disconnect(this->CreatePage->OpenButton_Story, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            disconnect(this->CreatePage->OpenButton_Cache, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            disconnect(this->CreatePage->OpenButton_Official, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            disconnect(this->CreatePage->OpenButton_Source, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideCreatePage()));
        }
        void showToolsPage(void) {
            OPToolsPage->setOpacity(1);
            ToolsPage->raise();
            Iconlabel->raise();
            BackButton->raise();
            connect(this->ToolsPage->ClrWrongButton, SIGNAL(clicked()), this, SLOT(clearWrongImage()));
            connect(this->ToolsPage->ClrCacheButton, SIGNAL(clicked()), this, SLOT(clearAllCacheImage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideToolsPage()));

        }
        void hideToolsPage(void) {
            OPToolsPage->setOpacity(0); 
            disconnect(this->ToolsPage->ClrWrongButton, SIGNAL(clicked()), this, SLOT(clearWrongImage()));
            disconnect(this->ToolsPage->ClrCacheButton, SIGNAL(clicked()), this, SLOT(clearAllCacheImage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideToolsPage()));
        }
        void showSettingsPage(void) {
            OPSettingsPage->setOpacity(1);
            SettingsPage->raise();
            Iconlabel->raise();
            BackButton->raise();
            connect(this->SettingsPage->DevButton, SIGNAL(clicked()), this, SLOT(showDevSetPage()));
            connect(this->SettingsPage->GCPButton, SIGNAL(clicked()), this->SettingsPage, SLOT(showGCPDialog()));
            connect(this->SettingsPage->LangButton, SIGNAL(clicked()), this, SLOT(chooseLangFile()));
            connect(this->SettingsPage->AboutButton, SIGNAL(clicked()), this, SLOT(showAboutPage()));
            connect(this->SettingsPage->AboutButton, SIGNAL(clicked()), this, SLOT(hideSettingsPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideSettingsPage()));
            
        }
        void hideSettingsPage(void) {
            OPSettingsPage->setOpacity(0);
            disconnect(this->SettingsPage->DevButton, SIGNAL(clicked()), this, SLOT(showDevSetPage()));
            disconnect(this->SettingsPage->GCPButton, SIGNAL(clicked()), this->SettingsPage, SLOT(showGCPDialog()));
            disconnect(this->SettingsPage->LangButton, SIGNAL(clicked()), this, SLOT(chooseLangFile()));
            disconnect(this->SettingsPage->AboutButton, SIGNAL(clicked()), this, SLOT(showAboutPage()));
            disconnect(this->SettingsPage->AboutButton, SIGNAL(clicked()), this, SLOT(hideSettingsPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideSettingsPage()));
        }
        void showAboutPage(void) {
            OPAboutPage->setOpacity(1);
            AboutPage->raise();
            Iconlabel->raise();
            BackButton->raise();
            this->AboutPage->AboutLabel_Donate->setOpenExternalLinks(TRUE);
            connect(this->AboutPage->CheckUpdateButton, SIGNAL(clicked()), this, SLOT(checkUpdate()));
            connect(this->AboutPage->MoreAboutInfo, SIGNAL(clicked()), this, SLOT(showMoreInfoPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showSettingsPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideAboutPage()));
        }
        void hideAboutPage(void) {
            OPAboutPage->setOpacity(0);
            this->AboutPage->AboutLabel_Donate->setOpenExternalLinks(FALSE);
            disconnect(this->AboutPage->CheckUpdateButton, SIGNAL(clicked()), this, SLOT(checkUpdate()));
            disconnect(this->AboutPage->MoreAboutInfo, SIGNAL(clicked()), this, SLOT(showMoreInfoPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showSettingsPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideAboutPage()));
        }
        void launchUIPage(void) {
            exitPage(1);
        }
        void exitProgram(void) {
            exitPage(2);
        }
        void exitPage(int exitType=0) {
            Shrink();
            Sleep(500);
            close();
            QApplication* app;
            app->exit(exitType);
        }
};