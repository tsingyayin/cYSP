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
		TextLabel->setText("我们很抱歉的告知您，由于程序使用了由新版本Windows10（11）提供的API，因此YSP程序无法在您的老旧版本Windows系统上工作。\n\
本程序对于2018年及之前发布的Windows系统的兼容性差。请考虑升级到最新版本的Windows以使用程序");
		TextLabel->setStyleSheet("QLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:25px}");
		Button->setText("确定");
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
		TextLabel->setText("必须向您指出，YSP程序只有在处于Windows11上时才能正常显示，请考虑升级到Windows11");
		TextLabel->setStyleSheet("QLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:25px}");
		Button->setText("确定");
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
		TextLabel->setText("SPOL.6X->SPOL.9X迁移须知：\nSPOL语法在.6X(0.5.10、0.6.0、0.6.5)与.9X(0.9.0)之间差异巨大，所有基于旧版SPOL的文档都不能通过FollowNew机制正常执行\n\
请您打开教学文档重新了解新版本的变化，并按需修改您的旧版本文档。\n\n本窗口仅对您展示一次。");
		TextLabel->setStyleSheet("QLabel{color:#FFFFFF;font-family:'Microsoft YaHei';font-size:25px}");
		Button->setText("确定");
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
