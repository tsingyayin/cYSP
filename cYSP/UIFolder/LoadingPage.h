#pragma once
#include <QtCore>
#include <QtWidgets>
#include <QtCore>
#pragma execution_character_set("utf-8")
#include "../loadsettings.h"
#include "../Aaspcommand/aaspcommand.h"
#include "../global_value.h"
#include <QTest>
#if DEPLOY == 1
class EnsureInstallKLite :public QWidget
{
	Q_OBJECT
signals:
	void isClosed();
public:
	QFrame* CentralWidget;
	QLabel* NoticeLabel;
	QPushButton* YesButton;
	QPushButton* NoButton;
	QGridLayout* CurrentLayout;
	EnsureInstallKLite(QWidget* parent = Q_NULLPTR) {
		this->setFixedSize(600, 300);
		this->setParent(parent);
		this->setWindowFlag(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);
		this->setStyleSheet("QWidget{color:#FFFFFF;font-family:'Microsoft YaHei'};");
		CentralWidget = new QFrame(this);
		CentralWidget->setStyleSheet("QFrame{background-color:#444444;border:3px solid #555555;border-radius:10px;}");
		CentralWidget->setFixedSize(600, 300);
		NoticeLabel = new QLabel(this);
		NoticeLabel->setText("请注意，未能在您计算机上的 C:/Program Files (x86)/K-Lite Codec Pack 或您指定的路径下找到DirectShow解码服务。\n该服务用于支持音视频解码。\n按下确定键，程序将自动添加解码服务到该指定路径，若您不想添加该服务，请单击取消，程序随后会退出。\
\n\n如果您已经在别处安装了此解码服务，请您退出程序，手动打开程序目录下的设置文件options.txt，并在项目'CodecPath'的等号后输入您的K-Lite Codec Pack安装位置以正常使用程序。");
		NoticeLabel->setWordWrap(TRUE);
		YesButton = new QPushButton(this);
		NoButton = new QPushButton(this);
		YesButton->setFixedHeight(30);
		NoButton->setFixedHeight(30);
		connect(YesButton, SIGNAL(clicked()), this, SLOT(isYes()));
		connect(NoButton, SIGNAL(clicked()), this, SLOT(isNo()));
		YesButton->setText("确定");
		NoButton->setText("取消");
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->addWidget(NoticeLabel, 0, 0, 1, 5);
		CurrentLayout->addWidget(NoButton, 1, 1, 1, 1);
		CurrentLayout->addWidget(YesButton, 1, 3, 1, 1);
		this->setLayout(CurrentLayout);
		YesButton->setStyleSheet("\
				QPushButton\
					{border:2px solid #1473E6;border-radius:10px;background-color:#555555;}\
				QPushButton:hover\
					{border:2px solid #1473E6;border-radius:10px;background-color:rgba(0,0,0,0);}\
				QPushButton:pressed\
					{border:2px solid #1473E6;border-radius:10px;background-color:#333333;}");
		NoButton->setStyleSheet("\
				QPushButton\
					{border:2px solid #D61921;border-radius:10px;background-color:#555555;}\
				QPushButton:hover\
					{border:2px solid #D61921;border-radius:10px;background-color:rgba(0,0,0,0);}\
				QPushButton:pressed\
					{border:2px solid #D61921;border-radius:10px;background-color:#333333;}");
	}
public slots:

	void isYes() {
		system((QDir::currentPath() + "/codec/klcp_basic_unattended.bat").toStdString().c_str());
		this->close();
	}
	void isNo() {
		qApp->exit(-1);
	}
	void closeEvent(QCloseEvent* event) {
		this->hide();
		emit isClosed();
		this->deleteLater();
	}
};
#endif
class LoadingPage :public QFrame
{
	Q_OBJECT
public:
	QFrame* CentralWidget;
	QLabel* TitleLabel;
	QLabel* NoticeLabel;
	QTimer* WaitTimer;
	LoadingPage() {
		this->setFixedSize(800, 400);
		this->setWindowFlag(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);
		CentralWidget = new QFrame(this);
		CentralWidget->setStyleSheet("QFrame{background-color:#00000000;border-radius:10px;border-image:url(':/IRC/InsiderSource/Icons/LoadingPage.png');}");
		TitleLabel = new QLabel(this);
		TitleLabel->setText("Yayin Story Player");
		NoticeLabel = new QLabel(this);
		NoticeLabel->setText("准备启动检查...");
		WaitTimer = new QTimer(this);
		connect(WaitTimer, SIGNAL(timeout()), this, SLOT(checking()));
		WaitTimer->setSingleShot(TRUE);
		WaitTimer->start(500);
	}
	void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
		CentralWidget->setGeometry(QRect(0, 0, width(), height()));
		TitleLabel->setGeometry(QRect(width() * 0.011, height() * 0.4, width() * 0.9, height() * 0.2));
		NoticeLabel->setGeometry(QRect(width() * 0.011, height() * 0.93, width() * 0.8, height() * 0.05));
		TitleLabel->setStyleSheet("QLabel{color:#FFFFFF;font-size:" + QString::number((int)(height() * 0.18)) + "px}");
		NoticeLabel->setStyleSheet("QLabel{color:#888888;font-size:" + QString::number((int)(height() * 0.05)) + "px}");
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
#if DEPLOY==1
		NoticeLabel->repaint();
		NoticeLabel->setText("检查K-Lite解码器");
		NoticeLabel->repaint();
		QString CodecPath = Program_Settings("CodecPath") == "__Default__" ? "C:/Program Files (x86)/K-Lite Codec Pack" : Program_Settings("CodecPath");
		QDir KLiteDir = CodecPath;
		if (!KLiteDir.exists()) {
			EnsureInstallKLite* NoticePage = new EnsureInstallKLite();
			connect(NoticePage, SIGNAL(isClosed()), this, SLOT(checking_()));
			NoticePage->show();
		}
		else {
			checking_();
		}
#elif DEPLOY == 2
		checking_();
#endif
	}
	void checking_() {
		NoticeLabel->setText(msg("Kernal_Text_IFL_Version").arg("IFL_20211227"));
		NoticeLabel->repaint();
		QTest::qSleep(500);
		qApp->exit(0);
	}
};