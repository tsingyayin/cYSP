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

class SPOLController :public QGroupBox
{
	Q_OBJECT
	public:

		QGridLayout* CurrentLayout;

		QPushButton* Edition_C;
		QPushButton* Title_C;
		QPushButton* BGP_C;
		QPushButton* Sound_C;
		QPushButton* Speak_C;
		QPushButton* Free_C;
		QPushButton* Branch_C;
		QPushButton* Jump_C;

		SPOLController(QWidget *parent=Q_NULLPTR) {
			this->setParent(parent);
			this->setTitle("控制器列表");
			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);

			Edition_C = new QPushButton(this);
			Edition_C->setText("版本控制器");
			CurrentLayout->addWidget(Edition_C, 0, 1, 1, 1);

			Title_C = new QPushButton(this);
			Title_C->setText("标题控制器");
			CurrentLayout->addWidget(Title_C, 0, 0, 1, 1);

			BGP_C = new QPushButton(this);
			BGP_C->setText("背景控制器");
			CurrentLayout->addWidget(BGP_C, 1, 0, 1, 1);

			Sound_C = new QPushButton(this);
			Sound_C->setText("音乐\\音效控制器");
			CurrentLayout->addWidget(Sound_C, 1, 1, 1, 1);

			Speak_C = new QPushButton(this);
			Speak_C->setText("讲述控制器");
			CurrentLayout->addWidget(Speak_C, 2, 0, 1, 1);

			Free_C = new QPushButton(this);
			Free_C->setText("自由文本控制器");
			CurrentLayout->addWidget(Free_C, 2, 1, 1, 1);

			Branch_C = new QPushButton(this);
			Branch_C->setText("小分支控制器");
			CurrentLayout->addWidget(Branch_C, 3, 0, 1, 1);

			Jump_C = new QPushButton(this);
			Jump_C->setText("大分支控制器");
			CurrentLayout->addWidget(Jump_C, 3, 1, 1, 1);
		}
};

class SoundSub :public QWidget
{
	Q_OBJECT
	public:
		QRadioButton* BGMSub;
		QRadioButton* AcousticsSub;
		QGridLayout* CurrentLayout;
		QButtonGroup* CurrentGroup;
		SoundSub(QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			BGMSub = new QRadioButton(this);
			AcousticsSub = new QRadioButton(this);

			BGMSub->setText("音乐控制器");
			AcousticsSub->setText("音效控制器");

			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);
			CurrentLayout->addWidget(BGMSub, 0, 0, 1, 1);
			CurrentLayout->addWidget(AcousticsSub, 1, 0, 1, 1);

			CurrentGroup = new QButtonGroup(this);
			CurrentGroup->addButton(BGMSub, 0);
			CurrentGroup->addButton(AcousticsSub, 1);
		}
};

class SpeakMain :public QWidget
{
	Q_OBJECT
	public:
		QGridLayout* CurrentLayout;

		QLabel* Text_1_Name;
		QLabel* Text_2_Name;

		QLabel* Text_Emotion;
		QLabel* Text_Flip;
		QLabel* Text_Filter;
		QLabel* Text_Call;

		QLineEdit* Edit_1_Name;
		QLineEdit* Edit_1_Emotion;
		QComboBox* Edit_1_Flip;
		QComboBox* Edit_1_Filter;
		QLineEdit* Edit_1_Call;

		QLineEdit* Edit_2_Name;
		QLineEdit* Edit_2_Emotion;
		QComboBox* Edit_2_Flip;
		QComboBox* Edit_2_Filter;
		QLineEdit* Edit_2_Call;

		QTextEdit* Edit_Said;

		QRadioButton* Follow1;
		QRadioButton* Follow2;
		QButtonGroup* FollowWho;

		QLabel* Text_Word_Interval;
		QLabel* Text_Word_Wait;
		QLineEdit* Edit_Word_Interval;
		QLineEdit* Edit_Word_Wait;

		QPushButton* ClearButton;
		QPushButton* UpdateButton;
		QPushButton* FillButton;

		QList<QStringList> FilterList;
		QList<QStringList> FlipList;
		SpeakMain(QWidget *parent = Q_NULLPTR) {
			this->setParent(parent);
			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);
			Text_1_Name = new QLabel(this);
			Text_1_Name->setText("第一人名称");
			
			Text_2_Name = new QLabel(this);
			Text_2_Name->setText("第二人名称");

