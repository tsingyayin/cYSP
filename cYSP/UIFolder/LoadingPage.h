#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtCore>
#pragma execution_character_set("utf-8")
#include "../loadsettings.h"
#include "../Aaspcommand/aaspcommand.h"
#include "../global_value.h"
#include <QTest>

class CENotice :public QWidget
{
	Q_OBJECT
signals:
	void isClosed();
public:
	QFrame* CentralWidget;
	QLabel* NoticeLabel;
	QPushButton* YesButton;
	QGridLayout* CurrentLayout;
	CENotice(QWidget* parent = Q_NULLPTR) {
		this->setFixedSize(800, 300);
		this->setParent(parent);
		this->setWindowFlag(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);
		this->setWindowModality(Qt::ApplicationModal);
		this->setStyleSheet("QWidget{color:#000000;};");
		CentralWidget = new QFrame(this);
		CentralWidget->setStyleSheet("QFrame{background-color:#FFFFFF;border:0px solid #555555;border-radius:10px;}");
		CentralWidget->setFixedSize(800, 300);
		NoticeLabel = new QLabel(this);
		NoticeLabel->setText("光 敏 性 癫 痫 警 告\n\n\
有极少数人在观看某些视觉内容时会突然癫痫发作，即使这些人并无癫痫病史。\n\
程序本体中可能含有令您感到不适的程序动画行为，包括但不限于闪烁，渐变等等。\n\
由您创建、编写或打开、预览的任一项目中亦可能存在会导致您感到不适的程序运行定义。\n\
\n\
不适症状包括但不限于头晕目眩，四肢、面部发生抽搐，甚至是神志不清、暂时失去意识等。\n\
若您在使用程序时感到不适，应当立即退出程序或直接远离屏幕。若症状未能得到缓解，您应当立即向医生或医师求助，并遵医嘱。\n\
");
		NoticeLabel->setAlignment(Qt::AlignCenter);
		NoticeLabel->setWordWrap(TRUE);
		YesButton = new QPushButton(this);
		YesButton->setFixedHeight(30);
		connect(YesButton, SIGNAL(clicked()), this, SLOT(isYes()));
		YesButton->setText("确定");
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->addWidget(NoticeLabel, 0, 0, 1, 5);
		CurrentLayout->addWidget(YesButton, 1, 2, 1, 1);
		this->setLayout(CurrentLayout);
		YesButton->setStyleSheet("\
				QPushButton\
					{border:2px solid #1473E6;border-radius:10px;background-color:#FFFFFF;}\
				QPushButton:hover\
					{border:2px solid #1473E6;border-radius:10px;background-color:#EEEEEE;}\
				QPushButton:pressed\
					{border:2px solid #1473E6;border-radius:10px;background-color:#DDDDDD;}");
	}
public slots:

	void isYes() {
		this->close();
	}
	void isNo() {
		this->close();
	}
	void closeEvent(QCloseEvent* event) {
		this->hide();
		this->repaint();
		emit isClosed();
		this->disconnect();
		this->deleteLater();
	}
	void mousePressEvent(QMouseEvent* event) {

	}
};

class LoadingPage :public QFrame
{
	Q_OBJECT
public:
	QFrame* CentralWidget;
	QLabel* TitleLabel;
	QLabel* NoticeLabel;
	QTimer* WaitTimer;
	QGraphicsOpacityEffect* Effect;
	LoadingPage() {
		this->setFixedSize(800, 300);
		this->setWindowFlag(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);
		CentralWidget = new QFrame(this);
		Effect = new QGraphicsOpacityEffect(this);
		Effect->setOpacity(1);
		this->setGraphicsEffect(Effect);
		CentralWidget->setStyleSheet("QFrame{background-color:#00000000;border-radius:10px;border-image:url(':/IRC/InsiderSource/Icons/LoadingPage.png');}");
		TitleLabel = new QLabel(this);
		//TitleLabel->setText("VisIndigo");
		NoticeLabel = new QLabel(this);
		NoticeLabel->setText("准备启动检查...");
		NoticeLabel->setAlignment(Qt::AlignCenter);
		WaitTimer = new QTimer(this);
		connect(WaitTimer, SIGNAL(timeout()), this, SLOT(checking()));
		WaitTimer->setSingleShot(TRUE);
		WaitTimer->start(500);
	}
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		CentralWidget->setGeometry(QRect(0, 0, width(), height()));
		TitleLabel->setGeometry(QRect(width() * 0.011, height() * 0.4, width() * 0.9, height() * 0.2));
		NoticeLabel->setGeometry(QRect(width() * 0.1, height() * 0.89, width() * 0.8, height() * 0.08));
		TitleLabel->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + QString::number((int)(height() * 0.18)) + "px}");
		NoticeLabel->setStyleSheet("QLabel{color:#444444;font-size:" + QString::number((int)(height() * 0.07)) + "px}");
	}
public slots:
	void checking(void) {
		NoticeLabel->setText(PROINFO::Kernal + "\t" + PROINFO::Total);
		QTest::qSleep(300);
		NoticeLabel->repaint();
		NoticeLabel->setText("Check Files");
		ensuredirs(0);
		QTest::qSleep(100);
		NoticeLabel->repaint();
		NoticeLabel->setText("Load Language");
		langset("0");
		QTest::qSleep(100);
		NoticeLabel->repaint();
		NoticeLabel->setText("Load Settings");
		loadsettings();
		QTest::qSleep(100);
		NoticeLabel->repaint();
		NoticeLabel->setText("Delete Cache");
		DeleteCache(0);
		QTest::qSleep(100);
		NoticeLabel->repaint();
		checking_();
	}
	void checking_() {
		NoticeLabel->setText(msg("Kernal_Text_IFL_Version").arg("IFL_20211227"));
		NoticeLabel->repaint();
		QTest::qSleep(500);
		CENotice* notice = new CENotice();
		notice->show();
		connect(notice, SIGNAL(isClosed()), this, SLOT(checking__()));
	}
	void checking__() {
		QTest::qSleep(100);
		for (float i = 0; i <= 3.1415 / 2; i += 0.02) {
			QTest::qSleep(1);
			Effect->setOpacity(1 - qSin(i));
			CentralWidget->repaint();
		}
		qApp->exit(0);
	}
};