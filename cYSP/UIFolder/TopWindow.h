#pragma once
#include "..\langcontrol.h"
#include "..\global_value.h"
#include "..\loadsettings.h"
#include "ProgramSettings.h"
#include "..\Aaspcommand\aaspcommand.h"
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <exception>
#include <QTest>
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
            frame = new QFrame(this);
            hl = new QHBoxLayout(this);
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
        CurrentStyle* Style;
        int gX, gY;
        hUpdateDialog(int X, int Y, QString VersionName,QString DialogLink,QWidget* parent = Q_NULLPTR) {
            gVersionName = VersionName;
            gDialogLink = DialogLink;
            this->setParent(parent);
            Style = new CurrentStyle(this);
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

            this->setStyleSheet(Style->Widget1);

            OopsLabel = new QLabel(this);
            OopsLabel->setText(msg("Ui_Update_Update_Available")+"UYXA");
            OopsLabel->setGeometry(QRect(50, 50, 800, 40));
            OopsLabel->setAlignment(Qt::AlignCenter);
            OopsLabel->setStyleSheet("\
                QLabel{\
                background-color:rgba(255, 255, 255, 0);\
                border:none;\
                border-radius:0px;\
                color:#88DDFF;\
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
            BackButton->setText(msg("Ui_Text_Common_Back"));
            BackButton->setStyleSheet(Style->Button2);
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
                UpdateInfoLabel->setText("<A href='" + DialogLink + "'>" + msg("Ui_Update_With_Log") + "</a>");
            }
            else {
                UpdateInfoLabel->setOpenExternalLinks(FALSE);
                UpdateInfoLabel->setText(msg("Ui_Update_Without_Log"));
            }
        }
        void UpdateLang(void) {
            OopsLabel->setText(msg("Ui_Update_Update_Available") + "UYXA");
            if (gVersionName.contains("Pre")) {
                NewVersionLabel->setText("<A href='" + Preurl + "'>" + gVersionName + "</a>");
            }
            else {
                NewVersionLabel->setText("<A href='" + Puburl + "'>" + gVersionName + "</a>");
            }
            BackButton->setText(msg("Ui_Text_Common_Back"));
            if (gDialogLink != "NONELINK") {
                UpdateInfoLabel->setOpenExternalLinks(TRUE);
                UpdateInfoLabel->setText("<A href='" + gDialogLink + "'>" + msg("Ui_Update_With_Log") + "</a>");
            }
            else {
                UpdateInfoLabel->setOpenExternalLinks(FALSE);
                UpdateInfoLabel->setText(msg("Ui_Update_Without_Log"));
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
        CurrentStyle* Style;
		hFirstPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            Style = new CurrentStyle(this);

            UIModeButton = new QPushButton(this);
            UIModeButton->setGeometry(QRect(50, 350, 600, 50));
            UIModeButton->setStyleSheet(Style->Button1);

            ToolsButton = new QPushButton(this);
            ToolsButton->setGeometry(QRect(390, 420, 260, 50));
            ToolsButton->setStyleSheet(Style->Button1);

            CreateButton = new QPushButton(this);
            CreateButton->setGeometry(QRect(50, 420, 260, 50));
            CreateButton->setStyleSheet(Style->Button1);

            SettingsButton = new QPushButton(this);
            SettingsButton->setGeometry(QRect(50, 490, 600, 50));
            SettingsButton->setStyleSheet(Style->Button1);

            ExitButton = new QPushButton(this);
            ExitButton->setGeometry(QRect(50, 560, 260, 50));
            ExitButton->setStyleSheet(Style->Button1);

            setChildText();
		}
        
        void setChildText(void) {
            UIModeButton->setText(msg("Ui_MainPage_Launch_UI"));
            ToolsButton->setText(msg("Ui_MainPage_Open_Tools"));
            CreateButton->setText(msg("Ui_MainPage_Open_Creation"));
            SettingsButton->setText(msg("Ui_MainPage_Open_Settings"));
            ExitButton->setText(msg("Ui_Text_Common_Exit"));
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
        QPushButton* NormalButton;
        QPushButton* GCPButton;
        hGCPDialog* GCPDialog;
        hDevSettings* DevPage;
        hProgramSettings* NormalSetPage;
        CurrentStyle* Style;
        int gX=0, gY=0;
        hSettingsPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            Style = new CurrentStyle(this);

            gX = X;
            gY = Y;
            AboutButton = new QPushButton(this);
            AboutButton->setGeometry(QRect(50,420,260,50));
            AboutButton->setStyleSheet(Style->Button1);

            LangButton = new QPushButton(this);
            LangButton->setGeometry(QRect(390,420,260,50));
            LangButton->setStyleSheet(Style->Button1);

            NormalButton = new QPushButton(this);
            NormalButton->setGeometry(QRect(50,350,260,50));
            NormalButton->setStyleSheet(Style->Button1);

            DevButton = new QPushButton(this);
            DevButton->setGeometry(QRect(390, 350, 260, 50));
            DevButton->setStyleSheet(Style->Button1);

            /*GCPButton = new QPushButton(this);
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
                    }");*/
            setChildText();
        }
        void setChildText(void) {
            AboutButton->setText(msg("Ui_Text_Common_About_"));
            LangButton->setText(msg("Ui_SettingsPage_Choose_Language"));
            NormalButton->setText(msg("Ui_SettingsPage_Normal_Settings"));
            DevButton->setText(msg("Ui_SettingsPage_Dev_Settings"));
        }

    public slots:
        /*void showGCPDialog(void) {
            if (Program_Settings("GCPMode") == "True") {
                writesettings("GCPMode", "False");
                GCPButton->setText(msg("Ui_Msg_OpenGCPMode"));
            }
            else {
                GCPDialog = new hGCPDialog(gX, gY);
                GCPDialog->show();
                connect(GCPDialog, SIGNAL(chooseEnd()), this, SLOT(repaintMsg()));
            }
        }*/
        void showDevSetPage(void) {
            DevPage = new hDevSettings(gX, gY);
            DevPage->show(); 
        }
        void showNormalSetPage(void) {
            NormalSetPage = new hProgramSettings(gX, gY);
            NormalSetPage->show();
        }
        /*void repaintMsg(void){
            if (Program_Settings("GCPMode") == "True") {
                GCPButton->setText(msg("Ui_Msg_CloseGCPMode"));
            }
            else {
                GCPButton->setText(msg("Ui_Msg_OpenGCPMode"));
            }
            
        }*/
};

