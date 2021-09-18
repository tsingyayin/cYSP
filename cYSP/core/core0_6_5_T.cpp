#pragma once
#include "core0_6_5_T.h"
#include "core0_6_5_B.h"
#include "../global_value.h"
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <algorithm>

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

void Interpreter(QString storyFilename, InterpreterSignals *signalsName, mQThread *parent ) {
	QFile CurrentSPOLFile;
	SpeedFloat = 1.0;
	while (TRUE) {
		CurrentSPOLFile.setFileName(storyFilename);
		CurrentSPOLFile.open(QIODevice::ReadOnly | QIODevice::Text);
		QTextStream CurrentSPOLText(&CurrentSPOLFile);
		CurrentSPOLText.setCodec("UTF-8");

		emit signalsName->clr_line_list();

		qDebug().noquote() << "-->尝试启动预解释和资源补齐模块<--- ";
		bool InNotes = FALSE;
		TransThreadCount = 0;
		TransPictureName.clear();
		MeaningfulLine.clear();
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

		Sleep(5000);
		emit signalsName->can_hide_title();
		Sleep(1000);
		while (TransThreadCount!=0) {
			Sleep(500);
		}
		qDebug().noquote() << "InterpreterInfo→成功预剔除注释行";

		emit signalsName->set_scroll_info();
		emit signalsName->can_prepare_play();

		LineNum = -1;
		justJump = FALSE;
		QStringList LineResult;
		qDebug().noquote() << "-->尝试启动实时解释模块<--- ";
		bool InBranch=FALSE;
		bool FindBranch = FALSE;
		exitNow = FALSE;
		for (;;) {
			LineNum += 1;
			if (LineNum == MeaningfulLine.length() || exitNow==TRUE) {
				LineResult[0] = "FILEEND";
				LineResult[1] = "FILEEND";
				break;
			}
			if (justJump == TRUE) {
				InBranch = FALSE;
				for (int i = 1; i < BGPList.length();  i++) {
					if (BGPList[BGPList.length() - i][0] < LineNum) {
						SingleLine(BGPList[BGPList.length() - i][0].toInt() ,BGPList[BGPList.length()-i][1],InterpreterMode::run,signalsName, parent);
						break;
					}
				}
				for (int i = 1; i < BGMList.length(); i++) {
					if (BGMList[BGMList.length() - i][0] < LineNum) {
						SingleLine(BGMList[BGMList.length() - i][0].toInt() ,BGMList[BGMList.length() - i][1], InterpreterMode::run, signalsName, parent);
						break;
					}
				}
				justJump = FALSE;
			}
			QString CurrentLine = MeaningfulLine[LineNum];
			if (CurrentLine.mid(0, 3) == "|||" ) {
				if (InBranch == FALSE) {
					QStringList SmallJumpSetList;
					SmallJumpSetList = CurrentLine.mid(3, CurrentLine.length() - 4).split("|||");
					if (SmallJumpSetList.length() > 4) { continue; }
					QList<QStringList> SmallJumpNoteList;
					for (int i = 0; i < SmallJumpSetList.length(); i++) {
						SmallJumpNoteList.append(SmallJumpSetList[i].split(":"));
					}
					qDebug() << SmallJumpSetList;
					InBranch = TRUE;
					emit signalsName->need_to_choose(SmallJumpSetList);
					emit signalsName->willstop();
					parent->pause();
					emit signalsName->inrunning();
					continue;
				}
				else {
					InBranch = FALSE;
					FindBranch = FALSE;
				}
			}
			if (CurrentLine.mid(0, 2) == "||" && CurrentLine.mid(0, 3) != "|||" && InBranch) {
				if (CurrentLine.mid(2, CurrentLine.length() - 3) != UserChooseBranch) {
					FindBranch = FALSE;
					continue;
				}
				else {
					FindBranch = TRUE;
					continue;
				}
			}
			if (CurrentLine[0] == "|" && CurrentLine.mid(0, 2) != "||" && CurrentLine.mid(0, 3) != "|||" ) {
				if (FindBranch==FALSE) {continue;}
				else {
					CurrentLine = CurrentLine.mid(1, CurrentLine.length() - 1);
				}
				
			}
			LineResult = SingleLine(LineNum, CurrentLine, InterpreterMode::run, signalsName, parent);
			
			if (LineResult[0] == "FILEJUMP") {
				CurrentSPOLFile.close();
				storyFilename = "./story/"+LineResult[1];
				break;
			}
		}
		if (LineResult[0] == "FILEEND") {
			break;
		}
	}
};


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
		if (!TransPictureName.contains(NewPictureName)) {
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
		emit signalsName->now_which_line(Line);
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
				qDebug().noquote() << "检查行" + QString::number(LineNum) + "中存在的数值设定超限";
			}
		}

		if (whichMode == InterpreterMode::presource) {
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
			qDebug() << BGSetList;

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
		qDebug() << PlaySetList;

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
			for (int j = 0; j < 6 - CharaSetList[i][0].split("/").length(); j++) { AvgSetList[i].append(""); }
			if (AvgSetList[i][0] == "") { AvgSetList[i][0] = ""; }
			if (AvgSetList[i][1] == "") { AvgSetList[i][1] = ""; }
			if (AvgSetList[i][2] == "") { AvgSetList[i][2] = "0"; }
			if (AvgSetList[i][3] == "") { AvgSetList[i][3] = "0"; }
			if (AvgSetList[i][4] == "") { AvgSetList[i][4] = "0.5"; }
			if (AvgSetList[i][5] == "") { AvgSetList[i][5] = "0.5"; }
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
			}
		}

		if (whichMode == InterpreterMode::debug) {
			if (Charanum > 2) {
				qDebug().noquote() << "检查行" + QString::number(LineNum) + "中存在的控制器数量超限";
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
								Sleep((float)1000 * PlaySetList[0].toFloat());
								if ("\u4e00" <= WordSetList[i][1][j] && WordSetList[i][1][j] <= "\u9fff" ||
									"\u3040" <= WordSetList[i][1][j] && WordSetList[i][1][j] <= "\u309f" ||
									"\u30a0" <= WordSetList[i][1][j] && WordSetList[i][1][j] <= "\u30ff"  ) {
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
						else if (PlaySetList[0].toFloat() != 0) {
							for (int j = 0; j < WordSetList[i][1].length(); j++) {
								if ("\u4e00" <= WordSetList[i][1][j] && WordSetList[i][1][j] <= "\u9fff" ||
									"\u3040" <= WordSetList[i][1][j] && WordSetList[i][1][j] <= "\u309f" ||
									"\u30a0" <= WordSetList[i][1][j] && WordSetList[i][1][j] <= "\u30ff") {
									AlphaCount += 2;
								}
								else { AlphaCount += 1; }
								if (AlphaCount > 60) {
									WordsAll += "\n";
									AlphaCount = 1;
								}
								WordsAll += WordSetList[i][1][j];
								emit signalsName->update_chara_num(WordSetList[i], WordsAll, Charanum, PlaySetList);
							}
						}
						
					}
					break;
				}			
			}
			emit signalsName->willstop();
			Sleep((float)1000 * PlaySetList[1].toFloat());
			emit signalsName->show_next();
			parent->pause();
			emit signalsName->inrunning();
		}
	}
	return { "TEST","TEST" };
};

