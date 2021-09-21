#pragma once
#include "core0_6_5_T.h"
#include "core0_6_5_B.h"
#include "../global_value.h"
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <algorithm>
#include <windows.h>
using namespace std;

int LineNum;
bool justJump;
bool exitNow;
float SpeedFloat;
QString UserChooseBranch;
QStringList MeaningfulLine;
QList<QStringList> BGPList;
QList<QStringList> BGMList;
int TransThreadCount;
QStringList TransPictureName;

void ReciveUserControl::LineNumNow(int Num) {
	LineNum = Num;
	justJump = TRUE;
}

void ReciveUserControl::SpeedNow(float Num) {
	SpeedFloat = Num;

}

void ReciveUserControl::ChooseWhichBranch(QString BranchName){
	UserChooseBranch = BranchName;
}

void ReciveUserControl::ExitNow(void) {
	exitNow = TRUE;
}


/*
cYSP解释器逻辑不同于Python版本。首先，cYSP将原来的预处理核心（P核心）、解释器核心（U核心）的代码合二为一
区分为顶层核心（T核心）的presource模式和run模式，并且把原来在U核心实时解释时产生的报错信息归为T核心的debug模式以减少控制台污染
其次，在presource阶段，解释器除了处理图像滤镜之外，还要从源文件中提取有义列，即预先剔除注释（但不剔除其他语法错误行），
以减少实时运行过程中遇到超长注释时产生的卡顿。
并且，为了保证按行跳转之后的视听效果正常，现在在按行跳转之后会先尝试从目标行向前回溯一个有效的BGM和背景，再继续进行目标行解释。
与此同时，在Python版中，大分支控制器的跳转交还UICoreLauncher进行处理，并在处理之后重新启动解释器函数。
但是现在统一用解释器函数的通用文档循环解决这个问题。确保了UICoreLauncher只是一个核心启动器，一切SPOL解释都由解释器本身完成。
对于多线程处理图像，由于C++运行速度甚于Python，因此不会占用太长时间，相应的，在cYSP中，我们减少了基础等待时间。
并且由于速度过快，线程计数值很有可能因为线程冲突而导致最后的计数不归零，这在Python版中几乎不存在，但在C++版本中常见。
为了避免由此卡死，我们给计数归零给予了5秒的等待上限。若5秒后仍不归零，则继续执行接下来的解释语句。
*/

