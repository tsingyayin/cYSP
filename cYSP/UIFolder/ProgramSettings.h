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
#include <exception>
using namespace std;

//����ͨ������
class hProgramSettings :public QWidget
{
	Q_OBJECT
signals:
	void windowIsClosed(void);
public:
	QSpacerItem* Space1;
	QSpacerItem* Space2;
	QSpacerItem* Space3;
	QGridLayout* CurrentLayout;

	QLabel* Text_Window_DisplayMode;
	QComboBox* Edit_Window_DisplayMode;
	QLabel* Text_Window_Geometry;
	QComboBox* Edit_Window_Geometry;

	QPushButton* InitButton;
	QPushButton* EnableButton;
	int gX, gY;
	hProgramSettings(int X, int Y, QWidget* parent = Q_NULLPTR) {
		this->setParent(parent);
		this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
		this->setAttribute(Qt::WA_DeleteOnClose);
		this->setWindowTitle(msg("Ui_SettingsPage_Normal_Settings"));

		CurrentLayout = new QGridLayout(this);
		this->setLayout(CurrentLayout);

		Space1 = new QSpacerItem(40, 0);
		Space2 = new QSpacerItem(40, 0);
		Space3 = new QSpacerItem(40, 0);
		CurrentLayout->addItem(Space1, 0, 0, 1, 1);
		CurrentLayout->addItem(Space2, 0, 2, 1, 1);
		CurrentLayout->addItem(Space3, 0, 4, 1, 1);

		Text_Window_DisplayMode = new QLabel(this);
		Text_Window_DisplayMode->setText(msg("Ui_Settings_WindowDisplayMode_Label"));
		Text_Window_DisplayMode->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
		Text_Window_DisplayMode->setToolTip(msg("Ui_Settings_WindowDisplayMode_Text"));
		Text_Window_DisplayMode->setAlignment(Qt::AlignLeft);
		CurrentLayout->addWidget(Text_Window_DisplayMode, 0, 1, 1, 1);

		Edit_Window_DisplayMode = new QComboBox(this);
		Edit_Window_DisplayMode->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei';}");
		Edit_Window_DisplayMode->addItem(msg("Ui_Settings_Common_FullScreen"), 0);
		Edit_Window_DisplayMode->addItem(msg("Ui_Settings_Common_Window"), 1);
		Edit_Window_DisplayMode->setView(new QListView(this));

		if (Program_Settings("Window_DisplayMode") == "Window") {
			Edit_Window_DisplayMode->setCurrentIndex(1);
		}
		else {
			Edit_Window_DisplayMode->setCurrentIndex(0);
		}
		CurrentLayout->addWidget(Edit_Window_DisplayMode, 0, 3, 1, 1);

		Text_Window_Geometry = new QLabel(this);
		Text_Window_Geometry->setText(msg("Ui_Settings_WindowGeometry_Label"));
		Text_Window_Geometry->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
		Text_Window_Geometry->setToolTip(msg("Ui_Settings_WindowGeometry_Text"));
		Text_Window_Geometry->setAlignment(Qt::AlignLeft);
		CurrentLayout->addWidget(Text_Window_Geometry, 1, 1, 1, 1);

		QList<QStringList> GeometryList;
		GeometryList.append({ "1366x768", "0" });
		GeometryList.append({ "1600x900", "1" });
		GeometryList.append({ "1920x1080", "2" });
		GeometryList.append({ "2560x1440", "3" });
		GeometryList.append({ "3840x2160", "4" });

		Edit_Window_Geometry = new QComboBox(this);
		Edit_Window_Geometry->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei'}");
		for (int i = 0; i < GeometryList.length(); i++) {
			Edit_Window_Geometry->addItem(GeometryList[i][0], GeometryList[i][1].toInt());
		}

		for (int i = 0; i < GeometryList.length(); i++) {
			if (GeometryList[i][0].replace("x","_") == Program_Settings("Window_Geometry")) {
				Edit_Window_Geometry->setCurrentIndex(GeometryList[i][1].toInt());
				break;
			}
		}
		Edit_Window_Geometry->setView(new QListView(this));
		
		CurrentLayout->addWidget(Edit_Window_Geometry, 1, 3, 1, 1);

		InitButton = new QPushButton(this);
		InitButton->setText(msg("Ui_SettingsPage_Reset_Parameters"));
		InitButton->setStyleSheet("QPushButton{text-align:center;font-size:25px;font-family:'Microsoft YaHei'}");
		connect(InitButton, SIGNAL(clicked()), this, SLOT(resetAll()));
		CurrentLayout->addWidget(InitButton, 10, 4, 1, 1);

		EnableButton = new QPushButton(this);
		EnableButton->setText(msg("Ui_SettingsPage_Apply_Parameters"));
		EnableButton->setStyleSheet("QPushButton{text-align:center;font-size:25px;font-family:'Microsoft YaHei'}");
		connect(EnableButton, SIGNAL(clicked()), this, SLOT(applySettings()));
		CurrentLayout->addWidget(EnableButton, 11, 4, 1, 1);

	}

public slots:
	void resetAll(void) {
		writesettings("Window_DisplayMode", "Full");
		writesettings("Window_Geometry", "1366_768");
		this->close();
	}
	void applySettings(void) {
		int WindowDisplayModeSet = Edit_Window_DisplayMode->currentIndex();
		if (WindowDisplayModeSet == 0) { writesettings("Window_DisplayMode", "Full"); }
		if (WindowDisplayModeSet == 1) { writesettings("Window_DisplayMode", "Window"); }

		QString WindowGeometrySet = Edit_Window_Geometry->currentText();
		writesettings("Window_Geometry", WindowGeometrySet.replace("x", "_"));
	}
	void closeEvent(QCloseEvent* event) {
		emit windowIsClosed();
	}
	void showEvent(QShowEvent* event) {
		this->setFixedSize(this->width(), this->height());
	}
};


