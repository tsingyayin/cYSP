#pragma once
#pragma once
#include "..\langcontrol.h"
#include "..\global_value.h"
#include "..\loadsettings.h"
#include <math.h>
#pragma comment(lib, "user32.lib")
#include <qt_windows.h>
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <ctype.h>
using namespace std;

//程序通用设置
class hProgramSettings :public QWidget
{
	Q_OBJECT
public:
	int gX, gY;
	hProgramSettings(int X, int Y, QWidget* parent = Q_NULLPTR) {
		this->setParent(parent);
		this->setGeometry(QRect(0, 0, 700, 650));
	}
};


//开发性设置
class hDevSettings :public QWidget
{
	Q_OBJECT
	signals:
		void windowIsClosed(void);

	public:
		QLabel* Text_Dev;
		QComboBox* Edit_Dev;
		QLabel* Text_GCP;
		QComboBox* Edit_GCP;
		QSpacerItem* Space;
		QGridLayout* CurrentLayout;
		QPushButton* InitButton;
		QPushButton* EnableButton;
		
		hDevSettings(int X, int Y, QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
			this->setWindowTitle("YSP程序高级设定");

			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);

			Text_Dev = new QLabel(this);
			Text_Dev->setText("选择更新通道");
			Text_Dev->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
			Text_Dev->setToolTip("更改此项设置可以改变当前接收更新消息提醒的通道。\n自动模式会遵循您使用的软件版本自行匹配，使用其他选项强制指定对应通道。\n如果您是公开版本用户，请您在切换到内部测试之前慎重考虑，因为内部测试版本会有更多Bug，甚至可能破坏您现有的SPOL文档。");
			Text_Dev->setAlignment(Qt::AlignLeft);
			CurrentLayout->addWidget(Text_Dev, 0, 1, 1, 1);

			Edit_Dev = new QComboBox(this);
			Edit_Dev->addItem("自动(Auto)", 0);
			Edit_Dev->addItem("内部测试渠道(Pre)", 1);
			Edit_Dev->addItem("公开发布渠道(Pub)", 2);
			Edit_Dev->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei'}");
			if (Program_Settings("Update_Channel") == "Pre") {
				Edit_Dev->setCurrentIndex(1);
			}
			else if (Program_Settings("Update_Channel") == "Pub") {
				Edit_Dev->setCurrentIndex(2);
			}
			else {
				Edit_Dev->setCurrentIndex(0);
			}
			CurrentLayout->addWidget(Edit_Dev, 0, 3, 1, 1);


			Space = new QSpacerItem(40,0);
			CurrentLayout->addItem(Space, 0, 0, 1, 1);
			CurrentLayout->addItem(Space, 0, 2, 1, 1);
			CurrentLayout->addItem(Space, 0, 4, 1, 1);

			Text_GCP = new QLabel(this);
			Text_GCP->setText("程序GCP模式");
			Text_GCP->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
			Text_GCP->setToolTip("更改此项设置允许程序启用内置的GCP解释模块，从而正常识别GPOL文件\nGPOL文件是本程序的galgame平台模式的脚本文件。");
			Text_GCP->setAlignment(Qt::AlignLeft);
			CurrentLayout->addWidget(Text_GCP, 1, 1, 1, 1);

			Edit_GCP = new QComboBox(this);
			Edit_GCP->addItem("禁用", 0);
			Edit_GCP->addItem("启用", 1);
			Edit_GCP->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei'}");
			if (Program_Settings("GCPMode") == "True") {
				Edit_GCP->setCurrentIndex(1);
			}
			else {
				Edit_GCP->setCurrentIndex(0);
			}
			CurrentLayout->addWidget(Edit_GCP, 1, 3, 1, 1);

			InitButton = new QPushButton(this);
			InitButton->setText("重设为默认值");
			InitButton->setStyleSheet("QPushButton{text-align:center;font-size:25px;font-family:'Microsoft YaHei'}");
			CurrentLayout->addWidget(InitButton, 10, 4, 1, 1);

			EnableButton = new QPushButton(this);
			EnableButton->setText("应用上述设置");
			EnableButton->setStyleSheet("QPushButton{text-align:center;font-size:25px;font-family:'Microsoft YaHei'}");
			CurrentLayout->addWidget(EnableButton, 11, 4, 1, 1);

			
		}
	public slots:
		void closeEvent(QCloseEvent* event) {
			emit windowIsClosed();
		}
		void showEvent(QShowEvent* event) {
			this->setFixedSize(this->width(), this->height());
		}
};

//更多高级信息
class hMoreInfo :public QWidget
{
	Q_OBJECT
	signals:
		void windowIsClosed(void);
	public:
		QLabel* Kernal_Version;
		QLabel* Kernal_Introduce;
		QLabel* Developer_Info;
		QGridLayout* CurrentLayout;
		int gX, gY;
		hMoreInfo(int X,int Y,QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
			this->setWindowTitle(msg("About_Info_More"));
			this->setMinimumSize(370, 150);
			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);

			Kernal_Version = new QLabel(this);
			Kernal_Version->setText(msg("About_Info_SPOLEnv") +"\n"+ Program_Info("SPEnv"));
			Kernal_Version->setStyleSheet("QLabel{font-size:30px;font-family:'Microsoft YaHei'}");
			Kernal_Version->setAlignment(Qt::AlignCenter);
			CurrentLayout->addWidget(Kernal_Version, 0, 0, 1, 1);

			Kernal_Introduce = new QLabel(this);
			Kernal_Introduce->setText("AASP是由Ayano_Aishi提出程序构想之后，由青雅音完成的最初版本的SPOL解释器程序。\
\n该解释器只有命令行状态，其后的拥有UI的Python版YSP程序在此命令行程序之上构建。\
\nC++版YSP程序亦使用了优化重构后的AASP内核。重构过程受到了来自Ayano_Aishi的支持。\
\n\
\n当前K9UT0内核为.9X设计，但是其表现与.6X的内核K6U2(应用于YSP版本0.7)一致。\n");
			Kernal_Introduce->setStyleSheet("QLabel{font-size:20px;font-family:'Microsoft YaHei'}");
			Kernal_Introduce->setAlignment(Qt::AlignCenter);
			CurrentLayout->addWidget(Kernal_Introduce, 1, 0, 1, 1);

			Developer_Info = new QLabel(this);
			Developer_Info->setText("策划：Ayano_Aishi\
\n开发者：青雅音\
\n开发支持：v0v_tempest、Ayano_Aishi\
\n美工：青雅音\
\n翻译：_低吟ゞ");
			Developer_Info->setAlignment(Qt::AlignCenter);
			Developer_Info->setStyleSheet("QLabel{font-size:20px;font-family:'Microsoft YaHei'}");
			CurrentLayout->addWidget(Developer_Info, 2, 0, 1, 1);

		}
	public slots:
		void closeEvent(QCloseEvent* event) {
			emit windowIsClosed();
		}
		void showEvent(QShowEvent* event) {
			this->setFixedSize(this->width(), this->height());
		}
};