			Text_Emotion = new QLabel(this);
			Text_Emotion->setText("表情");
			Text_Emotion->setAlignment(Qt::AlignCenter);

			Text_Flip = new QLabel(this);
			Text_Flip->setText("翻转");
			Text_Flip->setAlignment(Qt::AlignCenter);
			Text_Filter = new QLabel(this);
			Text_Filter->setText("滤镜选项");
			Text_Filter->setAlignment(Qt::AlignCenter);
			Text_Call = new QLabel(this);
			Text_Call->setText("别名");
			Text_Call->setAlignment(Qt::AlignCenter);

			FilterList.append(QStringList({ "无特效","0" }));
			FilterList.append(QStringList({ "上隐藏","1" }));
			FilterList.append(QStringList({ "褪色","2" }));
			FilterList.append(QStringList({ "褪色上隐藏","3" }));
			FilterList.append(QStringList({ "黑白","4" }));
			FilterList.append(QStringList({ "黑白上隐藏","5" }));

			FlipList.append(QStringList({ "不翻转","0" }));
			FlipList.append(QStringList({ "翻转","1" }));

			Edit_1_Name = new QLineEdit(this);
			Edit_1_Emotion = new QLineEdit(this);
			Edit_1_Flip = new QComboBox(this);		
			Edit_1_Filter = new QComboBox(this);		
			Edit_1_Call = new QLineEdit(this);
			
			Edit_2_Name = new QLineEdit(this);
			Edit_2_Emotion = new QLineEdit(this);
			Edit_2_Flip = new QComboBox(this);
			Edit_2_Filter = new QComboBox(this);
			Edit_2_Call = new QLineEdit(this);

			for (int i = 0; i < FlipList.length(); i++) {
				Edit_1_Flip->addItem(FlipList[i][0], FlipList[i][1].toInt());
				Edit_2_Flip->addItem(FlipList[i][0], FlipList[i][1].toInt());
			}
			for (int i = 0; i < FilterList.length(); i++) {
				Edit_1_Filter->addItem(FilterList[i][0], FilterList[i][1].toInt());
				Edit_2_Filter->addItem(FilterList[i][0], FilterList[i][1].toInt());
			}

			Edit_Said = new QTextEdit(this);

			Follow1 = new QRadioButton(this);
			Follow1->setText("第一人讲述");
			Follow2 = new QRadioButton(this);
			Follow2->setText("第二人讲述");
			FollowWho = new QButtonGroup();
			FollowWho->addButton(Follow1);
			FollowWho->addButton(Follow2);

			Text_Word_Interval = new QLabel(this);
			Text_Word_Interval->setText("出字间隔");
			Text_Word_Interval->setAlignment(Qt::AlignCenter);

			Text_Word_Wait = new QLabel(this);
			Text_Word_Wait->setText("页面停留时长");
			Text_Word_Wait->setAlignment(Qt::AlignCenter);

			Edit_Word_Interval = new QLineEdit(this);
			Edit_Word_Wait = new QLineEdit(this);

			ClearButton = new QPushButton(this);
			ClearButton->setText("清除所有内容");
			FillButton = new QPushButton(this);
			FillButton->setText("用默认值充满空格");
			UpdateButton = new QPushButton(this);
			UpdateButton->setText("向文本区提交");

			CurrentLayout->addWidget(Text_1_Name, 0, 0, 1, 1);
			CurrentLayout->addWidget(Edit_1_Name, 0, 1, 1, 1);
			CurrentLayout->addWidget(Edit_1_Emotion, 0, 2, 1, 1);
			CurrentLayout->addWidget(Edit_1_Flip, 0, 3, 1, 1);
			CurrentLayout->addWidget(Edit_1_Filter, 0, 4, 1, 1);
			CurrentLayout->addWidget(Edit_1_Call, 0, 5, 1, 1);

			CurrentLayout->addWidget(Text_Emotion, 1, 2, 1, 1);
			CurrentLayout->addWidget(Text_Flip, 1, 3, 1, 1);
			CurrentLayout->addWidget(Text_Filter, 1, 4, 1, 1);
			CurrentLayout->addWidget(Text_Call, 1, 5, 1, 1);

