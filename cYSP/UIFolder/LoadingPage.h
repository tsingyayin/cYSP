#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtCore>
#pragma execution_character_set("utf-8")
#include "../loadsettings.h"
#include "../Aaspcommand/aaspcommand.h"
#include "../global_value.h"
#include <QTest>

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
		for (float i = 0; i <= 3.1415 / 2; i += 0.02) {
			QTest::qSleep(1);
			Effect->setOpacity(1 - qSin(i));
			CentralWidget->repaint();
		}
		qApp->exit(0);
	}
};