//工具页面定义
class hToolsPage :public QWidget
{
    Q_OBJECT
    public:
        QPushButton* ToSpolButton;
        QPushButton* ClrWrongButton;
        QPushButton* ClrCacheButton;
        CurrentStyle* Style;
        int gX, gY;
        hToolsPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            Style = new CurrentStyle(this);
            gX = X;
            gY = Y;

            /*ToSpolButton = new QPushButton(this);
            ToSpolButton->setGeometry(QRect(390,420,260,50));
            ToSpolButton->setStyleSheet(Style->Button1);*/

            ClrWrongButton = new QPushButton(this);
            ClrWrongButton->setGeometry(QRect(50,350,260,50));
            ClrWrongButton->setStyleSheet(Style->Button1);

            ClrCacheButton = new QPushButton(this);
            ClrCacheButton->setGeometry(QRect(390,350,260,50));
            ClrCacheButton->setStyleSheet(Style->Button1);

            setChildText();
        }
        void setChildText(void){
            //ToSpolButton->setText(msg("Ui_Msg_To_Spol"));
            ClrWrongButton->setText(msg("Ui_ToolsPage_Delete_Wrong"));
            ClrCacheButton->setText(msg("Ui_ToolsPage_Delete_Cache"));
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
        CurrentStyle* Style;
        hCreatePage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            Style = new CurrentStyle(this);
            gX = X;
            gY = Y;
            OpenButton_Cache= new QPushButton(this);
            OpenButton_Cache->setGeometry(QRect(50,280,260,50));
            OpenButton_Cache->setObjectName("OpenButton_Cache");
            OpenButton_Cache->setStyleSheet(Style->Button1);

            OpenButton_Source= new QPushButton(this);
            OpenButton_Source->setGeometry(QRect(50,350,260,50));
            OpenButton_Source->setObjectName("OpenButton_Source");
            OpenButton_Source->setStyleSheet(Style->Button1);

            OpenButton_Story= new QPushButton(this);
            OpenButton_Story->setGeometry(QRect(50,420,260,50));
            OpenButton_Story->setObjectName("OpenButton_Story");
            OpenButton_Story->setStyleSheet(Style->Button1);

            OpenButton_Official= new QPushButton(this);
            OpenButton_Official->setGeometry(QRect(50,490,260,50));
            OpenButton_Official->setObjectName("OpenButton_Official");
            OpenButton_Official->setStyleSheet(Style->Button1);

            SPOLDevButton= new QPushButton(this);
            SPOLDevButton->setGeometry(QRect(390, 280, 260, 50));
            SPOLDevButton->setObjectName("SPOLDevButton");
            SPOLDevButton->setStyleSheet(Style->Button1);

            setChildText();
        }
        void setChildText(void) {
            OpenButton_Cache->setText(msg("Ui_CreationPage_Folder_Cache"));
            OpenButton_Source->setText(msg("Ui_CreationPage_Folder_Source"));
            OpenButton_Story->setText(msg("Ui_CreationPage_Folder_Story"));
            OpenButton_Official->setText(msg("Ui_CreationPage_Folder_Official"));
            SPOLDevButton->setText(msg("Ui_CreationPage_Open_SPOLDev"));
        }
    public slots:
        void showSPOLDevWindow(void) {
            QString SPOLDevPath = QDir::currentPath() + "/SPOLDev.exe";
            system(("start " + SPOLDevPath).toLocal8Bit());
            //DevWindow = new SPOLDevWindow();
            //DevWindow->show();
        }
};

