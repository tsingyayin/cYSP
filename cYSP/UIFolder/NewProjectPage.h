#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtGui>

#include "../loadsettings.h"
#include "../global_value.h"
#pragma execution_character_set("utf-8")
class uNewProjectPage :public QFrame
{
	Q_OBJECT
public:
	enum class InitProject {
		Unknown = 0,
		Empty = 1,
		Default = 2,
	};
	QLabel* TitleLabel;
	QLabel* ProjectName_Label;
	QLineEdit* ProjectName_Edit;
	QLabel* ProjectEnter_Label;
	QComboBox* ProjectEnter_Box;
	QLabel* ProjectSource_Label;
	QComboBox* ProjectSource_Box;
	QLabel* SPOLInterpreter_Label;
	QComboBox* SPOLInterpreter_Box;

	QLabel* NoticeLabel;
	SYSTEM_INFO SysInfo;
	QPushButton* StartButton;
	QPushButton* CancelButton;
	QString InitDocText;
	InitProject InitStatus = InitProject::Unknown;
	QPushButton* CloseButton;
	QFrame* BackGroundFrame;
	QGraphicsDropShadowEffect* TitleEffect;
	uNewProjectPage(InitProject ProjectInit = InitProject::Default) {
		this->setMinimumSize(800, 600);
		this->setAttribute(Qt::WA_TranslucentBackground);
		this->setWindowFlags(Qt::FramelessWindowHint);
		BackGroundFrame = new QFrame(this);
		TitleLabel = new QLabel(BackGroundFrame);
		TitleLabel->setText("  新建");
		TitleEffect = new QGraphicsDropShadowEffect(this);
		TitleLabel->setGraphicsEffect(TitleEffect);
		TitleEffect->setBlurRadius(20);
		TitleEffect->setOffset(3, 3);
		TitleEffect->setColor(QColor(128, 128, 128));
		ProjectName_Label = new QLabel(this);
		ProjectName_Edit = new QLineEdit(this);
		ProjectEnter_Label = new QLabel(this);
		ProjectEnter_Box = new QComboBox(this);
		ProjectSource_Label = new QLabel(this);
		ProjectSource_Box = new QComboBox(this);
		SPOLInterpreter_Label = new QLabel(this);
		SPOLInterpreter_Box = new QComboBox(this);

		NoticeLabel = new QLabel(this);
		StartButton = new QPushButton(this);
		CancelButton = new QPushButton(this);

		ProjectName_Label->setText("项目名称");
		ProjectEnter_Label->setText("项目入点");
		ProjectSource_Label->setText("资源管理");
		SPOLInterpreter_Label->setText("SPOL解释器类型");

		NoticeLabel->setAlignment(Qt::AlignCenter);
		StartButton->setText("开始");
		CancelButton->setText("取消");

		ProjectEnter_Box->addItem("SPOL文档", 0);
		ProjectEnter_Box->addItem("VIS文档（不可用）", 1);
		ProjectEnter_Box->addItem("PyGP文档（不可用）", 2);
		ProjectEnter_Box->addItem("GPOL字节码文档（不可用）", 3);
		ProjectEnter_Box->addItem("目前所有项都视作\"SPOL文档\"", 4);

		ProjectSource_Box->addItem("公共资源库", 0);
		ProjectSource_Box->addItem("自有资源库", 1);

		SPOLInterpreter_Box->addItem("AASPCMD_K9U1(SPOL.9X)", 0);
		SPOLInterpreter_Box->addItem("GSS_K10UT0(SPOL.9X)", 1);

		CloseButton = new QPushButton(this);
		CloseButton->setStyleSheet("\
			QPushButton{\
				border-image:url(:/IRC/InsiderSource/Icons/CloseButton.png);}\
			QPushButton:hover{\
				border-image:url(:/IRC/InsiderSource/Icons/CloseButton.png);background-color:#EEEEEE;}\
			QPushButton:pressed{\
				border-image:url(:/IRC/InsiderSource/Icons/CloseButton.png);background-color:#DDDDDD;}");
		connect(CloseButton, SIGNAL(clicked()), this, SLOT(close()));
		InitInfo(ProjectInit);

		connect(StartButton, SIGNAL(clicked()), this, SLOT(createProject()));
		connect(CancelButton, SIGNAL(clicked()), this, SLOT(exitPage()));
	}
	void InitInfo(InitProject ProjectInit) {
		InitStatus = ProjectInit;
		switch (ProjectInit) {
		case InitProject::Default:
			ProjectName_Edit->setText("未命名框架项目" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
			ProjectEnter_Box->setCurrentIndex(0);
			ProjectSource_Box->setCurrentIndex(0);
			SPOLInterpreter_Box->setCurrentIndex(0);
			break;
		case InitProject::Empty:
			ProjectName_Edit->setText("未命名项目" + QDateTime::currentDateTime().toString("yyyyMMdd_hhmmss"));
			ProjectEnter_Box->setCurrentIndex(-1);
			ProjectSource_Box->setCurrentIndex(-1);
			SPOLInterpreter_Box->setCurrentIndex(-1);
			break;
		}
	}

	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		this->setStyleSheet("\
			QFrame{\
				color:#000000;\
				font-size:" + QString::number((int)(height() * 0.03)) + "px;\
			}");
		BackGroundFrame->setStyleSheet("\
			QFrame{\
				border-radius:10px;\
				background-color:#FFFFFF;\
				border:1px solid black;\
			}");
		BackGroundFrame->setGeometry(QRect(0, 0, width(), height()));
		TitleLabel->setStyleSheet("\
			QLabel{\
				background-color:#FFFFFF;\
				color:#000000;\
				font-size:" + QString::number((int)(height() * 0.05)) + "px;\
				font-family:'Microsoft YaHei';\
				border-bottom:0px solid black;\
				border-bottom-left-radius:0px;\
				border-bottom-right-radius:0px;\
			}");
		TitleLabel->setGeometry(QRect(BackGroundFrame->width() * 0.0, BackGroundFrame->height() * 0.0, BackGroundFrame->width() * 1.0, BackGroundFrame->height() * 0.1));
		ProjectName_Label->setGeometry(QRect(width() * 0.15, height() * 0.2, width() * 0.2, height() * 0.1));
		ProjectName_Edit->setGeometry(QRect(width() * 0.35, height() * 0.2, width() * 0.5, height() * 0.1));
		ProjectName_Edit->setStyleSheet("\
			QLineEdit{\
				background-color:#EFEFEF;\
				border:1px solid #4A4A4A;\
				border-radius:5px;\
			}");
		ProjectEnter_Label->setGeometry(QRect(width() * 0.15, height() * 0.35, width() * 0.2, height() * 0.1));
		ProjectEnter_Box->setGeometry(QRect(width() * 0.35, height() * 0.35, width() * 0.5, height() * 0.1));
		ProjectEnter_Box->setStyleSheet("\
			QComboBox{\
				background-color:#EFEFEF;\
				border:1px solid #4A4A4A;\
				border-radius:5px\
			}\
			QComboBox::drop-down{\
				background-color:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop: 0 #FFC2C3,stop: 1.0 #AEE4FF);\
				border-top-right-radius:5px;\
				border-bottom-right-radius:5px;\
			}");
		ProjectSource_Label->setGeometry(QRect(width() * 0.15, height() * 0.5, width() * 0.2, height() * 0.1));
		ProjectSource_Box->setGeometry(QRect(width() * 0.35, height() * 0.5, width() * 0.5, height() * 0.1));
		ProjectSource_Box->setStyleSheet("\
			QComboBox{\
				background-color:#EFEFEF;\
				border:1px solid #4A4A4A;\
				border-radius:5px\
			}\
			QComboBox::drop-down{\
				background-color:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop: 0 #FFC2C3,stop: 1.0 #AEE4FF);\
				border-top-right-radius:5px;\
				border-bottom-right-radius:5px;\
			}");
		SPOLInterpreter_Label->setGeometry(QRect(width() * 0.15, height() * 0.65, width() * 0.2, height() * 0.1));
		SPOLInterpreter_Box->setGeometry(QRect(width() * 0.35, height() * 0.65, width() * 0.5, height() * 0.1));
		SPOLInterpreter_Box->setStyleSheet("\
			QComboBox{\
				background-color:#EFEFEF;\
				border:1px solid #4A4A4A;\
				border-radius:5px\
			}\
			QComboBox::drop-down{\
				background-color:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop: 0 #FFC2C3,stop: 1.0 #AEE4FF);\
				border-top-right-radius:5px;\
				border-bottom-right-radius:5px;\
			}");
		NoticeLabel->setGeometry(QRect(width() * 0.1, height() * 0.75, width() * 0.8, height() * 0.1));
		StartButton->setGeometry(QRect(width() * 0.75, height() * 0.88, width() * 0.15, height() * 0.07));
		CancelButton->setGeometry(QRect(width() * 0.55, height() * 0.88, width() * 0.15, height() * 0.07));
		CloseButton->setGeometry(QRect(width() * 0.96, height() * 0.012, height() * 0.04, height() * 0.04));
		StartButton->setStyleSheet("\
				QPushButton\
					{border:2px solid #1473E6;border-radius:10px;background-color:#FFFFFF;}\
				QPushButton:hover\
					{border:2px solid #1473E6;border-radius:10px;background-color:#EEEEEE;}\
				QPushButton:pressed\
					{border:2px solid #1473E6;border-radius:10px;background-color:#DDDDDD;}");
		CancelButton->setStyleSheet("\
				QPushButton\
					{border:2px solid #D61921;border-radius:10px;background-color:#FFFFFF;}\
				QPushButton:hover\
					{border:2px solid #D61921;border-radius:10px;background-color:#EEEEEE;}\
				QPushButton:pressed\
					{border:2px solid #D61921;border-radius:10px;background-color:#DDDDDD;}");
	}
public slots:
	void createProject() {
		if (ProjectName_Edit->text() != "" 
			&& ProjectEnter_Box->currentIndex() != -1 
			&& ProjectSource_Box->currentIndex() != -1 
			&& SPOLInterpreter_Box->currentIndex() != -1) 
			{
			NoticeLabel->setText("正在创建项目...");
			NoticeLabel->repaint();

			QString Settings = "ProjectEdition=Visindigo0.10.0\n";
			switch (ProjectEnter_Box->currentIndex()) {
			case 0:
				Settings += "ProjectEnter=SPOL\n";
				break;
			case 1:
				Settings += "ProjectEnter=SPOL\n";
				break;
			case 2:
				Settings += "ProjectEnter=SPOL\n";
				break;
			case 3:
				Settings += "ProjectEnter=SPOL\n";
				break;
			}
			switch (ProjectSource_Box->currentIndex()) {
			case 0:
				Settings += "ProjectSource=Public\n";
				break;
			case 1:
				Settings += "ProjectSource=Private\n";
				break;
			default:
				Settings += "ProjectSource=Public\n";
			}
			switch (SPOLInterpreter_Box->currentIndex()) {
			case 0:
				Settings += "SPOLInterpreter=AASPCMD_K9U1\n";
				break;
			case 1:
				Settings += "SPOLInterpreter=GSS_K10UT0\n";
				break;
			default:
				Settings += "SPOLInterpreter=GSS_K10UT0\n";
			}
			QDir NewProjectDir;
			NewProjectDir.mkpath("./Users_Data/repos/" + ProjectName_Edit->text());
			QDir ProjectDir = "./Users_Data/repos/" + ProjectName_Edit->text();
			ProjectDir.mkdir("cache");
			ProjectDir.mkdir("output");
			ProjectDir.mkdir("resource");
			QFile SettingsFile;
			SettingsFile.setFileName("./Users_Data/repos/" + ProjectName_Edit->text() + "/Project.ces");
			SettingsFile.open(QIODevice::ReadWrite | QIODevice::Text);
			SettingsFile.write(Settings.toUtf8());
			SettingsFile.close();

			QFile EnterFile;
			switch (InitStatus) {
			case InitProject::Empty:
				InitDocText = "#这个文档是您的项目\"" + ProjectName_Edit->text() + "\"的入点。\n#其名称main.spol不得更改\n";

				EnterFile.setFileName("./Users_Data/repos/" + ProjectName_Edit->text() + "/main.spol");
				EnterFile.open(QIODevice::ReadWrite | QIODevice::Text);
				EnterFile.write(InitDocText.toUtf8());
				EnterFile.close();
				break;
			case InitProject::Default:
				InitDocText = "#这个文档是您的项目\"" + ProjectName_Edit->text() + "\"的入点。\n#其名称main.spol不得更改。 \
\n/SPOL0.9.0-FollowNew\
\ntitle(框架项目,子标题,默认背景,紫靛工作室)\
\ncover(on)\
\nregister(Counter)\
\n#在下面键入您的SPOL代码，遮罩框架已经为您打开\
\n\
\n#在上面键入您的SPOL代码。\
\ncover(off)\
\n";
				EnterFile.setFileName("./Users_Data/repos/" + ProjectName_Edit->text() + "/main.spol");
				EnterFile.open(QIODevice::ReadWrite | QIODevice::Text);
				EnterFile.write(InitDocText.toUtf8());
				EnterFile.close();
				break;
			}
			GlobalValue::CurrentProject = ProjectName_Edit->text();
			Sleep(500);
			qApp->exit(1);
		}
		else {
			NoticeLabel->setText("检查是否有空参数或文件名称是否有效！");
		}
	}
	void exitPage() {
		qApp->exit(-1);
	}
	void closeEvent(QCloseEvent* event = Q_NULLPTR) {
		qApp->exit(-1);
	}
	void mousePressEvent(QMouseEvent* event) {
#if DEPLOY == 1
		if (TitleLabel->underMouse()) {
			QWidget* pWindow = this->window();
			ReleaseCapture();
			SendMessage(HWND(pWindow->winId()), WM_SYSCOMMAND, SC_MOVE + HTCAPTION, 0);
			event->ignore();
		}
#endif
	}
};