//����������
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
		QLabel* Text_Forced_Debugging;
		QComboBox* Edit_Forced_Debugging;
		QSpacerItem* Space1;
		QSpacerItem* Space2;
		QSpacerItem* Space3;
		QGridLayout* CurrentLayout;
		QPushButton* InitButton;
		QPushButton* EnableButton;
		
		hDevSettings(int X, int Y, QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
			this->setWindowTitle(msg("Ui_SettingsPage_Dev_Settings"));
			this->setAttribute(Qt::WA_DeleteOnClose);
			CurrentLayout = new QGridLayout(this);
			this->setLayout(CurrentLayout);

			Text_Dev = new QLabel(this);
			Text_Dev->setText(msg("Ui_Settings_ChooseChannel_Label"));
			Text_Dev->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
			Text_Dev->setToolTip(msg("Ui_Settings_ChooseChannel_Text"));
			Text_Dev->setAlignment(Qt::AlignLeft);
			CurrentLayout->addWidget(Text_Dev, 0, 1, 1, 1);

			Edit_Dev = new QComboBox(this);
			Edit_Dev->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei';}");
			Edit_Dev->addItem(msg("Ui_Text_Common_Auto"), 0);
			Edit_Dev->addItem(msg("Ui_Text_Common_Pre"), 1);
			Edit_Dev->addItem(msg("Ui_Text_Common_Pub"), 2);
			Edit_Dev->setView(new QListView(this));

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

			Space1 = new QSpacerItem(40,0);
			Space2 = new QSpacerItem(40,0);
			Space3 = new QSpacerItem(40,0);
			CurrentLayout->addItem(Space1, 0, 0, 1, 1);
			CurrentLayout->addItem(Space2, 0, 2, 1, 1);
			CurrentLayout->addItem(Space3, 0, 4, 1, 1);
			
			Text_GCP = new QLabel(this);
			Text_GCP->setText(msg("Ui_Settings_GCPMode_Label"));
			Text_GCP->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
			Text_GCP->setToolTip(msg("Ui_Settings_GCPMode_Text"));
			Text_GCP->setAlignment(Qt::AlignLeft);
			CurrentLayout->addWidget(Text_GCP, 1, 1, 1, 1);

			Edit_GCP = new QComboBox(this);
			Edit_GCP->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei'}");
			Edit_GCP->addItem(msg("Ui_Text_Common_Disable"), 0);
			Edit_GCP->addItem(msg("Ui_Text_Common_Enable"), 1);		
			Edit_GCP->setView(new QListView(this));

			if (Program_Settings("GCPMode") == "True") {
				Edit_GCP->setCurrentIndex(1);
			}
			else {
				Edit_GCP->setCurrentIndex(0);
			}
			CurrentLayout->addWidget(Edit_GCP, 1, 3, 1, 1);

			Text_Forced_Debugging = new QLabel(this);
			Text_Forced_Debugging->setText(msg("Ui_Settings_ForcedDebugging_Label"));
			Text_Forced_Debugging->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
			Text_Forced_Debugging->setToolTip(msg("Ui_Settings_ForcedDebugging_Text"));
			Text_Forced_Debugging->setAlignment(Qt::AlignLeft);
			CurrentLayout->addWidget(Text_Forced_Debugging, 2, 1, 1, 1);

			Edit_Forced_Debugging = new QComboBox(this);
			Edit_Forced_Debugging->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei'}");
			Edit_Forced_Debugging->addItem(msg("Ui_Text_Common_Disable"), 0);
			Edit_Forced_Debugging->addItem(msg("Ui_Text_Common_Enable"), 1);
			Edit_Forced_Debugging->setView(new QListView(this));

			if (Program_Settings("Forced_Debugging_Info") == "True") {
				Edit_Forced_Debugging->setCurrentIndex(1);
			}
			else {
				Edit_Forced_Debugging->setCurrentIndex(0);
			}
			CurrentLayout->addWidget(Edit_Forced_Debugging, 2, 3, 1, 1);

			InitButton = new QPushButton(this);
			InitButton->setText(msg("Ui_SettingsPage_Reset_Parameters"));
			InitButton->setStyleSheet("QPushButton{text-align:center;font-size:25px;font-family:'Microsoft YaHei'}");
			connect(InitButton, SIGNAL(clicked()), this, SLOT(resetAll()));
			CurrentLayout->addWidget(InitButton, 10, 4, 1, 1);
			
			EnableButton = new QPushButton(this);
			EnableButton->setText(msg("Ui_SettingsPage_Apply_Parameters"));
			EnableButton->setStyleSheet("QPushButton{text-align:center;font-size:25px;font-family:'Microsoft YaHei'}");
			connect(EnableButton, SIGNAL(clicked()), this, SLOT(applySettings()));
			CurrentLayout->addWidget(EnableButton, 11, 4, 1, 1);

			
		}
		~hDevSettings() {
			//delete Space;
		}
	public slots:
		void resetAll(void) {
			writesettings("Update_Channel","Auto");
			writesettings("GCPMode","False");
			writesettings("Forced_Debugging_Info", "False");
			this->close();
		}
		void applySettings(void) {
			int UpdateChannelSet = Edit_Dev->currentIndex();
			if (UpdateChannelSet == 0) { writesettings("Update_Channel", "Auto"); }
			else if (UpdateChannelSet == 1) { writesettings("Update_Channel", "Pre"); }
			else if (UpdateChannelSet == 2) { writesettings("Update_Channel", "Pub"); }

			int GCPModSet = Edit_GCP->currentIndex();
			if (GCPModSet == 0) { writesettings("GCPMode", "False"); }
			if (GCPModSet == 1) { writesettings("GCPMode", "True"); }

			int Forced_Debugging_Set = Edit_Forced_Debugging->currentIndex();
			if (Forced_Debugging_Set == 0) { writesettings("Forced_Debugging_Info", "False"); }
			if (Forced_Debugging_Set == 1) { writesettings("Forced_Debugging_Info", "True"); }
		}
		void closeEvent(QCloseEvent* event) {
			emit windowIsClosed();
		}
		void showEvent(QShowEvent* event) {
			this->setFixedSize(this->width(), this->height());
		}
};