//关于页定义
class hAboutPage :public QWidget
{
    Q_OBJECT
    public:
        QWidget* BackgroundWidget;
        QLabel* AboutLabel_FullVer;
        QLabel* AboutLabel_MainVer;
        QLabel* AboutLabel_SubVer;
        QLabel* AboutLabel_BuildVer;
        QLabel* AboutLabel_SpolVer;
        QLabel* AboutLabel_Support;
        QLabel* AboutLabel_Donate;
        QPushButton* MoreAboutInfo;
        QPushButton* CheckUpdateButton;
        hMoreInfo* MoreInfoPage;
        CurrentStyle* Style;
        int gX, gY;
        hAboutPage(int X, int Y, QWidget* parent = Q_NULLPTR) {
            this->setParent(parent);
            this->setGeometry(QRect(0, 0, 700, 650));
            Style = new CurrentStyle(this);

            gX = X;
            gY = Y;
            BackgroundWidget = new QWidget(this);
            BackgroundWidget->setGeometry(QRect(30, 275, 640, 200));
            BackgroundWidget->setStyleSheet("QWidget{background-color:rgba(255,255,255,150);}");

            AboutLabel_FullVer = new QLabel(this);          
            AboutLabel_FullVer->setGeometry(QRect(25,280,650,30));
            AboutLabel_FullVer->setAlignment(Qt::AlignCenter);
            AboutLabel_FullVer->setStyleSheet(Style->Label1);

            AboutLabel_MainVer = new QLabel(this);
            AboutLabel_MainVer->setGeometry(QRect(60,320,300,30));
            AboutLabel_MainVer->setAlignment(Qt::AlignLeft);
            AboutLabel_MainVer->setStyleSheet(Style->Label1);

            AboutLabel_SubVer= new QLabel(this);
            AboutLabel_SubVer->setGeometry(QRect(360,320,300,30));
            AboutLabel_SubVer->setAlignment(Qt::AlignLeft);
            AboutLabel_SubVer->setStyleSheet(Style->Label1);

            AboutLabel_BuildVer= new QLabel(this);
            AboutLabel_BuildVer->setGeometry(QRect(60,360,300,30));
            AboutLabel_BuildVer->setAlignment(Qt::AlignLeft);
            AboutLabel_BuildVer->setStyleSheet(Style->Label1);

            AboutLabel_SpolVer= new QLabel(this);
            AboutLabel_SpolVer->setGeometry(QRect(360,360,300,30));
            AboutLabel_SpolVer->setAlignment(Qt::AlignLeft);
            AboutLabel_SpolVer->setStyleSheet(Style->Label1);

            AboutLabel_Support= new QLabel(this);
            AboutLabel_Support->setGeometry(QRect(60, 400, 600, 30));
            AboutLabel_Support->setAlignment(Qt::AlignLeft);
            AboutLabel_Support->setStyleSheet(Style->Label1);

            AboutLabel_Donate= new QLabel(this);
            AboutLabel_Donate->setOpenExternalLinks(FALSE);
            AboutLabel_Donate->setGeometry(QRect(60, 440, 600, 30));
            AboutLabel_Donate->setAlignment(Qt::AlignLeft);
            AboutLabel_Donate->setStyleSheet(Style->Label1);

            MoreAboutInfo = new QPushButton(this);
            MoreAboutInfo->setGeometry(QRect(50, 490, 600, 50));
            MoreAboutInfo->setStyleSheet(Style->Button1);

            CheckUpdateButton= new QPushButton(this);
            CheckUpdateButton->setGeometry(QRect(50,560,260,50));
            CheckUpdateButton->setStyleSheet(Style->Button1);

            setChildText();
        }
        void setChildText(void){
            AboutLabel_FullVer->setText(PROINFO::Total);
            AboutLabel_MainVer->setText(msg("KAU_About_Info_MainVer") + PROINFO::Main);
            AboutLabel_SubVer->setText(msg("KAU_About_Info_SubVer") + PROINFO::Sub);
            AboutLabel_BuildVer->setText(msg("KAU_About_Info_BuildVer") + PROINFO::Build);
            AboutLabel_SpolVer->setText(msg("KAU_About_Info_SpolVer") + PROINFO::SPOL);
            AboutLabel_Support->setText(msg("KAU_About_Info_Support") + "紫靛工作室");
            AboutLabel_Donate->setText(msg("KAU_About_Info_Donate").arg("<A href='" + urlAFD + "'>" + urlAFD + "</a>"));
            MoreAboutInfo->setText(msg("KAU_About_Info_More"));
            CheckUpdateButton->setText(msg("Ui_AboutPage_Check_Update"));
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
        hToolsPage* ToolsPage;
        hCreatePage* CreatePage;
        hSettingsPage* SettingsPage;
        hAboutPage* AboutPage;
        hDevSettings* DevSetPage;
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

        CurrentStyle* Style;
		int X,  Y;
		void setupUI() {
			desktop = new QDesktopWidget();
			int Current_monitor = desktop->screenNumber();
			QRect Display = desktop->screenGeometry(Current_monitor);
			X = Display.width();
			Y = Display.height();
            Style = new CurrentStyle(this);
            //基本圆角框架和半透明效果实现
            this->setGeometry(QRect(600, 400, 700, 300));
			
			this->setAttribute(Qt::WA_TranslucentBackground);           
            this->setWindowFlags(Qt::FramelessWindowHint);
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
            this->setFixedSize(this->size());
            this->setStyleSheet(Style->Widget1);

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
            AboutPage->hide();

            CreatePage = new hCreatePage(X, Y, this);
            CreatePage->hide();

            ToolsPage = new hToolsPage(X, Y, this);
            ToolsPage->hide();

            SettingsPage = new hSettingsPage(X, Y, this);
            SettingsPage->hide();

            FirstPage = new hFirstPage(X,Y,this);
            FirstPage->hide();

            Titlelabel = new QLabel(this);
            Titlelabel->setStyleSheet("\
                QLabel{\
                    background-color:rgba(255,255,255,0);\
                    border:none;\
                    border-radius:0px;\
                    color:#FFFFFF;\
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
            LogoRaw.load(PROPATH::Users + "/source/BaseUI/Image/Videotape_Win11.png");
            LogoRaw = LogoRaw.scaled(270, 270, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
            Iconlabel->setPixmap(QPixmap::fromImage(LogoRaw));
            Iconlabel->setStyleSheet("QLabel{background-color:rgba(255,255,255,0);border:none;border-radius:0px;}");
            OPIconlabel = new QGraphicsOpacityEffect();
            OPIconlabel->setOpacity(1);
            Iconlabel->setGraphicsEffect(OPIconlabel);

            BackButton = new QPushButton(this);
            BackButton->setGeometry(QRect(390, 560, 260, 50));
            BackButton->setStyleSheet(Style->Button2);
            setChildText();
		}
        void setChildText(void) {
            BackButton->setText(msg("Ui_Text_Common_Back"));
            Titlelabel->setText(msg("Ui_AllPage_Text_Title"));
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
            this->setWindowTitle("YSP "+PROINFO::Main);
            this->setWindowIcon(QIcon(PROPATH::Users + "/source/WinICO/Videotape_Win11.ico"));
			setupUI();
            showFirstPage();
            connectAll();
            Service = new hServiceFramework();
            connect(Service, SIGNAL(Anyinfo(int, QString)), this, SLOT(showAnyInfo(int, QString)));
            
		}

        //信号链接函数
        void connectAll(void) {
            connect(this->FirstPage->UIModeButton, SIGNAL(clicked()), this, SLOT(launchUIPage()));
            connect(this->FirstPage->CreateButton, SIGNAL(clicked()), this, SLOT(showCreatePage()));
            connect(this->FirstPage->CreateButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            connect(this->FirstPage->ToolsButton, SIGNAL(clicked()), this, SLOT(showToolsPage()));
            connect(this->FirstPage->ToolsButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            connect(this->FirstPage->SettingsButton, SIGNAL(clicked()), this, SLOT(showSettingsPage()));
            connect(this->FirstPage->SettingsButton, SIGNAL(clicked()), this, SLOT(hideFirstPage()));
            connect(this->FirstPage->ExitButton, SIGNAL(clicked()), this, SLOT(exitProgram()));

            connect(this->CreatePage->SPOLDevButton, SIGNAL(clicked()), this->CreatePage, SLOT(showSPOLDevWindow()));
            connect(this->CreatePage->OpenButton_Story, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            connect(this->CreatePage->OpenButton_Cache, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            connect(this->CreatePage->OpenButton_Official, SIGNAL(clicked()), this, SLOT(openAnyFolder()));
            connect(this->CreatePage->OpenButton_Source, SIGNAL(clicked()), this, SLOT(openAnyFolder()));

            connect(this->ToolsPage->ClrWrongButton, SIGNAL(clicked()), this, SLOT(clearWrongImage()));
            connect(this->ToolsPage->ClrCacheButton, SIGNAL(clicked()), this, SLOT(clearAllCacheImage()));

            connect(this->SettingsPage->DevButton, SIGNAL(clicked()), this, SLOT(showDevSetPage()));
            connect(this->SettingsPage->NormalButton, SIGNAL(clicked()), this, SLOT(showNormalSetPage()));
            //connect(this->SettingsPage->GCPButton, SIGNAL(clicked()), this->SettingsPage, SLOT(showGCPDialog()));
            connect(this->SettingsPage->LangButton, SIGNAL(clicked()), this, SLOT(chooseLangFile()));
            connect(this->SettingsPage->AboutButton, SIGNAL(clicked()), this, SLOT(showAboutPage()));
            connect(this->SettingsPage->AboutButton, SIGNAL(clicked()), this, SLOT(hideSettingsPage()));

            this->AboutPage->AboutLabel_Donate->setOpenExternalLinks(TRUE);
            connect(this->AboutPage->CheckUpdateButton, SIGNAL(clicked()), this, SLOT(checkUpdate()));
            connect(this->AboutPage->MoreAboutInfo, SIGNAL(clicked()), this, SLOT(showMoreInfoPage()));
        }

        //窗体扩展函数
		void Expand() {
			double a;
			for (int i = 0; i <= 101; i += 2) {
				a = 0.5 * (1 - qCos(i * 0.0314159));
				//this->setGeometry(QRect(600, (int)(400 - a * 200), 700, (int)(300 + a * 350)));
                this->move(600, (int)(400 - a * 200));
                this->setFixedSize(700, (int)(300 + a * 350));
                this->OPTitlelabel->setOpacity(1 - (float)i / 100);
                this->Iconlabel->setGeometry(QRect((int)(50 + 170 * a), 15, 270, 270));
				this->repaint();
				QTest::qSleep(1);
			}
		}

        //窗体收缩函数
		void Shrink() {
			double a;
            QRect Rect = this->geometry();
			for (int i = 100; i >= -1; i -= 1) {
				a = 0.5 * (1 - qCos(i * 0.0314159));
				//this->setGeometry(QRect(Rect.left(), (int)(Rect.top() + 200 - a * 200), 700, (int)(300 + a * 350)));
                this->move(Rect.left(), (int)(Rect.top() + 200 - a * 200));
                this->setFixedSize(700, (int)(300 + a * 350));
                this->OPTitlelabel->setOpacity(1 - (float)i / 100);
                this->Iconlabel->setGeometry(QRect((int)(50 + 170 * a), 15, 270, 270));
				this->repaint();
				QTest::qSleep(1);
			}
		}

        //（首次）鼠标进入事件
		void enterEvent(QEvent*) {
			if (FirstEnter == 0) {
				Expand();
				FirstEnter = 1;
                checkUpdate();
                this->BackButton->show();
			}
		}

        //鼠标拖拽事件
        void mousePressEvent(QMouseEvent* event) {
            if (Iconlabel->underMouse()) {
                QWidget* pWindow = this->window();
                ReleaseCapture();
                SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
                event->ignore();
            }
        }

    public slots:
        //检查更新函数
        void checkUpdate() {
            QStringList UpdateInfo = Service->ui_CheckUpdate();
            if (UpdateInfo[0] != "NODIALOG" && !UpdateDialogWindowIsShow) {
                UpdateDialog = new hUpdateDialog(X, Y, UpdateInfo[0], UpdateInfo[1]);
                UpdateDialog->show();
                UpdateDialogWindowIsShow = TRUE;
                connect(this->UpdateDialog, SIGNAL(windowIsClosed()), this, SLOT(updateDialogClosed()));
            }
        }

        //更新对话框状态变更函数
        void updateDialogClosed(void) {
            UpdateDialogWindowIsShow = FALSE;
        }

        //语言刷新函数
        void chooseLangFile(void) {
            QString LangFileDialog = QFileDialog::getOpenFileName(this,msg("Ui_Msg_Choose_Lang"), PROPATH::Users+"/Language", "Story Player Language(*.splang)");
            QString LangFileName = LangFileDialog.section("/",-1,-1).section(".",0,0);
            Service->ui_langset(LangFileName);

            setChildText();
            FirstPage->setChildText();
            SettingsPage->setChildText();
            AboutPage->setChildText();
            CreatePage->setChildText();
            ToolsPage->setChildText();

            /*if (Program_Settings("GCPMode") == "True") {
                SettingsPage->GCPButton->setText(msg("Ui_Msg_CloseGCPMode"));
            }else {
                SettingsPage->GCPButton->setText(msg("Ui_Msg_OpenGCPMode"));
            }*/   

            if (UpdateDialogWindowIsShow) { UpdateDialog->UpdateLang(); };
        }

        //打开文件夹函数
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

        //清除损坏图像
        void clearWrongImage(void) {
            Service->ui_DeleteEmptyMap();
        }
        
        //清除所有缓存
        void clearAllCacheImage(void) {
            Service->ui_DeleteAllCache();
        }

        //下增式消息服务
        void showAnyInfo(int infoGroup = 2, QString needToShow = "UNKNOWN INFO") {
            float a = 0;
            QRect Rect = this->geometry();
            for (int i = 0; i <= 101; i += 4) {
                a = 0.5 * (1 - qCos(i * 0.0314159));
                //this->setGeometry(QRect(Rect.left(), Rect.top(), 700, (int)(650 + a * 50)));
                this->setFixedSize(700, (int)(650 + a * 50));
                this->repaint();
                QTest::qSleep(3);
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
                        color:#88DDFF;\
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
            QTest::qSleep(1000);
            AnyInfolabel->setText("");
            OPAnyInfolabel->setOpacity(0);
            AnyInfolabel->repaint();
            a = 0;
            for (int i = 101; i >= 2; i -= 4) {
                a = 0.5 * (1 - qCos(i * 0.0314159));
                //this->setGeometry(QRect(Rect.left(), Rect.top(), 700, (int)(650 + a * 50)));
                this->setFixedSize(700, (int)(650 + a * 50));
                this->repaint();
                QTest::qSleep(3);
            }
        }


        //展示一般设置
        void showNormalSetPage(void) {
            SettingsPage->showNormalSetPage();
            this->hide();
            connect(this->SettingsPage->NormalSetPage, SIGNAL(windowIsClosed()), this, SLOT(show()));
        }
        
        //展示开发设置
        void showDevSetPage(void) {
            SettingsPage->showDevSetPage();
            this->hide();
            connect(this->SettingsPage->DevPage, SIGNAL(windowIsClosed()), this, SLOT(show()));
        }

        //展示更多信息
        void showMoreInfoPage(void) {
            AboutPage->showMoreInfoPage();
            this->hide();
            connect(this->AboutPage->MoreInfoPage, SIGNAL(windowIsClosed()), this, SLOT(show()));
        }

        //展示首页
        void showFirstPage(void) {
            FirstPage->show();
            FirstPage->raise();
            Iconlabel->raise();
            BackButton->raise();          
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(exitPage()));
        }

        //隐藏首页
        void hideFirstPage(void) {
            FirstPage->hide();
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(exitPage()));
        }

        //展示创作页面
        void showCreatePage(void) {
            CreatePage->show();
            CreatePage->raise();
            Iconlabel->raise();
            BackButton->raise();         
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideCreatePage()));
        }

        //隐藏创作页面
        void hideCreatePage(void) {
            CreatePage->hide();
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideCreatePage()));
        }

        //展示工具页面
        void showToolsPage(void) {
            ToolsPage->show();           
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideToolsPage()));
        }