//解释器函数
void Interpreter(QString storyFilename, InterpreterSignals *signalsName, mQThread *parent ) {
	QFile CurrentSPOLFile;
	SpeedFloat = 1.0;
	bool FirstEnter = TRUE;
	//通用文档循环
	while (TRUE) {
		//文件获取
		CurrentSPOLFile.setFileName(storyFilename);
		CurrentSPOLFile.open(QIODevice::ReadOnly | QIODevice::Text);
		if (!CurrentSPOLFile.isOpen()) { return; }
		QTextStream CurrentSPOLText(&CurrentSPOLFile);
		CurrentSPOLText.setCodec("UTF-8");
		//清理跳转列表
		emit signalsName->clr_line_list();
		//启动预加载
		qDebug().noquote() << "-->尝试启动预解释和资源补齐模块<--- ";
		bool InNotes = FALSE;
		TransThreadCount = 0;
		TransPictureName.clear();
		MeaningfulLine.clear();
		//预加载循环
		for (int i = 1;;i++) {
			QString CurrentLine = CurrentSPOLText.readLine();
			if (CurrentLine.mid(0, 3) == "###") {
				InNotes = !InNotes;
				continue;
			}
			if (InNotes == TRUE) { continue; }
			if (CurrentLine[0] != "#" && CurrentLine!="" && CurrentLine[0]!= ":" && CurrentLine[0]!="/") {
				SingleLine(i, CurrentLine, InterpreterMode::presource, signalsName, parent);
			}
			if (CurrentSPOLText.atEnd()) { break; }
		}
		qDebug().noquote() << "InterpreterInfo→成功预剔除注释行";
		//装载跳转列表
		emit signalsName->set_scroll_info();
		//制造标题阶段动画
		if (FirstEnter) { 
			Sleep(4000);
			emit signalsName->can_hide_title();
			Sleep(1000); 
		}
		//多线程等待区域
		for (int i = 0; i < 10; i++) {
			Sleep(500);
			if (TransThreadCount <= 0) { break; }
		}
		//追加长时控制器列表
		BGPList.append({ "51200","[黑场]" });
		BGMList.append({ "51200","{}" });
		
		//替换顶控件
		if (FirstEnter) { emit signalsName->can_prepare_play(); }

		//实时解释模块
		qDebug().noquote() << "-->尝试启动实时解释模块<--- ";
		LineNum = -1;
		justJump = FALSE;
		QStringList LineResult;
		QString Note = "UNKOWN_NOTE";
		bool InBranch=FALSE;
		bool FindBranch = FALSE;
		exitNow = FALSE;
		
		//主解释循环
		for (;;) {
			LineNum += 1;

			//确认本循环目标行号，以及是否仍处于运行状态
			if (LineNum == MeaningfulLine.length() || exitNow==TRUE) {
				LineResult[0] = "FILEEND";
				LineResult[1] = "FILEEND";
				break;
			}

			//对于刚刚完成跳转的情况回溯上一长时控制器
			if (justJump == TRUE) {
				InBranch = FALSE;
				qDebug() << LineNum;
				qDebug() << BGPList;
				for (int i = 0; i < BGPList.length() - 2; i++) {
					if (BGPList[i][0].toInt() <= LineNum && LineNum<= BGPList[i+1][0].toInt()) {
						SingleLine(BGPList[i][0].toInt() ,BGPList[i][1],InterpreterMode::run,signalsName, parent);
						break;
					}
				}
				for (int i = 0; i < BGMList.length() - 2; i++) {
					if (BGMList[i][0].toInt() >= LineNum) {
						SingleLine(BGMList[i][0].toInt() ,BGMList[i][1], InterpreterMode::run, signalsName, parent);
						break;
					}
				}	
				justJump = FALSE;
			}

			//从有义列中取出当前行
			QString CurrentLine = MeaningfulLine[LineNum];
			
			//预处理小分支控制器——检测小分支开始与结束
			if (CurrentLine.mid(0, 3) == "|||" ) {
				if (InBranch == FALSE) {
					QStringList SmallJumpSetList;
					SmallJumpSetList = CurrentLine.mid(3, CurrentLine.length() - 4).split("|||");
					if (SmallJumpSetList.length() > 4) { continue; }
					QList<QStringList> SmallJumpNoteList;
					for (int i = 0; i < SmallJumpSetList.length(); i++) {
						SmallJumpNoteList.append(SmallJumpSetList[i].split(":"));
					}

					InBranch = TRUE;
					emit signalsName->need_to_choose(SmallJumpSetList);
					emit signalsName->willstop();
					parent->pause();
					emit signalsName->inrunning();
					
					for (int i = 0; i < SmallJumpNoteList.length(); i++) {
						if (UserChooseBranch == SmallJumpNoteList[i][1]) {
							Note = SmallJumpNoteList[i][0];
						}
					}
					continue;
				}
				else {
					InBranch = FALSE;
					FindBranch = FALSE;
				}
			}

			//预处理小分支控制器——检测标签是否匹配
			if (CurrentLine.mid(0, 2) == "||" && CurrentLine.mid(0, 3) != "|||" && InBranch) {
				qDebug() << Note;
				if (CurrentLine.mid(2, CurrentLine.length() - 2) != Note) {
					FindBranch = FALSE;
					continue;
				}
				else {
					FindBranch = TRUE;
					continue;
				}
			}

			//预处理小分支控制器——匹配标签后识别标签区
			if (CurrentLine[0] == "|" && CurrentLine.mid(0, 2) != "||" && CurrentLine.mid(0, 3) != "|||" ) {
				if (FindBranch==FALSE) {continue;}
				else {
					CurrentLine = CurrentLine.mid(1, CurrentLine.length() - 1);
				}
				
			}

			//解释当前行
			LineResult = SingleLine(LineNum, CurrentLine, InterpreterMode::run, signalsName, parent);
			
			//对于大分支控制器的返回结果进行文档刷新
			if (LineResult[0] == "FILEJUMP") {
				CurrentSPOLFile.close();
				storyFilename = "./story/"+LineResult[1]+".spol";
				FirstEnter = FALSE;
				break;
			}
		}
		//退出循环
		if (LineResult[0] == "FILEEND") {
			break;
		}
	}
};

