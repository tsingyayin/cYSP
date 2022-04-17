#pragma once
#include "core_T.h"
#include "core_B.h"
#include "../global_value.h"
#include "../Aaspcommand/aaspcommand.h"
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <algorithm>
#include <QTest>
using namespace std;

int LineNum;
bool justJump;
bool exitNow;
float SpeedFloat;
QString UserChooseBranch;
QStringList MeaningfulLine;
QList<QStringList> BGPList;
QList<QStringList> BGMList;
QList<QStringList> CVRList;
QList<QStringList> ExtendList;
QList<QStringList> MoveList;
QString ExtendRawLine;
bool InExtend = FALSE;
int TransThreadCount;
QStringList TransPictureName;
QMutex TransformMutex;

void ReciveUserControl::LineNumNow(int Num) {
	LineNum = Num;
	justJump = TRUE;
}
void ReciveUserControl::SpeedNow(float Num) {
	SpeedFloat = Num;
}
void ReciveUserControl::ChooseWhichBranch(QString BranchName) {
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
并且由于速度过快，线程计数值很有可能因为线程冲突（并发）而导致最后的计数不归零，这在Python版中几乎不存在，但在C++版本中常见。
为了避免由此卡死，我们给计数归零给予了5秒的等待上限。若5秒后仍不归零，则继续执行接下来的解释语句。
经过测算，5秒的等待时间约等于大部分现有计算机在1080P播放时预先处理50余图像所需要的平均速度。
*/

//解释器函数
void Interpreter(QString storyFilename, InterpreterSignals* signalsName, mQThread* parent) {
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
		//qDebug().noquote() << "-->尝试启动预解释和资源补齐模块<--- ";
		emit signalsName->send_kernal_info("-->尝试启动预解释和资源补齐模块<---");
		bool InNotes = FALSE;
		InExtend = FALSE;
		TransThreadCount = 0;
		TransPictureName.clear();
		MeaningfulLine.clear();
		BGPList.clear();
		BGMList.clear();
		CVRList.clear();
		ExtendList.clear();
		MoveList.clear();
		//预加载循环
		for (int i = 1;; i++) {
			QString CurrentLine = CurrentSPOLText.readLine();
			if (CurrentLine.mid(0, 3) == "###") {
				InNotes = !InNotes;
				continue;
			}
			if (InNotes == TRUE) { continue; }
			if (CurrentLine[0] != "#" && CurrentLine != "" && CurrentLine.mid(0, 5) != "title" && CurrentLine[0] != "/") {
				SingleLine(i, CurrentLine, InterpreterMode::presource, signalsName, parent);
			}
			if (CurrentSPOLText.atEnd()) { break; }
		}
		if (MeaningfulLine.isEmpty()) { MeaningfulLine.append(">>>:"); }

		//装载跳转列表
		emit signalsName->set_scroll_info();

		//多线程等待区域
		for (int i = 0; i <= 10; i++) {
			if (TransThreadCount <= 0) { break; }
			QTest::qSleep(100);
		}
		//追加长时控制器列表
		BGPList.append({ "51200","BGP(黑场)" });
		BGMList.append({ "51200","BGM()" });
		CVRList.append({ "51200","CVR()" });
		ExtendList.append({ "51200",">>>:===" });
		MoveList.append({ "51200","moveBack(L)","moveBack(M)","moveBack(R)" });
		//qDebug().noquote() << "InterpreterInfo→成功预剔除注释行";
		emit signalsName->send_kernal_info("InterpreterInfo→成功预剔除注释行");

		//实时解释模块
		//qDebug().noquote() << "-->尝试启动实时解释模块<--- ";
		emit signalsName->send_kernal_info("-->尝试启动实时解释模块<---");
		QTest::qSleep(2000);
		LineNum = -1;
		justJump = FALSE;
		QStringList LineResult;
		QString Note = "UNKOWN_NOTE";
		bool InBranch = FALSE;
		bool FindBranch = FALSE;
		exitNow = FALSE;

		emit signalsName->can_show_title();
		QTest::qSleep(4000);
		emit signalsName->can_hide_title();
		QTest::qSleep(900);
		//替换顶控件
		if (FirstEnter) { emit signalsName->can_prepare_play(); }

		//主解释循环
		for (;;) {
			LineNum += 1;

			//确认本循环目标行号，以及是否仍处于运行状态。若不成立则退出主解释循环
			if (LineNum == MeaningfulLine.length() || exitNow == TRUE) {
				LineResult[0] = "FILEEND";
				LineResult[1] = "FILEEND";
				break;
			}
			LineResult.clear();
			LineResult.append("");
			LineResult.append("");
			//对于刚刚完成跳转的情况回溯上一长时控制器
			if (justJump == TRUE) {
				InBranch = FALSE;
				for (int i = BGPList.length() - 1; i >= 0; i--) {
					if (BGPList[i][0].toInt() <= LineNum) {
						SingleLine(BGPList[i][0].toInt(), BGPList[i][1], InterpreterMode::run, signalsName, parent);
						break;
					}
				}
				for (int i = BGMList.length() - 1; i >= 0; i--) {
					if (BGMList[i][0].toInt() <= LineNum) {
						SingleLine(BGMList[i][0].toInt(), BGMList[i][1], InterpreterMode::run, signalsName, parent);
						break;
					}
				}
				for (int i = CVRList.length() - 1; i >= 0; i--) {
					if (CVRList[i][0].toInt() <= LineNum) {
						SingleLine(CVRList[i][0].toInt(), CVRList[i][1], InterpreterMode::run, signalsName, parent);
						break;
					}
				}
				for (int i = ExtendList.length() - 1; i >= 0; i--) {
					if (ExtendList[i][0].toInt() <= LineNum) {
						ExtendRawLine = ExtendList[i][1];
						InExtend = TRUE;
						break;
					}
				}
				for (int i = MoveList.length() - 1; i >= 0; i--) {
					//qDebug() << MoveList[i][0].toInt();
					if (MoveList[i][0].toInt() < LineNum) {
						SingleLine(MoveList[i][0].toInt(), "moveBack()", InterpreterMode::run, signalsName, parent);
						//qDebug() << "RE:" << MoveList[i];
						for (int j = 1; j < MoveList[i].length(); j++) {
							SingleLine(MoveList[i][0].toInt(), MoveList[i][j], InterpreterMode::run, signalsName, parent);
							//qDebug() << MoveList[i][j];
						}
						break;
					}
				}
				justJump = FALSE;
			}

			//从有义列中取出当前行
			QString CurrentLine = MeaningfulLine[LineNum];

			
			//预处理小分支控制器——检测小分支开始与结束
			if (CurrentLine.mid(0, 3) == "|||") {
				InExtend = FALSE;
				if (InBranch == FALSE) {
					QStringList SmallJumpSetList;
					SmallJumpSetList = CurrentLine.mid(3, CurrentLine.length() - 3).split("|||");
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
					qDebug() << "run";
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
					continue;
				}
			}

			//小分支控制器自动结束——检测“|”是否还是一行的第一个字符。
			if (InBranch && CurrentLine[0] != "|") {
				InBranch = FALSE;
				FindBranch = FALSE;
			}

			//预处理小分支控制器——检测标签是否匹配
			if (CurrentLine.mid(0, 2) == "||" && CurrentLine.mid(0, 3) != "|||" && InBranch) {
				InExtend = FALSE;
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
			if (CurrentLine[0] == "|" && CurrentLine.mid(0, 2) != "||" && CurrentLine.mid(0, 3) != "|||") {
				if (FindBranch == FALSE) { continue; }
				else {
					CurrentLine = CurrentLine.mid(1, CurrentLine.length() - 1);
				}
			}

			
			//解释当前行
			if (CurrentLine != "/" && CurrentLine.mid(0, 5) != "title") {
				LineResult = SingleLine(LineNum, CurrentLine, InterpreterMode::run, signalsName, parent);
				if (LineResult[0] == "NOTFOUND" && LineResult[1] == "NOTFOUND" && InExtend) {
					QString ReplaceString = ExtendRawLine;
					ReplaceString.replace("===", CurrentLine);
					LineResult = SingleLine(LineNum, ReplaceString, InterpreterMode::rerun, signalsName, parent);
				}
				else if (LineResult[0] == "NOTFOUND" && LineResult[1] == "NOTFOUND" && !InExtend) {
					if (!InExtend) {
						int count = 0;
						QFile tryFile;
						tryFile.setFileName(PROPATH::Users + "/source/BGP/" + CurrentLine + ".png");
						if (tryFile.exists() || CurrentLine == "黑场") {
							count++;
							LineResult = SingleLine(LineNum, "BGP(" + CurrentLine + ")", InterpreterMode::run, signalsName, parent);
						}
						tryFile.setFileName(PROPATH::Users + "/source/Sound/" + CurrentLine + ".mp4");
						if (tryFile.exists()) {
							count++;
							LineResult = SingleLine(LineNum, "SND(" + CurrentLine + ")", InterpreterMode::run, signalsName, parent);
						}
						tryFile.setFileName(PROPATH::Users + "/source/BGM/" + CurrentLine + ".mp4");
						if (tryFile.exists()) {
							count++;
							LineResult = SingleLine(LineNum, "BGM(" + CurrentLine + ")", InterpreterMode::run, signalsName, parent);
						}
						if (count != 0) {
							continue;
						}
					}
				}
				if (LineResult[0] == "NOTFOUND") {
					signalsName->send_EIFL_info("SPOL语法异常！", "不能识别行 " + QString::number(LineNum) + " 中的内容", CurrentLine, EIFL::SSE);
				}
			}
			//对于大分支控制器的返回结果进行文档刷新
			if (LineResult[0] == "FILEJUMP") {
				CurrentSPOLFile.close();
				storyFilename = "./Users_Data/story/" + LineResult[1] + ".spol";
				FirstEnter = FALSE;
				break;
			}
		}
		//退出文档循环
		if (LineResult[0] == "FILEEND") {
			break;
		}
	}
};

void GPOLInterpreter(QStringList GPOLText, InterpreterSignals* signalsName, mQThread* parent) {
}



//通用滤镜处理线程
class cTransform :public QThread
{
public:
	QString gFilename;
	QString gAddname;
	QString gFilefamily;
	QList<Filter> gFilterList;
	int gFilterCount;
	InterpreterSignals* gSignalsName;
	cTransform(QString filename, QString filefamily, QList<Filter> filterList, InterpreterSignals* signalsName) {
		gFilename = filename;
		gFilterList = filterList;
		gFilefamily = filefamily;
		gFilterCount = gFilterList.length();
		gSignalsName = signalsName;
		gAddname = "";
		for (int i = 0; i < filterList.length(); i++) {
			switch (filterList[i]) {
			case gradientMask:
				gAddname += "_1";
				break;
			case blackSilhouette:
				gAddname += "_2";
				break;
			case fade:
				gAddname += "_3";
				break;
			case onlyBW:
				gAddname += "_4";
				break;
			case reverseColor:
				gAddname += "_5";
				break;
			case turnDark:
				gAddname += "_6";
				break;
			case gaussianBlur5:
				gAddname += "_7";
				break;
			case gaussianBlur11:
				gAddname += "_8";
				break;
			default:
				break;
			}
		}
	}

	void run(void) {
		QString SourceName = PROPATH::Users + "/source/" + gFilefamily + "/" + gFilename + ".png";
		QString NewPictureName = PROPATH::Users + "/cache/" + gFilefamily + "/" + gFilename + gAddname + ".png";
		if (!TransPictureName.contains(NewPictureName) && gAddname != "") {
			TransPictureName.append(NewPictureName);
			//qDebug().noquote() << "InterpreterInfo→需要建立 :" + NewPictureName;
			gSignalsName->send_kernal_info("InterpreterInfo→需要建立 :" + NewPictureName);
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
					QList<QList<int>> colorMatrix;
					if (gFilterList.contains(Filter::gaussianBlur5)) {
						for (int i = -2; i < 3; i++) {
							for (int j = -2; j < 3; j++) {
								if (x + j >= 0 && x + j < X && y + i >= 0 && y + i < Y) {
									colorMatrix.append({ SourcePicture.pixelColor(x + j,y + i).red(),SourcePicture.pixelColor(x + j,y + i).green(),SourcePicture.pixelColor(x + j,y + i).blue() });
								}
								else {
									colorMatrix.append({ 0,0,0 });
								}
							}
						}
					}
					if (gFilterList.contains(Filter::gaussianBlur11)) {
						for (int i = -5; i < 6; i++) {
							for (int j = -5; j < 6; j++) {
								if (x + j >= 0 && x + j < X && y + i >= 0 && y + i < Y) {
									colorMatrix.append({ SourcePicture.pixelColor(x + j,y + i).red(),SourcePicture.pixelColor(x + j,y + i).green(),SourcePicture.pixelColor(x + j,y + i).blue() });
								}
								else {
									colorMatrix.append({ 0,0,0 });
								}
							}
						}
					}
					for (int i = 0; i < gFilterList.length(); i++) {
						transformation(gFilterList[i], &r, &g, &b, &a, y, Y, colorMatrix);
					}
					NewImage.setPixel(x, y, qRgba(r, g, b, a));
				}
			}
			NewImage.save(NewPictureName);
			//qDebug().noquote() << "InterpreterInfo→成功建立 :" + NewPictureName;

			gSignalsName->send_kernal_info("InterpreterInfo→成功建立 :" + NewPictureName);

		}
		TransThreadCount--;
		this->deleteLater();
	}
};

