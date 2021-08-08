#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <QCoreApplication>
#include <QDebug>
#include "../Aaspcommand/SPOLDevFunc.h"
#include "../langcontrol.h"
#include "..\global_value.h"
#include "..\Aaspcommand\aaspcommand.h"

using namespace std;

class SPOLDevWindow :public QWidget
{
	Q_OBJECT
public:

	QTimer* WhileInput;
	bool NowIsFree = TRUE;
	QTextEdit* SPOLEdit;
	QTextBrowser* LineNumLabel;
	QScrollBar* SPOLEditScroll;
	QScrollBar* LineNumScrollV;
	QScrollBar* LineNumScrollH;
	QGraphicsOpacityEffect* OPLineNumScrollV;
	QGraphicsOpacityEffect* OPLineNumScrollH;
	QLineEdit* SPOLFileNameLabel;
	QGridLayout* WindowLayout;
	QPushButton* OpenButton;
	QPushButton* SaveButton;
	QPushButton* NewFileButton;
	QPushButton* CloseProButton;
	QPushButton* FaRButton;
	QPushButton* EnableLinkModeButton;
	QPushButton* PlayButton;
	QString SPOLFileDialog;
	QString SPOLFileName = "";
	QFile SPOLFile;
	QString RawLine;


	SPOLDevWindow(QWidget* parent = Q_NULLPTR) {
		WhileInput = new QTimer(this);
		connect(WhileInput, SIGNAL(timeout()), this, SLOT(repaintWhileFree()));
		this->setGeometry(QRect(500, 200, 1024, 768));
		this->setWindowTitle("SPOL着色开发环境");
		this->setWindowIcon(QIcon("./Visual/source/WinICO/Videotape_Win11.ico"));
		this->setAttribute(Qt::WA_DeleteOnClose);
		WindowLayout = new QGridLayout();
		this->setLayout(WindowLayout);

		SPOLEdit = new QTextEdit(this);
		SPOLEdit->setStyleSheet("QTextEdit{font-size:20px;font-family:'Microsoft YaHei';}");
		setDefaultText();
		SPOLEdit->setLineWrapMode(QTextEdit::NoWrap);
		SPOLEdit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		SPOLEdit->installEventFilter(this);
		SPOLEditScroll = SPOLEdit->verticalScrollBar();
		WindowLayout->addWidget(SPOLEdit, 1, 1, 11, 11);

		LineNumLabel = new QTextBrowser(this);
		LineNumLabel->setMaximumWidth(100);
		LineNumLabel->setFocusPolicy(Qt::NoFocus);
		LineNumLabel->setStyleSheet("QTextEdit{font-size:20px;font-family:'Microsoft YaHei';background-color:#2266CCFF;}");
		LineNumLabel->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		LineNumScrollV = LineNumLabel->verticalScrollBar();
		LineNumScrollV->setStyleSheet("QScrollBar{width:0px;}");
		LineNumScrollH = LineNumLabel->horizontalScrollBar();
		LineNumScrollV->installEventFilter(this);
		LineNumScrollH->installEventFilter(this);
		OPLineNumScrollV = new QGraphicsOpacityEffect();
		OPLineNumScrollH = new QGraphicsOpacityEffect();
		OPLineNumScrollV->setOpacity(0);
		OPLineNumScrollH->setOpacity(0);
		LineNumScrollH->setGraphicsEffect(OPLineNumScrollH);
		LineNumScrollV->setGraphicsEffect(OPLineNumScrollV);
		WindowLayout->addWidget(LineNumLabel, 1, 0, 11, 1);

		OpenButton = new QPushButton(this);
		OpenButton->setText("打开SPOL");
		WindowLayout->addWidget(OpenButton, 0, 0, 1, 1);

		NewFileButton = new QPushButton(this);
		NewFileButton->setText("新建");
		WindowLayout->addWidget(NewFileButton, 0, 1, 1, 1);

		SaveButton = new QPushButton(this);
		SaveButton->setText("保存");
		WindowLayout->addWidget(SaveButton, 0, 2, 1, 1);

		SPOLFileNameLabel = new QLineEdit(this);
		SPOLFileNameLabel->setText("未命名文档");
		SPOLFileNameLabel->setStyleSheet("QLineEdit{background-color:#2266CCFF;}");
		WindowLayout->addWidget(SPOLFileNameLabel, 0, 3, 1, 3);

		FaRButton = new QPushButton(this);
		FaRButton->setText("查找和替换");
		WindowLayout->addWidget(FaRButton, 0, 6, 1, 1);

		EnableLinkModeButton = new QPushButton(this);
		EnableLinkModeButton->setText("文本链接");
		WindowLayout->addWidget(EnableLinkModeButton, 0, 7, 1, 1);

		PlayButton = new QPushButton(this);
		PlayButton->setText("播放（开发中）");
		WindowLayout->addWidget(PlayButton, 0, 8, 1, 2);

		connect(this->SaveButton, SIGNAL(clicked()), this, SLOT(saveSPOLFile()));
		connect(this->OpenButton, SIGNAL(clicked()), this, SLOT(openSPOLFile()));
		connect(this->FaRButton, SIGNAL(clicked()), this, SLOT(testSelect()));
		//connect(this->CloseProButton, SIGNAL(clicked()), this, SLOT(closeProgram()));
		connect(this->NewFileButton, SIGNAL(clicked()), this, SLOT(createNewFile()));
		//connect(this->SPOLEdit, SIGNAL(textChanged()), this, SLOT(repaintLineNum()));

		connect(this->SPOLEditScroll, SIGNAL(valueChanged(int)), this, SLOT(setSameValue(int)));

	}
	bool eventFilter(QObject* target, QEvent* event) {
		if (target == LineNumScrollV && event->type() == QEvent::Wheel) {
			event->accept();
			return 1;
		}
		if (target == SPOLEdit && event->type() == QEvent::KeyPress) {
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Return || keyEvent->key() == Qt::Key_Enter) {
				repaintColor(1);
				repaintLineNum(1);
				event->accept();
				return 1;
			}
			else {
				if (NowIsFree) {
					NowIsFree = FALSE;
					WhileInput->start(2000);
				}else {
					WhileInput->start(2000);
				}
				return 0;
			}
		}