//通用滤镜处理线程
class cTransform :public QThread
{
public:
	QString gFilename;
	QString gAddname;
	QString gFilefamily;
	QList<Filter> gFilterList;
	int gFilterCount;
	cTransform(QString filename, QString filefamily, QList<Filter> filterList) {
		gFilename = filename;
		gFilterList = filterList;
		gFilefamily = filefamily;
		gFilterCount = gFilterList.length();
		gAddname = "";
		if (filterList.contains(Filter::gradientMask)) { gAddname += "_1"; }
		if (filterList.contains(Filter::blackSilhouette)) { gAddname += "_2"; }
		if (filterList.contains(Filter::fade)) { gAddname += "_3"; }
		if (filterList.contains(Filter::onlyBW)) { gAddname += "_4"; }
		if (filterList.contains(Filter::reverseColor)) { gAddname += "_5"; }
		if (filterList.contains(Filter::turnDark)) { gAddname += "_6"; }
	}
	void run(void) {
		QString SourceName = "./Visual/source/" + gFilefamily + "/" + gFilename + ".png";
		QString NewPictureName = "./Visual/cache/" + gFilefamily + "/" + gFilename + gAddname + ".png";
		if (!TransPictureName.contains(NewPictureName) && gAddname!="") {
			TransPictureName.append(NewPictureName);
			qDebug().noquote() << "InterpreterInfo→需要建立 :" + NewPictureName;
			QImage SourcePicture = QImage(SourceName);
			int X = SourcePicture.width();
			int Y = SourcePicture.height();
			QImage NewImage = QImage(X, Y, QImage::Format_ARGB32);
			for (int x = 0; x < X; x++) {
				for (int y = 0; y < Y; y++) {
					QColor oldcolor = QColor(SourcePicture.pixelColor(x, y));
					int r = oldcolor.red();
					int g = oldcolor.green();
					int b = oldcolor.blue();
					int a = oldcolor.alpha();
					for (int i = 0; i < gFilterList.length(); i++) {
						transformation(gFilterList[i], &r, &g, &b, &a, y, Y);
					}
					NewImage.setPixel(x, y, qRgba(r, g, b, a));
				}
			}
			NewImage.save(NewPictureName);
			qDebug().noquote() << "InterpreterInfo→成功建立 :" + NewPictureName;
		}
		TransThreadCount--;
		this->deleteLater();
	}
};

QList<cTransform*> TransThreadList;