//����߼���Ϣ
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
			this->setWindowTitle(msg("Ui_Text_Common_About_"));
			this->setMinimumSize(370, 150);
			this->setAttribute(Qt::WA_DeleteOnClose);


			CurrentLayout = new QGridLayout(this);
			this->setLayout(CurrentLayout);

			Kernal_Version = new QLabel(this);
			Kernal_Version->setText(msg("KAU_About_Info_SPOLEnv") +"\n"+ Program_Info("SPEnv"));
			Kernal_Version->setStyleSheet("QLabel{font-size:30px;font-family:'Microsoft YaHei'}");
			Kernal_Version->setAlignment(Qt::AlignCenter);
			CurrentLayout->addWidget(Kernal_Version, 0, 0, 1, 1);

			Kernal_Introduce = new QLabel(this);
			Kernal_Introduce->setText("AASP����Ayano_Aishi���������֮������������ɵ�����汾��SPOL����������\
\n�ý�����ֻ��������״̬������ӵ��UI��Python��YSP�����ڴ������г���֮�Ϲ�����\
\nC++��YSP������ʹ�����Ż��ع����AASP�ںˡ��ع������ܵ�������Ayano_Aishi��֧�֡�\
\n\
\n��ǰK9UT0�ں�Ϊ.9X��ƣ������䶥�������.6X���ں�K6U2(Ӧ����YSP�汾0.7)һ�¡�\
\nK9UT0��K6U2�����ϸĽ�����ص��㷨���Ӷ�ʵ���˸���Ч���˾������ٶȡ����͵�\
\n�Ķ�̬�����ӳ��������İ���ʶ���߼������ͬʱ���µ��˾��߼�Ϊ�°汾SPOL\
\n�����˼�ʵ�Ļ������������պ���п��ٸ��µ�����\
\n\
\n�������ں����൱�������������ε��زġ���Щ�زİ�Ȩ�������������С�\
\n�������ȡ��Щ�ز����ڳ���UI���֣���Ϊ�û��ṩ���ٶ����Ĺ��ܡ�\
\n�κ�����δ����Ȩ��������ɵ�����¶�����ʹ����ֱ�ӽ���ӯ����\
\n�����κ�ʹ�������زĶ����µ���Ȩ��Ϊ�������򿪷��߸Ų�����\n\n");

			Kernal_Introduce->setStyleSheet("QLabel{font-size:20px;font-family:'Microsoft YaHei'}");
			Kernal_Introduce->setAlignment(Qt::AlignCenter);
			CurrentLayout->addWidget(Kernal_Introduce, 1, 0, 1, 1);

			Developer_Info = new QLabel(this);
			Developer_Info->setText("\
\n�����ߣ�������\
\n����֧�֣�v0v_tempest��Ayano_Aishi\
\n������������\
\n���룺��������_�����g\
\n���ԣ�The_Universe������īѩ");
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