		return 0;
	}
	void setDefaultText(void) {
		SPOLEdit->setHtml(setColor("#YSP自带着色开发环境，SPOLEnv版本0.1，兼容着色SPOL0.6+\n#使用SPOL创建您自己的剧情。\n\n/SPOL0.6.5-FollowNew\n"));
	}
public slots:
	void repaintWhileFree(void) {
		repaintColor(0);
		repaintLineNum(0);
		NowIsFree = TRUE;
		WhileInput->stop();
	}
	void testSelect(void) {
		//QTextDocument::FindBackward
		SPOLEdit->find("SPOL");
	}
	void setSameValue(int a) {
		LineNumScrollV->setValue(SPOLEditScroll->value());
	}
	void openSPOLFile(void) {
		QString CurrentPath = QDir::currentPath();
		SPOLFileDialog = QFileDialog::getOpenFileName(this, "选择一个SPOL文件", "./story", "SPOL File(*.spol)");
		SPOLFileName = SPOLFileDialog.mid(SPOLFileDialog.indexOf(CurrentPath)+CurrentPath.length());
		//SPOLFileName = SPOLFileDialog.section("/", -1, -1).section(".", 0, 0);
		SPOLFile.setFileName(SPOLFileDialog);
		SPOLFile.open(QIODevice::ReadOnly | QIODevice::Text);
		RawLine = SPOLFile.readAll();
		SPOLFile.close();
		this->setWindowTitle("SPOL着色开发环境——现在正在编辑：" + SPOLFileName);
		SPOLFileNameLabel->setText(SPOLFileName);
		RawLine = setColor(RawLine);
		SPOLEdit->setHtml(RawLine);
		repaintLineNum(0);
	}
	void saveSPOLFile(void) {
		SPOLFileName = SPOLFileNameLabel->text();
		SPOLFile.setFileName("."+SPOLFileName);
		SPOLFile.open(QIODevice::ReadWrite | QIODevice::Text);
		RawLine = SPOLFile.write(SPOLEdit->toPlainText().toUtf8());
		SPOLFile.close();
		//qDebug() << SPOLEdit->toPlainText();
	}
	void createNewFile(void) {
		saveSPOLFile();
		SPOLEdit->setText("");
		SPOLFileNameLabel->setText("未命名文档");
		this->setWindowTitle("SPOL着色开发环境——现在正在编辑：未命名文档.spol");
		repaintLineNum(0);
	}
	void repaintLineNum(bool isInput = 1) {
		QString Lineinfo;
		if (isInput) {
			Lineinfo = SPOLEdit->toPlainText() + "\n";
		}
		else {
			Lineinfo = SPOLEdit->toPlainText();
		}
		clock_t t1 = clock();
		int LineCount = Lineinfo.count("\n");
		clock_t t2 = clock();
		QString LineNumString = "";
		for (int i = 1; i <= LineCount; i++) {
			LineNumString.append(QString::number(i) + "<br>");
		}
		clock_t t3 = clock();
		qDebug() << "统计时间" << t2 - t1 << "毫秒，生成时间" << t3 - t2 << "毫秒。";
		LineNumLabel->setText("<div align='right'>" + LineNumString + "</div>");
		LineNumScrollV->setValue(SPOLEditScroll->value());
	}
	void repaintColor(bool isInput = 0) {
		QTextCursor Cursor;
		int cX, cY;
		Cursor = SPOLEdit->textCursor();
		if (isInput) {
			cX = Cursor.position() + 1;
			SPOLEdit->setHtml(setColor(SPOLEdit->toPlainText().mid(0,cX-1) + "\n"+SPOLEdit->toPlainText().mid(cX-1)));
		}
		else {
			cX = Cursor.position();
			SPOLEdit->setHtml(setColor(SPOLEdit->toPlainText()));
		}
		Cursor.setPosition(cX);
		SPOLEdit->setTextCursor(Cursor);
	}
	void closeProgram(void) {
		this->close();
		QApplication* qapp;
		qapp->exit(0);
	}
};