QStringList SingleLine(int LineNum ,QString Line, InterpreterMode whichMode, InterpreterSignals* signalsName, mQThread* parent) {
	if (whichMode == InterpreterMode::presource) {
		MeaningfulLine.append(Line);
		if (Line[0] != "|" || Line.mid(0,3)=="|||") {
			emit signalsName->save_line_list({ QString::number(MeaningfulLine.length() - 1),Line });
		}
		if (Line[0] == "|") { Line = Line.mid(1, Line.length() - 1); }
	}
	if (whichMode == InterpreterMode::run) {
		emit signalsName->now_which_line(LineNum);
	}
	
	//背景控制器
	if (Line[0] == "[") {
		QStringList RAW = Line.mid(1, Line.length() - 2).split(",");
		QStringList BGSetList = RAW;
		for (int i = 0; i < 4 - RAW.length(); i++) { BGSetList.append(""); }
		if (BGSetList[0] == "") { BGSetList[0] = "黑场"; }
		if (BGSetList[1] == "") { BGSetList[1] = "0"; }
		if (BGSetList[2] == "") { BGSetList[2] = "0"; }
		if (BGSetList[3] == "") { BGSetList[3] = "0.5"; }	
		try {
			if (0 > BGSetList[1].toInt() || BGSetList[1].toInt() > 5) { throw "Exception"; }
			if (0 > BGSetList[2].toInt() || BGSetList[2].toInt() > 3) { throw "Exception"; }
			if (0 > BGSetList[3].toFloat()) { throw "Exception"; }
		}
		catch (...) {
			if (whichMode == InterpreterMode::debug) {
				qDebug().noquote() << "检查行" + QString::number(LineNum) + "中背景控制器存在的数值设定超限";
			}
		}

		if (whichMode == InterpreterMode::presource) {
			BGPList.append({ QString::number(MeaningfulLine.length() - 1),Line });
			QList<Filter> FilterList;
			if (BGSetList[1] == "1") { FilterList.append(Filter::turnDark); }
			if (BGSetList[1] == "2") { FilterList.append(Filter::fade); }
			if (BGSetList[1] == "3") { FilterList.append(Filter::fade); FilterList.append(Filter::turnDark); }
			if (BGSetList[1] == "4") { FilterList.append(Filter::onlyBW); }
			if (BGSetList[1] == "5") { FilterList.append(Filter::onlyBW); FilterList.append(Filter::turnDark); }
			TransThreadList.append(new cTransform(BGSetList[0], "BGP", FilterList));
			TransThreadList[TransThreadList.length() - 1]->start();
			TransThreadCount++;
		}

		if (whichMode == InterpreterMode::run) {

			emit signalsName->can_update_bg(BGSetList);
			if (BGSetList[3].toFloat() != 0) {
				emit signalsName->willstop();
				for (float OpFloat = 0; OpFloat < 1; OpFloat += (1 / (BGSetList[3].toFloat() * 60))) {
					emit signalsName->update_num_bg(OpFloat, BGSetList);		
					Sleep((float)15*SpeedFloat);
				}
				emit signalsName->update_num_bg(1, BGSetList);
				parent->pause();
				emit signalsName->inrunning();
			}
			else {
				emit signalsName->willstop();
				Sleep(1);
				emit signalsName->update_num_bg(0, BGSetList);
				emit signalsName->update_num_bg(1, BGSetList);
				parent->pause();
				emit signalsName->inrunning();
			}
		}
	}

	//音乐控制器、音效控制器
	else if (Line[0] == "{" || Line[0] == "<") {
		QStringList RAW = Line.mid(1, Line.length() - 2).split(",");
		QStringList MusicSetList = RAW;
		for (int i = 0; i < 2 - RAW.length(); i++) { MusicSetList.append(""); }
		if (MusicSetList[0] == "") { MusicSetList[0] = "静音"; }
		if (MusicSetList[1] == "") { MusicSetList[1] = "50"; }

		if (whichMode == InterpreterMode::debug) {
			if (RAW.length() > 2) { qDebug() << "检查行" + QString::number(LineNum) + "中存在的音频或音效控制器参数个数超限的问题"; }
		}

		if (whichMode == InterpreterMode::presource) {
			BGMList.append({ QString::number(MeaningfulLine.length() - 1),Line });
		}

		if (whichMode == InterpreterMode::run) {
			if (Line[0] == "{") {
				emit signalsName->can_update_bgm(MusicSetList[0], MusicSetList[1].toInt());
			}
			else if (Line[0] == "<") {
				emit signalsName->can_update_sound(MusicSetList[0], MusicSetList[1].toInt());
			}
		}
	}

	//讲述控制器
	else if (Line.mid(0, 3) == ">>>") {
		//首先提取行进驻留控制器（若有）
		QStringList PlaySetList;
		if (Line[Line.length() - 1] == ")") {
			QStringList cachePlaySetList = Line.mid(Line.lastIndexOf("(") + 1, Line.length() - Line.lastIndexOf("(") - 2).split(",");
			PlaySetList = cachePlaySetList;
			for (int j = 0; j < 2 - cachePlaySetList.length(); j++) { PlaySetList.append(""); }
			Line = Line.mid(0, Line.lastIndexOf("("));
		}else {
			PlaySetList.append("");
			PlaySetList.append("");
		}
		if (PlaySetList[0] == "") { PlaySetList[0] = "0.066"; }
		if (PlaySetList[1] == "") { PlaySetList[1] = "1.5"; }

		//提取讲述控制器全体
		QStringList RAW = Line.mid(3, Line.length() - 3).split(">>>");
		QList<QStringList> CharaSetList;
		for (int i = 0; i < RAW.length(); i++) {
			CharaSetList.append({ RAW[i].split(":") });
		}
		//从讲述控制器全体提取立绘设置
		QList<QStringList> AvgSetList;
		for (int i = 0; i < CharaSetList.length(); i++) {
			AvgSetList.append({ CharaSetList[i][0].split("/") });
			for (int j = 0; j < 7 - CharaSetList[i][0].split("/").length(); j++) { AvgSetList[i].append(""); }
			if (AvgSetList[i][0] == "") { AvgSetList[i][0] = ""; }
			if (AvgSetList[i][1] == "") { AvgSetList[i][1] = ""; }
			if (AvgSetList[i][2] == "") { AvgSetList[i][2] = "0"; }
			if (AvgSetList[i][3] == "") { AvgSetList[i][3] = "0"; }
			if (AvgSetList[i][4] == "") { AvgSetList[i][4] = "0.5"; }
			if (AvgSetList[i][5] == "") { AvgSetList[i][5] = "0.5"; }
			if (AvgSetList[i][6] == "") { AvgSetList[i][6] == "()"; }
		}
		//从讲述控制器全体提取文本设置
		QList<QStringList> WordSetList;
		for (int i = 0; i < CharaSetList.length(); i++) {
			if (CharaSetList[i].length() == 2) {
				WordSetList.append({ AvgSetList[i][0],CharaSetList[i][1] });
			}
			else if (CharaSetList[i].length() == 3) {
				WordSetList.append({ CharaSetList[i][1],CharaSetList[i][2] });
			}
		}
		

		int Charanum = WordSetList.length();
		bool BGBlack = TRUE;

		if (Charanum == 1) {
			if (WordSetList[0][1] == "") { AvgSetList[0].append("(亮，沉默)"); }
			else if (WordSetList[0][1] != "") { AvgSetList[0].append("(亮，讲述)"); }
		}
		else if (Charanum == 2) {
			if (WordSetList[0][1] == "" && WordSetList[1][1] == "") {
				AvgSetList[0].append("(亮，沉默)");
				AvgSetList[1].append("(亮，沉默)");
				if (WordSetList[0][0] == "" && WordSetList[1][0] == "") { BGBlack = FALSE; }
			}
			else if (WordSetList[0][1] != "" && WordSetList[1][1] == "") {
				AvgSetList[0].append("(亮，讲述)");
				AvgSetList[1].append("(暗，沉默)");
			}
			else if (WordSetList[0][1] == "" && WordSetList[1][1] != "") {
				AvgSetList[0].append("(亮，沉默)");
				AvgSetList[1].append("(亮，讲述)");
			}else {
				AvgSetList[0].append("(亮，讲述)");
				AvgSetList[1].append("(亮，讲述)");
			}
		}
		if (whichMode == InterpreterMode::debug) {
			if (Charanum > 2) {
				qDebug().noquote() << "检查行" + QString::number(LineNum) + "中存在的讲述控制器数量超限";
			}
		}
		if (whichMode == InterpreterMode::presource) {
			QList<Filter> FilterList;
			for (int i = 0; i < AvgSetList.length(); i++) {
				if (AvgSetList[i][3] == "1") { FilterList.append(Filter::gradientMask); }
				if (AvgSetList[i][3] == "2") { FilterList.append(Filter::fade); }
				if (AvgSetList[i][3] == "3") { FilterList.append(Filter::fade); FilterList.append(Filter::gradientMask); }
				if (AvgSetList[i][3] == "4") { FilterList.append(Filter::onlyBW); }
				if (AvgSetList[i][3] == "5") { FilterList.append(Filter::onlyBW); FilterList.append(Filter::gradientMask); }
				if (AvgSetList[i][6] == "(暗，沉默)") { FilterList.append(Filter::turnDark); }
				TransThreadList.append(new cTransform(AvgSetList[i][0]+"_" + AvgSetList[i][1], "Chara", FilterList));
				TransThreadList[TransThreadList.length() - 1]->start();
				TransThreadCount++;
			}
		}
		if (whichMode == InterpreterMode::run) {
			emit signalsName->can_update_chara(AvgSetList, Charanum, BGBlack);
			QString WordsAll = "";
			for (int i = 0; i < WordSetList.length(); i++) {
				if (WordSetList[i][1] == "" && Charanum == 1) {
					emit signalsName->update_chara_num(WordSetList[i], WordsAll, Charanum, PlaySetList);
					break;
				}
				else if ((WordSetList[i][0] == "" && Charanum == 1) || (WordSetList[i][0] != "" && WordSetList[i][1] != "")) {
					int AlphaCount = 0;
					if (WordSetList[i][1] == "") {
						emit signalsName->update_chara_num(WordSetList[i], WordsAll, Charanum, PlaySetList);
					}
					else if (WordSetList[i][1] != "") {
						if (PlaySetList[0].toFloat() != 0) {	
							for (int j = 0; j < WordSetList[i][1].length(); j++) {
								Sleep(1000 * PlaySetList[0].toFloat() * SpeedFloat);
								ushort chara = WordSetList[i][1][j].unicode();
								if (0x4E00 <= chara && chara <= 0x9FFF ||
									0x3040 <= chara && chara <= 0x309F ||
									0x30A0 <= chara && chara <= 0x30FF  ) {
									AlphaCount += 2;
								}else { AlphaCount += 1; }
								if (AlphaCount > 60) {
									WordsAll += "\n";
									AlphaCount = 1;
								}
								WordsAll += WordSetList[i][1][j];
								emit signalsName->update_chara_num(WordSetList[i], WordsAll, Charanum, PlaySetList);
							}
						}
						else if (PlaySetList[0].toFloat() == 0) {
							for (int j = 0; j < WordSetList[i][1].length(); j++) {
								ushort chara = WordSetList[i][1][j].unicode();
								if (0x4E00 <= chara && chara <= 0x9FFF ||
									0x3040 <= chara && chara <= 0x309F ||
									0x30A0 <= chara && chara <= 0x30FF) {
									AlphaCount += 2;
								}
								else { AlphaCount += 1; }
								if (AlphaCount > 60) {
									WordsAll += "\n";
									AlphaCount = 1;
								}
								WordsAll += WordSetList[i][1][j];							
							}
							emit signalsName->update_chara_num(WordSetList[i], WordsAll, Charanum, PlaySetList);
						}						
					}
					break;
				}			
			}
			emit signalsName->willstop();
			Sleep((float)1000 * PlaySetList[1].toFloat() * SpeedFloat);
			emit signalsName->show_next();
			parent->pause();
			emit signalsName->inrunning();
		}
	}

	//自由文本控制器
	else if (Line.mid(0, 3) == ">^>") {
	//首先提取行进驻留控制器（若有）
		QStringList PlaySetList;
		if (Line[Line.length() - 1] == ")") {
			QStringList cachePlaySetList = Line.mid(Line.lastIndexOf("(") + 1, Line.length() - Line.lastIndexOf("(") - 2).split(",");
			PlaySetList = cachePlaySetList;
			for (int j = 0; j < 2 - cachePlaySetList.length(); j++) { PlaySetList.append(""); }
			Line = Line.mid(0, Line.lastIndexOf("("));
		}
		else {
			PlaySetList.append("");
			PlaySetList.append("");
		}
		if (PlaySetList[0] == "") { PlaySetList[0] = "0.066"; }
		if (PlaySetList[1] == "") { PlaySetList[1] = "1.5"; }

		//提取自由文本控制器
		QStringList RAW = Line.mid(3, Line.length() - 3).split(":");
		QStringList FreeSetList = RAW;
		for (int i = 0; i < 2 - RAW.length(); i++) { FreeSetList.append(""); }
		QStringList FreePoList = FreeSetList[0].split("/");
		for (int i = 0; i < 3 - FreeSetList[0].split("/").length(); i++) { FreePoList.append(""); }
		if (FreePoList[0] == "") { FreePoList[0] = "0.125"; }
		if (FreePoList[1] == "") { FreePoList[1] = "0.444"; }
		if (FreePoList[2] == "") { FreePoList[2] = "M"; }

		if (whichMode == InterpreterMode::debug) {
			if (FreeSetList.length() > 2 || FreePoList.length() > 3) {
				qDebug() << "检查行" + QString::number(LineNum) + "存在的自由文本控制器参数个数超限";			}
		}

		if (whichMode == InterpreterMode::run) {
			emit signalsName->can_update_freedom(FreePoList, PlaySetList);
			int AlphaCount = 0;
			QString WordsAll = "";
			if (PlaySetList[0].toFloat() != 0) {
				for (int j = 0; j < FreeSetList[1].length(); j++) {
					Sleep(1000 * PlaySetList[0].toFloat() * SpeedFloat);
					ushort chara = FreeSetList[1][j].unicode();
					if (0x4E00 <= chara && chara <= 0x9FFF ||
						0x3040 <= chara && chara <= 0x309F ||
						0x30A0 <= chara && chara <= 0x30FF) {
						AlphaCount += 2;
					}
					else { AlphaCount += 1; }
					if (AlphaCount > 60) {
						WordsAll += "\n";
						AlphaCount = 1;
					}
					WordsAll += FreeSetList[1][j];
					emit signalsName->update_num_freedom(WordsAll);
				}
			}
			else if (PlaySetList[0].toFloat() == 0) {
				for (int j = 0; j < FreeSetList[1].length(); j++) {
					ushort chara = FreeSetList[1][j].unicode();
					if (0x4E00 <= chara && chara <= 0x9FFF ||
						0x3040 <= chara && chara <= 0x309F ||
						0x30A0 <= chara && chara <= 0x30FF) {
						AlphaCount += 2;
					}
					else { AlphaCount += 1; }
					if (AlphaCount > 60) {
						WordsAll += "\n";
						AlphaCount = 1;
					}
					WordsAll += FreeSetList[1][j];
				}
				emit signalsName->update_num_freedom(WordsAll);
			}
			emit signalsName->willstop();
			Sleep((float)1000 * PlaySetList[1].toFloat() * SpeedFloat);
			emit signalsName->show_next();
			parent->pause();
			emit signalsName->inrunning();
			emit signalsName->can_clear_freedom(1);
		}
	}
	
	//大分支控制器
	else if (Line.mid(0, 3) == "-->") {
		QStringList RAW = Line.mid(3, Line.length() - 3).split("-->");
		QList<QStringList> JumpSetList;
		QStringList JumpTextList;
		for (int i = 0; i < RAW.length(); i++) {
			JumpSetList.append({ RAW[i].split(":")});
			for (int j = 0; j < 3 - RAW[i].split(":").length(); j++) { JumpSetList[i].append(""); }
			JumpTextList.append(JumpSetList[i][1]);
		}

		if (whichMode == InterpreterMode::run) {
			emit signalsName->need_to_choose(JumpTextList);
			emit signalsName->willstop();
			parent->pause();
			emit signalsName->inrunning();

			for (int i = 0; i < JumpSetList.length(); i++) {
				if (UserChooseBranch == JumpSetList[i][1]) {
					return { "FILEJUMP",JumpSetList[i][2] };
				}
			}
		}
	}

	//非法文本兜底
	else {
		if (whichMode == InterpreterMode::debug) {
			qDebug() << "检查行" + QString::number(LineNum) + "中的非法文本";
		}
	}
	return { "NORMAL","NORMAL" };
};