			CurrentLayout->addWidget(Text_2_Name, 2, 0, 1, 1);
			CurrentLayout->addWidget(Edit_2_Name, 2, 1, 1, 1);
			CurrentLayout->addWidget(Edit_2_Emotion, 2, 2, 1, 1);
			CurrentLayout->addWidget(Edit_2_Flip, 2, 3, 1, 1);
			CurrentLayout->addWidget(Edit_2_Filter, 2, 4, 1, 1);
			CurrentLayout->addWidget(Edit_2_Call, 2, 5, 1, 1);

			CurrentLayout->addWidget(Follow1, 0, 7, 1, 1);
			CurrentLayout->addWidget(Follow2, 0, 8, 1, 1);
			CurrentLayout->addWidget(Edit_Said, 1, 7, 7, 7);
			CurrentLayout->addWidget(ClearButton, 0, 9, 1, 1);
			CurrentLayout->addWidget(FillButton, 0, 10, 1, 1);
			CurrentLayout->addWidget(UpdateButton, 0, 11, 1, 1);

			CurrentLayout->addWidget(Text_Word_Interval, 5, 1, 1, 1);
			CurrentLayout->addWidget(Text_Word_Wait, 5, 2, 1, 1);
			CurrentLayout->addWidget(Edit_Word_Interval, 4, 1, 1, 1);
			CurrentLayout->addWidget(Edit_Word_Wait, 4, 2, 1, 1);

		}

};

class SpeakSub :public QWidget
{
	Q_OBJECT
public:
	QRadioButton* EmptySub;
	QRadioButton* SingleSub;
	QRadioButton* DoubleSub;
	
	QGridLayout* CurrentLayout;
	QButtonGroup* CurrentGroup;
	SpeakSub(QWidget* parent = Q_NULLPTR) {
		this->setParent(parent);
		EmptySub = new QRadioButton(this);
		SingleSub = new QRadioButton(this);
		DoubleSub = new QRadioButton(this);
		
		EmptySub->setText("空场控制器");
		SingleSub->setText("单人讲述控制器");
		DoubleSub->setText("双人讲述控制器");
	
		CurrentLayout = new QGridLayout();
		this->setLayout(CurrentLayout);
		CurrentLayout->addWidget(EmptySub, 0, 0, 1, 1);
		CurrentLayout->addWidget(SingleSub, 1, 0, 1, 1);
		CurrentLayout->addWidget(DoubleSub, 2, 0, 1, 1);

		CurrentGroup = new QButtonGroup(this);
		CurrentGroup->addButton(EmptySub, 0);
		CurrentGroup->addButton(SingleSub, 1);
		CurrentGroup->addButton(DoubleSub, 2);
	}
};

class SubControllerDef :public QGroupBox
{
	Q_OBJECT
	public:
		QLabel* NoneSub;
		SoundSub* SoundArea;
		SpeakSub* SpeakArea;
		QGridLayout* CurrentLayout;
		SubControllerDef(QWidget *parent = Q_NULLPTR) {
			this->setParent(parent);
			this->setTitle("控制器子类型");
			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);

			SoundArea = new SoundSub(this);
			SoundArea->move(-SoundArea->geometry().width(), -SoundArea->geometry().height());
			SpeakArea = new SpeakSub(this);
			SpeakArea->move(-SpeakArea->geometry().width(), -SpeakArea->geometry().height());

			NoneSub = new QLabel(this);
			NoneSub->setText("无控制器子类型");
			NoneSub->setAlignment(Qt::AlignCenter);
			CurrentLayout->addWidget(NoneSub);

		}
	public slots:
		void hideCurrentArea(void) {
			QLayoutItem* child;
			while ( (child = CurrentLayout->itemAt(0)) != Q_NULLPTR) {
				CurrentLayout->removeItem(child);
			}
			SoundArea->move(-SoundArea->geometry().width(), -SoundArea->geometry().height());
			SpeakArea->move(-SpeakArea->geometry().width(), -SpeakArea->geometry().height());
			NoneSub->move(-NoneSub->geometry().width(), -NoneSub->geometry().height());
		}
		void showNoneSubArea(void) {
			hideCurrentArea();
			CurrentLayout->addWidget(NoneSub);
		}
		void showSoundSubArea(void) {
			hideCurrentArea();
			CurrentLayout->addWidget(SoundArea);
		}
		void showSpeakSubArea(void) {
			hideCurrentArea();
			CurrentLayout->addWidget(SpeakArea);
		}
};

