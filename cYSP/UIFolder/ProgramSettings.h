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

//����ͨ������
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
		QSpacerItem* Space;
		QGridLayout* CurrentLayout;
		QPushButton* InitButton;
		QPushButton* EnableButton;
		
		hDevSettings(int X, int Y, QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			this->setWindowFlags(this->windowFlags() & ~Qt::WindowMinMaxButtonsHint | Qt::WindowMinimizeButtonHint);
			this->setWindowTitle("YSP����߼��趨");

			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);

			Text_Dev = new QLabel(this);
			Text_Dev->setText("ѡ�����ͨ��");
			Text_Dev->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
			Text_Dev->setToolTip("���Ĵ������ÿ��Ըı䵱ǰ���ո�����Ϣ���ѵ�ͨ����\n�Զ�ģʽ����ѭ��ʹ�õ�����汾����ƥ�䣬ʹ������ѡ��ǿ��ָ����Ӧͨ����\n������ǹ����汾�û����������л����ڲ�����֮ǰ���ؿ��ǣ���Ϊ�ڲ����԰汾���и���Bug�����������ƻ������е�SPOL�ĵ���");
			Text_Dev->setAlignment(Qt::AlignLeft);
			CurrentLayout->addWidget(Text_Dev, 0, 1, 1, 1);

			Edit_Dev = new QComboBox(this);
			Edit_Dev->addItem("�Զ�(Auto)", 0);
			Edit_Dev->addItem("�ڲ���������(Pre)", 1);
			Edit_Dev->addItem("������������(Pub)", 2);
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
			Text_GCP->setText("����GCPģʽ");
			Text_GCP->setStyleSheet("QLabel{font-size:25px;font-family:'Microsoft YaHei'}");
			Text_GCP->setToolTip("���Ĵ���������������������õ�GCP����ģ�飬�Ӷ�����ʶ��GPOL�ļ�\nGPOL�ļ��Ǳ������galgameƽ̨ģʽ�Ľű��ļ���");
			Text_GCP->setAlignment(Qt::AlignLeft);
			CurrentLayout->addWidget(Text_GCP, 1, 1, 1, 1);

			Edit_GCP = new QComboBox(this);
			Edit_GCP->addItem("����", 0);
			Edit_GCP->addItem("����", 1);
			Edit_GCP->setStyleSheet("QComboBox{font-size:25px;font-family:'Microsoft YaHei'}");
			if (Program_Settings("GCPMode") == "True") {
				Edit_GCP->setCurrentIndex(1);
			}
			else {
				Edit_GCP->setCurrentIndex(0);
			}
			CurrentLayout->addWidget(Edit_GCP, 1, 3, 1, 1);

			InitButton = new QPushButton(this);
			InitButton->setText("����ΪĬ��ֵ");
			InitButton->setStyleSheet("QPushButton{text-align:center;font-size:25px;font-family:'Microsoft YaHei'}");
			CurrentLayout->addWidget(InitButton, 10, 4, 1, 1);

			EnableButton = new QPushButton(this);
			EnableButton->setText("Ӧ����������");
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
			Kernal_Introduce->setText("AASP����Ayano_Aishi���������֮������������ɵ�����汾��SPOL����������\
\n�ý�����ֻ��������״̬������ӵ��UI��Python��YSP�����ڴ������г���֮�Ϲ�����\
\nC++��YSP������ʹ�����Ż��ع����AASP�ںˡ��ع������ܵ�������Ayano_Aishi��֧�֡�\
\n\
\n��ǰK9UT0�ں�Ϊ.9X��ƣ������������.6X���ں�K6U2(Ӧ����YSP�汾0.7)һ�¡�\n");
			Kernal_Introduce->setStyleSheet("QLabel{font-size:20px;font-family:'Microsoft YaHei'}");
			Kernal_Introduce->setAlignment(Qt::AlignCenter);
			CurrentLayout->addWidget(Kernal_Introduce, 1, 0, 1, 1);

			Developer_Info = new QLabel(this);
			Developer_Info->setText("�߻���Ayano_Aishi\
\n�����ߣ�������\
\n����֧�֣�v0v_tempest��Ayano_Aishi\
\n������������\
\n���룺_�����g");
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