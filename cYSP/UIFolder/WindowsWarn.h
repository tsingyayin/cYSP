#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtGui>
#include "..\global_value.h"
#include "..\loadsettings.h"
#include "..\langcontrol.h"
#include <windows.h>

class WindowsWarn :public QWidget
{
	Q_OBJECT
public:
	QLabel* TextLabel;
	QPushButton* Button;

	WindowsWarn(QWidget *parent = Q_NULLPTR) {
		this->setParent(parent);
		TextLabel = new QLabel(this);
		Button = new QPushButton(this);
		//this->setAttribute(Qt::WA_TranslucentBackground);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setStyleSheet("QWidget{background-color:#0078D4}");
		TextLabel->setGeometry(QRect(50, 10, 900, 200));
		TextLabel->setWordWrap(TRUE);
		TextLabel->setText("���Ǻܱ�Ǹ�ĸ�֪�������ڳ���ʹ�������°汾Windows10��11���ṩ��API�����YSP�����޷��������Ͼɰ汾Windowsϵͳ�Ϲ�����\n\
���������2018�꼰֮ǰ������Windowsϵͳ�ļ����Բ�뿼�����������°汾��Windows��ʹ�ó���");
		TextLabel->setStyleSheet("QLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:25px}");
		Button->setText("ȷ��");
		Button->setGeometry(QRect(800, 230, 160, 50));
		Button->setStyleSheet("QPushButton{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border:4px solid rgba(255,255,255,255);}\
QPushButton:hover{background-color:rgba(255,255,255,100);color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border:4px solid rgba(255,255,255,255);}\
QPushButton:Pressed{background-color:rgba(255,255,255,100);color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border:4px solid rgba(255,255,255,255);}");
		connect(Button, SIGNAL(clicked()), this, SLOT(exitProgram()));
		
		this->setFixedSize(1000,300);
	}
public slots:
	void exitProgram(void) {
		QApplication::instance()->quit();
	}
};

class WindowsWarn11 :public QWidget
{
	Q_OBJECT
public:
	QLabel* TextLabel;
	QPushButton* Button;

	WindowsWarn11(QWidget* parent = Q_NULLPTR) {
		this->setParent(parent);
		TextLabel = new QLabel(this);
		Button = new QPushButton(this);
		//this->setAttribute(Qt::WA_TranslucentBackground);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setStyleSheet("QWidget{background-color:#0078D4;}");
		TextLabel->setGeometry(QRect(50, 10, 900, 200));
		TextLabel->setWordWrap(TRUE);
		TextLabel->setText("��������ָ����YSP����ֻ���ڴ���Windows11��ʱ����������ʾ���뿼��������Windows11");
		TextLabel->setStyleSheet("QLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:25px}");
		Button->setText("ȷ��");
		Button->setGeometry(QRect(800, 230, 160, 50));
		Button->setStyleSheet("QPushButton{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border-radius:5px;border:1px solid rgba(255,255,255,255);}\
QPushButton:hover{background-color:rgba(255,255,255,100);color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border-radius:5px;border:1px solid rgba(255,255,255,255);}\
QPushButton:Pressed{background-color:rgba(255,255,255,100);color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border-radius:5px;border:1px solid rgba(255,255,255,255);}");
		connect(Button, SIGNAL(clicked()), this, SLOT(exitProgram()));

		this->setFixedSize(1000, 300);
	}
public slots:
	void exitProgram(void) {
		QApplication::instance()->quit();
	}
};

class WindowsWarnSPOL_6 :public QWidget
{
	Q_OBJECT
public:
	QLabel* TextLabel;
	QPushButton* Button;

	WindowsWarnSPOL_6(QWidget* parent = Q_NULLPTR) {
		this->setParent(parent);
		TextLabel = new QLabel(this);
		Button = new QPushButton(this);
		//this->setAttribute(Qt::WA_TranslucentBackground);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setStyleSheet("QWidget{background-color:#0078D4;}");
		TextLabel->setGeometry(QRect(50, 10, 900, 200));
		TextLabel->setWordWrap(TRUE);
		TextLabel->setText("SPOL.6X->SPOL.9XǨ����֪��\nSPOL�﷨��.6X(0.5.10��0.6.0��0.6.5)��.9X(0.9.0)֮�����޴����л��ھɰ�SPOL���ĵ�������ͨ��FollowNew��������ִ��\n\
�����򿪽�ѧ�ĵ������˽��°汾�ı仯���������޸����ľɰ汾�ĵ���\n\n�����ڽ�����չʾһ�Ρ�");
		TextLabel->setStyleSheet("QLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:25px}");
		Button->setText("ȷ��");
		Button->setGeometry(QRect(800, 230, 160, 50));
		Button->setStyleSheet("QPushButton{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border-radius:5px;border:1px solid rgba(255,255,255,255);}\
QPushButton:hover{background-color:rgba(255,255,255,100);color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border-radius:5px;border:1px solid rgba(255,255,255,255);}\
QPushButton:Pressed{background-color:rgba(255,255,255,100);color:#FFFFFF;font-family:'Microsoft YaHei';font-size:20px;border-radius:5px;border:1px solid rgba(255,255,255,255);}");
		connect(Button, SIGNAL(clicked()), this, SLOT(exitProgram()));

		this->setFixedSize(1000, 300);
	}
public slots:
	void exitProgram(void) {
		QApplication::instance()->quit();
	}
};