        //隐藏工具页面
        void hideToolsPage(void) {
            ToolsPage->hide();
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideToolsPage()));
        }

        //展示设定页面
        void showSettingsPage(void) {
            SettingsPage->show();
            SettingsPage->raise();
            Iconlabel->raise();
            BackButton->raise();          
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideSettingsPage()));            
        }

        //隐藏设定页面
        void hideSettingsPage(void) {
            SettingsPage->hide();
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showFirstPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideSettingsPage()));
        }

        //展示关于页面
        void showAboutPage(void) {
            AboutPage->show();
            AboutPage->raise();
            Iconlabel->raise();
            BackButton->raise();          
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(showSettingsPage()));
            connect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideAboutPage()));
        }

        //隐藏关于页面
        void hideAboutPage(void) {
            AboutPage->hide();
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(showSettingsPage()));
            disconnect(this->BackButton, SIGNAL(clicked()), this, SLOT(hideAboutPage()));
        }

        //启动播放器
        void launchUIPage(void) {
            exitPage(1);
        }

        //退出程序
        void exitProgram(void) {
            exitPage(2);
        }

        //退出交互页面
        void exitPage(int exitType=0) {
            Shrink();
            QTest::qSleep(500);
            close();
            QApplication* app;
            app->exit(exitType);
        }
};