class ControllerDetails :public QGroupBox
{
	Q_OBJECT
	public:
		SpeakMain* SpeakArea;
		QGridLayout* CurrentLayout;
		ControllerDetails(QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			this->setTitle("控制器详情");
			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);
			SpeakArea = new SpeakMain(this);
			CurrentLayout->addWidget(SpeakArea, 0, 0, 1, 1);

		}

};
class ControllerDefinition :public QGroupBox
{
	Q_OBJECT
	public:
		QGridLayout* CurrentLayout;
		SubControllerDef* SubArea;
		ControllerDetails* DetailsArea;
		ControllerDefinition(QWidget *parent=Q_NULLPTR) {
			this->setParent(parent);
			this->setTitle("控制器设定——在左边新建一个控制器，之后这里会显示详细设定");
			CurrentLayout = new QGridLayout();
			this->setLayout(CurrentLayout);
			SubArea = new SubControllerDef(this);
			CurrentLayout->addWidget(SubArea, 0, 1, 1, 1);
			DetailsArea = new ControllerDetails(this);
			CurrentLayout->addWidget(DetailsArea, 0, 2, 1, 5);

		}

};

class DebugInfo :public QGroupBox
{
	Q_OBJECT
	public:
		DebugInfo(QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			this->setTitle("预解释输出");
		}
};
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

	SPOLController* ControllerArea;
	ControllerDefinition* DefinitionArea;
	DebugInfo* DebugArea;

	SPOLDevWindow(QWidget* parent = Q_NULLPTR) {
		WhileInput = new QTimer(this);
		connect(WhileInput, SIGNAL(timeout()), this, SLOT(repaintWhileFree()));
		this->setGeometry(QRect(100, 100, 1024, 768));
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
		WindowLayout->addWidget(SPOLEdit, 2, 1, 8, 9);

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
		WindowLayout->addWidget(LineNumLabel, 2, 0, 8, 1);

		/*
		ControllerArea = new SPOLController(this);
		WindowLayout->addWidget(ControllerArea, 10, 0, 3, 2);

		DefinitionArea = new ControllerDefinition(this);
		WindowLayout->addWidget(DefinitionArea, 10, 2, 3, 8);

		//DebugArea = new DebugInfo(this);
		//WindowLayout->addWidget(DebugArea, 10, 8, 3, 2);

		connect(this->ControllerArea->Sound_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showSoundSubArea()));
		connect(this->ControllerArea->Speak_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showSpeakSubArea()));
		connect(this->ControllerArea->Title_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showNoneSubArea()));
		connect(this->ControllerArea->Edition_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showNoneSubArea()));
		connect(this->ControllerArea->Free_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showNoneSubArea()));
		connect(this->ControllerArea->Branch_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showNoneSubArea()));
		connect(this->ControllerArea->Jump_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showNoneSubArea()));
		connect(this->ControllerArea->Title_C, SIGNAL(clicked()), this->DefinitionArea->SubArea, SLOT(showNoneSubArea()));
		*/

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
		SPOLFileNameLabel->setText("/story/未命名文档.spol");
		SPOLFileNameLabel->setStyleSheet("QLineEdit{background-color:#2266CCFF;}");
		WindowLayout->addWidget(SPOLFileNameLabel, 1, 0, 1, 10);

		/*
		FaRButton = new QPushButton(this);
		FaRButton->setText("查找和替换");
		WindowLayout->addWidget(FaRButton, 0, 6, 1, 1);
		
		EnableLinkModeButton = new QPushButton(this);
		EnableLinkModeButton->setText("启用半可视化编辑");
		WindowLayout->addWidget(EnableLinkModeButton, 0, 7, 1, 1);
		
		PlayButton = new QPushButton(this);
		PlayButton->setText("播放（开发中）");
		WindowLayout->addWidget(PlayButton, 0, 8, 1, 1);
		*/

		connect(this->SaveButton, SIGNAL(clicked()), this, SLOT(saveSPOLFile()));
		connect(this->OpenButton, SIGNAL(clicked()), this, SLOT(openSPOLFile()));
		//connect(this->FaRButton, SIGNAL(clicked()), this, SLOT(testSelect()));
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
		SPOLEdit->setHtml(setColor("#YSP自带着色开发环境SPOLDev(Beta测试版)，版本0.1，兼容着色SPOL0.6+\n#使用SPOL创建您自己的剧情。\n\n/SPOL0.6.5-FollowNew\n"));
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
		SPOLFileNameLabel->setText("/story/未命名文档.spol");
		this->setWindowTitle("SPOL着色开发环境——现在正在编辑：/story/未命名文档.spol");
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