QList<cTransform*> TransThreadList;

QStringList SingleLine(int LineNum, QString Line, InterpreterMode whichMode, InterpreterSignals* signalsName, mQThread* parent) {
	if (whichMode == InterpreterMode::presource) {
		MeaningfulLine.append(Line);
		if (Line[0] != "|" || Line.mid(0, 3) == "|||" && Line != "|||") {
			emit signalsName->save_line_list({ QString::number(MeaningfulLine.length() - 1),Line });
		}
		if (Line[0] == "|") { Line = Line.mid(1, Line.length() - 1); }
	}
	if (whichMode == InterpreterMode::run || whichMode == InterpreterMode::rerun) {
		emit signalsName->now_which_line(LineNum);
	}

	//背景控制器
	if (Line.mid(0, 3) == "BGP" || Line.mid(0, 8) == "backdrop") {
		QStringList RAW = Line.mid(Line.indexOf("(") + 1, Line.lastIndexOf(")") - Line.indexOf("(") - 1).split(",");
		/*QStringList BGSetList = RAW;
		for (int i = 0; i < 4 - RAW.length(); i++) { BGSetList.append(""); }
		if (BGSetList[0] == "") { BGSetList[0] = "黑场"; }
		if (BGSetList[1] == "") { BGSetList[1] = "0"; }
		if (BGSetList[2] == "") { BGSetList[2] = "0"; }
		if (BGSetList[3] == "") { BGSetList[3] = "0.5"; }
		try {
			if (0 > BGSetList[2].toInt() || BGSetList[2].toInt() > 3) { throw "Exception"; }
			if (0 > BGSetList[3].toFloat()) { throw "Exception"; }
		}
		catch (...) {
			if (whichMode == InterpreterMode::debug) {
				qDebug().noquote() << "检查行" + QString::number(LineNum) + "中背景控制器存在的数值设定超限";
			}
		}*/

		int RAWLength = RAW.length();
		for (int i = 0; i < 4 - RAWLength; i++) { RAW.append(""); }
		Controller::Backdrop::Data SetList;
		SetList.Backdrop = (RAW[0] == "" ? "黑场" : RAW[0]);
		SetList.Filter = (RAW[1] == "" ? "0" : RAW[1]);
		SetList.Effect = (RAW[2] == "" ? "0" : RAW[2]).toInt();
		SetList.Time = (RAW[3] == "" ? "0.5" : RAW[3]).toFloat();

		if (whichMode == InterpreterMode::presource) {
			BGPList.append({ QString::number(MeaningfulLine.length() - 1),Line });
			QList<Filter> FilterList;
			QStringList FilterRaw = SetList.Filter.split("_");
			for (int i = 0; i < FilterRaw.length(); i++) {
				switch (FilterRaw[i].toInt()) {
				case 1:
					FilterList.append(Filter::gradientMask);
					break;
				case 2:
					FilterList.append(Filter::blackSilhouette);
					break;
				case 3:
					FilterList.append(Filter::fade);
					break;
				case 4:
					FilterList.append(Filter::onlyBW);
					break;
				case 5:
					FilterList.append(Filter::reverseColor);
					break;
				case 6:
					FilterList.append(Filter::turnDark);
					break;
				case 7:
					FilterList.append(Filter::gaussianBlur5);
					break;
				case 8:
					FilterList.append(Filter::gaussianBlur11);
					break;
				default:
					FilterList.append(Filter::unknownFilter);
					break;
				}
			}
			TransThreadList.append(new cTransform(SetList.Backdrop, "BGP", FilterList, signalsName));
			TransThreadList[TransThreadList.length() - 1]->start();
			TransThreadCount++;
		}

		if (whichMode == InterpreterMode::run) {
			emit signalsName->can_update_bg(SetList);
			if (SetList.Time != 0) {
				emit signalsName->willstop();
				for (float OpFloat = 0; OpFloat < 1; OpFloat += (1 / (SetList.Time * 60))) {
					emit signalsName->update_num_bg(OpFloat, SetList);
					QTest::qSleep((float)15 * SpeedFloat);
				}
				emit signalsName->update_num_bg(1, SetList);
				parent->pause();
				emit signalsName->inrunning();
			}
			else {
				emit signalsName->willstop();
				QTest::qSleep(1);
				emit signalsName->update_num_bg(0, SetList);
				emit signalsName->update_num_bg(1, SetList);
				parent->pause();
				emit signalsName->inrunning();
			}
		}
	}

	//音乐控制器、音效控制器
	else if (Line.mid(0, 3) == "BGM" || Line.mid(0, 5) == "music" || Line.mid(0, 3) == "SND" || Line.mid(0, 5) == "sound") {
		InExtend = FALSE;
		QStringList RAW = Line.mid(Line.indexOf("(") + 1, Line.lastIndexOf(")") - Line.indexOf("(") - 1).split(",");
		int RAWLength = RAW.length();
		for (int i = 0; i < RAWLength; i++) { RAW.append(""); }
		Controller::music::Data SetList;
		SetList.music = (RAW[0] == "" ? "静音" : RAW[0]);
		SetList.volume = (RAW[1] == "" ? 50 : RAW[1].toFloat());
		if (whichMode == InterpreterMode::presource) {
			if (Line.mid(0, 3) == "BGM" || Line.mid(0, 5) == "music") {
				BGMList.append({ QString::number(MeaningfulLine.length() - 1),Line });
			}
		}

		if (whichMode == InterpreterMode::run) {
			if (Line.mid(0, 3) == "BGM" || Line.mid(0, 5) == "music") {
				emit signalsName->can_update_bgm(SetList.music, SetList.volume);
			}
			else if (Line.mid(0, 3) == "SND" || Line.mid(0, 5) == "sound") {
				emit signalsName->can_update_sound(SetList.music, SetList.volume);
			}
		}
	}

	//遮罩开闭控制器
	else if (Line.mid(0, 3) == "CVR" || Line.mid(0, 5) == "cover") {
		InExtend = FALSE;
		QString UserSet;
		bool Cover = TRUE;
		if (Line.mid(0, 3) == "CVR") {
			UserSet = Line.mid(4, Line.length() - 5);
		}
		else {
			UserSet = Line.mid(6, Line.length() - 7);
		}
		qDebug() << UserSet;
		if (UserSet == "true" || UserSet == "on") { Cover = TRUE; }
		else if (UserSet == "false" || UserSet == "off") { Cover = FALSE; }
		if (whichMode == InterpreterMode::presource) {
			CVRList.append({ QString::number(MeaningfulLine.length() - 1),Line });
		}
		if (whichMode == InterpreterMode::run) {
			emit signalsName->set_cover_status(Cover);
		}
	}

	//讲述控制器
	else if (Line.mid(0, 3) == ">>>") {
		if (!Line.contains(":")) {
			return { "NOTFOUND","NOTFOUND" };
		}
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
		if (PlaySetList[0] == "") { PlaySetList[0] = "0.04"; }
		if (PlaySetList[1] == "") { PlaySetList[1] = "1.75"; }

		//提取讲述控制器全体
		QStringList RAW = Line.mid(3, Line.length() - 3).split(">>>");
		QList<QStringList> CharaSetList;
		for (int i = 0; i < RAW.length(); i++) {
			if (RAW[i].contains(":")) {
				CharaSetList.append({ RAW[i].split(":") });
			}
			else {
				return { "NOTFOUND","NOTFOUND" };
			}
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
			if (AvgSetList[i][4] == "") { AvgSetList[i][4] = "0"; }
			if (AvgSetList[i][5] == "") { AvgSetList[i][5] = "0"; }
			if (AvgSetList[i][6] == "") { AvgSetList[i][6] == "()"; }
		}
		//从讲述控制器全体提取文本设置
		QList<QStringList> WordSetList;
		for (int i = 0; i < CharaSetList.length(); i++) {
			if (CharaSetList[i].length() == 2) {
				WordSetList.append({ AvgSetList[i][0],CharaSetList[i][1] });
			}
			else if (CharaSetList[i].length() == 3) {
				if (CharaSetList[i][1] == "") { CharaSetList[i][1] = " "; }
				WordSetList.append({ CharaSetList[i][1],CharaSetList[i][2] });
			}
		}

		int Charanum = WordSetList.length();

		if (Charanum == 1) {
			if (WordSetList[0][1] == "") { AvgSetList[0][6] = ("(亮，沉默)"); }
			else if (WordSetList[0][1] != "") { AvgSetList[0][6] = ("(亮，讲述)"); }
		}
		else if (Charanum == 2) {
			if (WordSetList[0][1] == "" && WordSetList[1][1] == "") {
				AvgSetList[0][6] = ("(亮，沉默)");
				AvgSetList[1][6] = ("(亮，沉默)");
			}
			else if (WordSetList[0][1] != "" && WordSetList[1][1] == "") {
				AvgSetList[0][6] = ("(亮，讲述)");
				AvgSetList[1][6] = ("(暗，沉默)");
			}
			else if (WordSetList[0][1] == "" && WordSetList[1][1] != "") {
				AvgSetList[0][6] = ("(暗，沉默)");
				AvgSetList[1][6] = ("(亮，讲述)");
			}
			else {
				AvgSetList[0][6] = ("(亮，讲述)");
				AvgSetList[1][6] = ("(亮，讲述)");
			}
		}
		if (whichMode == InterpreterMode::debug) {
			if (Charanum > 2) {
				qDebug().noquote() << "检查行" + QString::number(LineNum) + "中存在的讲述控制器数量超限";
			}
		}
		if (whichMode == InterpreterMode::presource) {
			if (Line.contains("===")) {
				ExtendList.append({ QString::number(MeaningfulLine.length() - 1),Line });
			}
			for (int i = 0; i < AvgSetList.length(); i++) {
				QList<Filter> FilterList;
				QStringList FilterRaw = AvgSetList[i][3].split("_");
				for (int i = 0; i < FilterRaw.length(); i++) {
					switch (FilterRaw[i].toInt()) {
					case 1:
						FilterList.append(Filter::gradientMask);
						break;
					case 2:
						FilterList.append(Filter::blackSilhouette);
						break;
					case 3:
						FilterList.append(Filter::fade);
						break;
					case 4:
						FilterList.append(Filter::onlyBW);
						break;
					case 5:
						FilterList.append(Filter::reverseColor);
						break;
					case 6:
						FilterList.append(Filter::turnDark);
						break;
					case 7:
						FilterList.append(Filter::gaussianBlur5);
						break;
					case 8:
						FilterList.append(Filter::gaussianBlur11);
						break;
					default:
						FilterList.append(Filter::unknownFilter);
						break;
					}
				}
				if (AvgSetList[i][6] == "(暗，沉默)") { FilterList.append(Filter::turnDark); }
				if (AvgSetList[i][1] == "") {
					TransThreadList.append(new cTransform(AvgSetList[i][0], "Chara", FilterList, signalsName));
				}
				else {
					TransThreadList.append(new cTransform(AvgSetList[i][0] + "_" + AvgSetList[i][1], "Chara", FilterList, signalsName));
				}

				TransThreadList[TransThreadList.length() - 1]->start();
				TransThreadCount++;
			}
		}
		if (whichMode == InterpreterMode::run || whichMode == InterpreterMode::rerun) {
			if (whichMode == InterpreterMode::run) {
				if (Line.contains("===")) {
					ExtendRawLine = Line;
					InExtend = TRUE;
					return { "JUSTEXTEND","JUSTEXTEND" };
				}
				else {
					InExtend = FALSE;
				}
			}
			emit signalsName->can_update_chara(AvgSetList, Charanum);
			if (Charanum == 1) {
				if (WordSetList[0][0] != "") {
					int frame = AvgSetList[0][4].toFloat() * 30;
					if (frame != 0) {
						for (float i = 0; i < frame; i++) {
							emit signalsName->update_avg_num("M", i / frame);
							QTest::qSleep(33);
						}
					}
					emit signalsName->update_avg_num("M", 1);
				}
			}
			else {
				int frame = max(AvgSetList[0][4].toFloat(), AvgSetList[1][4].toFloat()) * 30;
				if (frame != 0) {
					for (float i = 0; i < frame; i++) {
						emit signalsName->update_avg_num("LR", i / frame);
						QTest::qSleep(33);
					}
				}
				emit signalsName->update_avg_num("LR", 1);
			}
			QString DisplayName = "";
			QString DisplayWords = "";
			QString WordsAll = "";
			//int AlphaCount = 0;
			for (int i = 0; i < WordSetList.length(); i++) {
				if (WordSetList[i][1] != "") {
					DisplayName = WordSetList[i][0];
					DisplayWords = WordSetList[i][1];
					break;
				}
			}
			emit signalsName->update_chara_num(DisplayName, WordsAll, TRUE);
			for (int j = 0; j < DisplayWords.length(); j++) {
				/*ushort chara = DisplayWords[j].unicode();
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
				*/
				WordsAll += DisplayWords[j];
				emit signalsName->update_chara_num(DisplayName, WordsAll, FALSE);
				if (PlaySetList[0].toFloat() != 0) {
					QTest::qSleep(1000 * PlaySetList[0].toFloat() * SpeedFloat + 1);
				}
			}

			emit signalsName->willstop();
			QTest::qSleep((float)1000 * PlaySetList[1].toFloat() * SpeedFloat + 1);
			emit signalsName->show_next();
			parent->pause();
			emit signalsName->inrunning();
			if (Charanum == 1) {
				if (WordSetList[0][0] != "") {
					int frame = AvgSetList[0][5].toFloat() * 30;
					if (frame != 0) {
						for (float i = 0; i < frame; i++) {
							emit signalsName->update_avg_num("M", 1.0 - i / frame);
							QTest::qSleep(33);
						}
					}
					emit signalsName->update_avg_num("M", 1);
				}
			}
			else {
				int frame = max(AvgSetList[0][5].toFloat(), AvgSetList[1][5].toFloat()) * 30;
				if (frame != 0) {
					for (float i = 0; i < frame; i++) {
						emit signalsName->update_avg_num("LR", 1.0 - i / frame);
						QTest::qSleep(33);
					}
				}
				emit signalsName->update_avg_num("LR", 1);
			}
		}
	}

	//自由文本控制器
	else if (Line.mid(0, 3) == ">^>") {
		if (!Line.contains(":")) {
			return { "NOTFOUND","NOTFOUND" };
		}
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
		if (PlaySetList[0] == "") { PlaySetList[0] = "0.04"; }
		if (PlaySetList[1] == "") { PlaySetList[1] = "1.75"; }

		//提取自由文本控制器
		QStringList RAW = Line.mid(3, Line.length() - 3).split(":");
		QStringList FreeSetList = RAW;
		for (int i = 0; i < 2 - RAW.length(); i++) { FreeSetList.append(""); }
		QStringList FreePoList = FreeSetList[0].split("/");
		for (int i = 0; i < 3 - FreeSetList[0].split("/").length(); i++) { FreePoList.append(""); }
		if (FreePoList[0] == "") { FreePoList[0] = "0.125"; }
		if (FreePoList[1] == "") { FreePoList[1] = "0.444"; }
		if (FreePoList[2] == "") { FreePoList[2] = "L"; }

		if (whichMode == InterpreterMode::debug) {
			if (FreeSetList.length() > 2 || FreePoList.length() > 3) {
				qDebug() << "检查行" + QString::number(LineNum) + "存在的自由文本控制器参数个数超限";
			}
		}
		if (whichMode == InterpreterMode::presource) {
			if (Line.contains("===")) {
				ExtendList.append({ QString::number(MeaningfulLine.length() - 1),Line });
			}
		}
		if (whichMode == InterpreterMode::run || whichMode == InterpreterMode::rerun) {
			if (whichMode == InterpreterMode::run) {
				if (Line.contains("===")) {
					ExtendRawLine = Line;
					InExtend = TRUE;
					return { "JUSTEXTEND","JUSTEXTEND" };
				}
				else {
					InExtend = FALSE;
				}
			}
			emit signalsName->can_update_freedom(FreePoList, PlaySetList);
			int AlphaCount = 0;
			QString WordsAll = "";
			FreeSetList[1] = spolEscape(FreeSetList[1]);
			if (PlaySetList[0].toFloat() != 0) {
				for (int j = 0; j < FreeSetList[1].length(); j++) {
					QTest::qSleep(1000 * PlaySetList[0].toFloat() * SpeedFloat + 1);
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
			QTest::qSleep((float)1000 * PlaySetList[1].toFloat() * SpeedFloat + 1);
			emit signalsName->show_next();
			parent->pause();
			emit signalsName->inrunning();
			emit signalsName->can_clear_freedom(1);
		}
	}

	//大分支控制器
	else if (Line.mid(0, 3) == "-->") {
		InExtend = FALSE;
		QStringList RAW = Line.mid(3, Line.length() - 3).split("-->");
		QList<QStringList> JumpSetList;
		QStringList JumpTextList;
		for (int i = 0; i < RAW.length(); i++) {
			JumpSetList.append({ RAW[i].split(":") });
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

	//对象（立绘）移动控制器
	else if (Line.mid(0, 4) == "move" && Line.mid(0, 8) != "moveBack") {
	qDebug() << Line;
		InExtend = FALSE;
		QStringList RAW = Line.mid(5, Line.length() - 6).split(",");
		int RAWLength = RAW.length();
		for (int i = 0; i < 5 - RAWLength ; i++) { RAW.append(""); }
		qDebug() << RAW;
		QStringList MoveSetList;
		RAW[0]=="" ? MoveSetList.append("M") : MoveSetList.append( RAW[0] );
		RAW[1]=="" ? MoveSetList.append("0") : MoveSetList.append( RAW[1] );
		RAW[2]=="" ? MoveSetList.append("0") : MoveSetList.append( RAW[2] );
		RAW[3]=="" ? MoveSetList.append("0") : MoveSetList.append( RAW[3] );
		RAW[4]=="" ? MoveSetList.append("SFS") : MoveSetList.append( RAW[4] );
		MoveSetList[3] = QString::number(MoveSetList[3].toFloat() * 120 + 1);
		qDebug() << MoveSetList;
		if (whichMode == InterpreterMode::presource) {
			if (!MoveList.isEmpty()) {
				QStringList LastMoveList = MoveList.last();
				QStringList LMRSplitList;
				LMRSplitList.append(QString::number(MeaningfulLine.length() - 1));
				if (LastMoveList[1] == "moveBack(L)") {
					if (MoveSetList[0].contains("L")) {
						LMRSplitList.append("move(L," + MoveSetList[1] + "," + MoveSetList[2] + ")");
					}
					else {
						LMRSplitList.append("move(L,0,0)");
					}
				}
				else {
					QStringList Last;
					if (LastMoveList[1] == "INSIDER_NULL") {
						Last = MoveList[MoveList.length() - 2][1].split(",");
					}
					else {
						Last = MoveList.last()[1].split(",");
					}
					if (MoveSetList[0].contains("L")) {
						LMRSplitList.append("move(L," + QString::number(Last[1].toFloat() + MoveSetList[1].toFloat()) + "," + QString::number(Last[2].mid(0, Last[2].length() - 1).toFloat() + MoveSetList[2].toFloat()) + ")");
					}
					else {
						LMRSplitList.append(Last.join(","));
					}
				}
				
				if (LastMoveList[2] == "moveBack(M)") {
					if (MoveSetList[0].contains("M")) {
						LMRSplitList.append("move(M," + MoveSetList[1] + "," + MoveSetList[2] + ")");
					}
					else {
						LMRSplitList.append("move(M,0,0)");
					}
				}
				else {
					QStringList Last;
					if (LastMoveList[2] == "INSIDER_NULL") {
						Last = MoveList[MoveList.length() - 2][2].split(",");
					}
					else {
						Last = MoveList.last()[2].split(",");
					}
					if (MoveSetList[0].contains("M")) {
						LMRSplitList.append("move(M," + QString::number(Last[1].toFloat() + MoveSetList[1].toFloat()) + "," + QString::number(Last[2].mid(0, Last[2].length() - 1).toFloat() + MoveSetList[2].toFloat()) + ")");
					}
					else {
						LMRSplitList.append(Last.join(","));
					}
				}
				
				if (LastMoveList[3] == "moveBack(R)") {
					if (MoveSetList[0].contains("R")) {
						LMRSplitList.append("move(R," + MoveSetList[1] + "," + MoveSetList[2] + ")");
					}
					else {
						LMRSplitList.append("move(R,0,0)");
					}
				}
				else {
					QStringList Last;
					if (LastMoveList[3] == "INSIDER_NULL") {
						Last = MoveList[MoveList.length() - 2][3].split(",");
					}
					else {
						Last = MoveList.last()[3].split(",");
					}
					if (MoveSetList[0].contains("R")) {
						LMRSplitList.append("move(R," + QString::number(Last[1].toFloat() + MoveSetList[1].toFloat()) + "," + QString::number(Last[2].mid(0, Last[2].length() - 1).toFloat() + MoveSetList[2].toFloat()) + ")");
					}
					else {
						LMRSplitList.append(Last.join(","));
					}
				}
				MoveList.append(LMRSplitList);
			}
			else {
				QStringList LMRSplitList;
				LMRSplitList.append(QString::number(MeaningfulLine.length() - 1));
				if (MoveSetList[0].contains("L")) {
					LMRSplitList.append("move(L,"+MoveSetList[1]+","+MoveSetList[2]+")");
				}
				else {
					LMRSplitList.append("move(L,0,0)");
				}
				if (MoveSetList[0].contains("M")) {
					LMRSplitList.append("move(M," + MoveSetList[1] + "," + MoveSetList[2]+")");
				}
				else {
					LMRSplitList.append("move(L,0,0)");
				}
				if (MoveSetList[0].contains("R")) {
					LMRSplitList.append("move(R," + MoveSetList[1] + "," + MoveSetList[2] + ")");
				}
				else {
					LMRSplitList.append("move(R,0,0)");
				}
				MoveList.append(LMRSplitList);
			}
		}
		if (whichMode == InterpreterMode::run) {
			emit signalsName->willstop();
			if (MoveSetList[4] == "K") {
				for (int i = 1; i <= MoveSetList[3].toInt(); i++) {
					emit signalsName->move_AVG_to(MoveSetList[0], MoveSetList[1].toFloat() / MoveSetList[3].toFloat(), MoveSetList[2].toFloat() / MoveSetList[3].toFloat());
					QTest::qSleep(8 * SpeedFloat);
				}
			}else if (MoveSetList[4] == "FS") {
				for (int i = 1; i <= MoveSetList[3].toInt(); i++) {
					double d = qSin((i * 3.1415) / (2 * MoveSetList[3].toInt())) - qSin(((i - 1) * 3.1415) / (2 * MoveSetList[3].toInt()));
					emit signalsName->move_AVG_to(MoveSetList[0], MoveSetList[1].toFloat() * d, MoveSetList[2].toFloat() *d);
					QTest::qSleep(8 * SpeedFloat);
				}
			}
			else if (MoveSetList[4] == "SF") {
				for (int i = MoveSetList[3].toInt(); i >= 1; i--) {
					double d = qSin((i * 3.1415) / (2 * MoveSetList[3].toInt())) - qSin(((i - 1) * 3.1415) / (2 * MoveSetList[3].toInt()));
					emit signalsName->move_AVG_to(MoveSetList[0], MoveSetList[1].toFloat() * d, MoveSetList[2].toFloat() * d);
					QTest::qSleep(8 * SpeedFloat);
				}
			}
			else if (MoveSetList[4] == "SFS") {
				for (int i = MoveSetList[3].toInt(); i >= 1; i--) {
					double d = (-qPow(qCos((i * 3.1415) / (MoveSetList[3].toInt())) + 1, 2) + qPow(qCos(((i - 1) * 3.1415) / (MoveSetList[3].toInt())) + 1, 2)) / 4;
					emit signalsName->move_AVG_to(MoveSetList[0], MoveSetList[1].toFloat() * d, MoveSetList[2].toFloat() * d);
					QTest::qSleep(8 * SpeedFloat);
				}
			}
			emit signalsName->show_next();
			parent->pause();
			emit signalsName->inrunning();
		}
	}
	
	//对象（立绘）移回控制器
	else if (Line.mid(0, 8) == "moveBack") {
		InExtend = FALSE;
		QString RAW = Line.mid(9, Line.length() - 10);
		if (RAW == "") { RAW = "LMR"; }
		if (whichMode == InterpreterMode::presource) {
			if (!MoveList.isEmpty()) {
				QStringList MoveSetList;
				MoveSetList.append(QString::number(MeaningfulLine.length() - 1));
				if (RAW.contains("L")) {
					MoveSetList.append("moveBack(L)");
				}
				else {
					MoveSetList.append("INSIDER_NULL");
				}
				if (RAW.contains("M")) {
					MoveSetList.append("moveBack(M)");
				}
				else {
					MoveSetList.append("INSIDER_NULL");
				}
				if (RAW.contains("R")) {
					MoveSetList.append("moveBack(R)");
				}
				else {
					MoveSetList.append("INSIDER_NULL");
				}
				MoveList.append(MoveSetList);
			}
			else {
				MoveList.append({ QString::number(MeaningfulLine.length() - 1),"moveBack(L)","moveBack(M)","moveBack(R)" });
			}
		}
		if (whichMode == InterpreterMode::run) {
			emit signalsName->move_AVG_back(RAW);
		}
	}
	
	else {
		if (whichMode == InterpreterMode::presource) {
			QFile tryFile;
			tryFile.setFileName(PROPATH::Users + "/source/BGP/" + Line + ".png");
			if (tryFile.exists() || Line == "黑场") {
				BGPList.append({ QString::number(MeaningfulLine.length() - 1),"BGP(" + Line + ")" });
			}
			tryFile.setFileName(PROPATH::Users + "/source/Sound/" + Line + ".mp4");
			if (tryFile.exists()) {
				BGMList.append({ QString::number(MeaningfulLine.length() - 1),"BGM(" + Line + ")" });
			}
		}
		return { "NOTFOUND","NOTFOUND" };
	}

	return { "NORMAL","NORMAL" };
};




QStringList GPOLSingle(int LineNum, QString Line, GPOLInterpreterMode whichMode, InterpreterSignals* signalsName, mQThread* parent) {
	return {};
}





