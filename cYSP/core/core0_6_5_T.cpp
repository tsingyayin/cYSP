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
cYSP�������߼���ͬ��Python�汾�����ȣ�cYSP��ԭ����Ԥ������ģ�P���ģ������������ģ�U���ģ��Ĵ���϶�Ϊһ
����Ϊ������ģ�T���ģ���presourceģʽ��runģʽ�����Ұ�ԭ����U����ʵʱ����ʱ�����ı�����Ϣ��ΪT���ĵ�debugģʽ�Լ��ٿ���̨��Ⱦ
��Σ���presource�׶Σ����������˴���ͼ���˾�֮�⣬��Ҫ��Դ�ļ�����ȡ�����У���Ԥ���޳�ע�ͣ������޳������﷨�����У���
�Լ���ʵʱ���й�������������ע��ʱ�����Ŀ��١�
���ң�Ϊ�˱�֤������ת֮�������Ч�������������ڰ�����ת֮����ȳ��Դ�Ŀ������ǰ����һ����Ч��BGM�ͱ������ټ�������Ŀ���н��͡�
���ͬʱ����Python���У����֧����������ת����UICoreLauncher���д������ڴ���֮����������������������
��������ͳһ�ý�����������ͨ���ĵ�ѭ�����������⡣ȷ����UICoreLauncherֻ��һ��������������һ��SPOL���Ͷ��ɽ�����������ɡ�
���ڶ��̴߳���ͼ������C++�����ٶ�����Python����˲���ռ��̫��ʱ�䣬��Ӧ�ģ���cYSP�У����Ǽ����˻����ȴ�ʱ�䡣
���������ٶȹ��죬�̼߳���ֵ���п�����Ϊ�̳߳�ͻ���������ļ��������㣬����Python���м��������ڣ�����C++�汾�г�����
Ϊ�˱����ɴ˿��������Ǹ��������������5��ĵȴ����ޡ���5����Բ����㣬�����ִ�н������Ľ�����䡣
*/

//����������
void Interpreter(QString storyFilename, InterpreterSignals *signalsName, mQThread *parent ) {
	QFile CurrentSPOLFile;
	SpeedFloat = 1.0;
	bool FirstEnter = TRUE;
	//ͨ���ĵ�ѭ��
	while (TRUE) {
		//�ļ���ȡ
		CurrentSPOLFile.setFileName(storyFilename);
		CurrentSPOLFile.open(QIODevice::ReadOnly | QIODevice::Text);
		if (!CurrentSPOLFile.isOpen()) { return; }
		QTextStream CurrentSPOLText(&CurrentSPOLFile);
		CurrentSPOLText.setCodec("UTF-8");
		//������ת�б�
		emit signalsName->clr_line_list();
		//����Ԥ����
		qDebug().noquote() << "-->��������Ԥ���ͺ���Դ����ģ��<--- ";
		bool InNotes = FALSE;
		TransThreadCount = 0;
		TransPictureName.clear();
		MeaningfulLine.clear();
		//Ԥ����ѭ��
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
		qDebug().noquote() << "InterpreterInfo���ɹ�Ԥ�޳�ע����";
		//װ����ת�б�
		emit signalsName->set_scroll_info();
		//�������׶ζ���
		if (FirstEnter) { 
			Sleep(4000);
			emit signalsName->can_hide_title();
			Sleep(1000); 
		}
		//���̵߳ȴ�����
		for (int i = 0; i < 10; i++) {
			Sleep(500);
			if (TransThreadCount <= 0) { break; }
		}
		//׷�ӳ�ʱ�������б�
		BGPList.append({ "51200","[�ڳ�]" });
		BGMList.append({ "51200","{}" });
		
		//�滻���ؼ�
		if (FirstEnter) { emit signalsName->can_prepare_play(); }

		//ʵʱ����ģ��
		qDebug().noquote() << "-->��������ʵʱ����ģ��<--- ";
		LineNum = -1;
		justJump = FALSE;
		QStringList LineResult;
		QString Note = "UNKOWN_NOTE";
		bool InBranch=FALSE;
		bool FindBranch = FALSE;
		exitNow = FALSE;
		
		//������ѭ��
		for (;;) {
			LineNum += 1;

			//ȷ�ϱ�ѭ��Ŀ���кţ��Լ��Ƿ��Դ�������״̬
			if (LineNum == MeaningfulLine.length() || exitNow==TRUE) {
				LineResult[0] = "FILEEND";
				LineResult[1] = "FILEEND";
				break;
			}

			//���ڸո������ת�����������һ��ʱ������
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

			//����������ȡ����ǰ��
			QString CurrentLine = MeaningfulLine[LineNum];
			
			//Ԥ����С��֧�������������С��֧��ʼ�����
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

			//Ԥ����С��֧��������������ǩ�Ƿ�ƥ��
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

			//Ԥ����С��֧����������ƥ���ǩ��ʶ���ǩ��
			if (CurrentLine[0] == "|" && CurrentLine.mid(0, 2) != "||" && CurrentLine.mid(0, 3) != "|||" ) {
				if (FindBranch==FALSE) {continue;}
				else {
					CurrentLine = CurrentLine.mid(1, CurrentLine.length() - 1);
				}
				
			}

			//���͵�ǰ��
			LineResult = SingleLine(LineNum, CurrentLine, InterpreterMode::run, signalsName, parent);
			
			//���ڴ��֧�������ķ��ؽ�������ĵ�ˢ��
			if (LineResult[0] == "FILEJUMP") {
				CurrentSPOLFile.close();
				storyFilename = "./story/"+LineResult[1]+".spol";
				FirstEnter = FALSE;
				break;
			}
		}
		//�˳�ѭ��
		if (LineResult[0] == "FILEEND") {
			break;
		}
	}
};

//ͨ���˾������߳�
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
			qDebug().noquote() << "InterpreterInfo����Ҫ���� :" + NewPictureName;
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
			qDebug().noquote() << "InterpreterInfo���ɹ����� :" + NewPictureName;
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
	
	//����������
	if (Line[0] == "[") {
		QStringList RAW = Line.mid(1, Line.length() - 2).split(",");
		QStringList BGSetList = RAW;
		for (int i = 0; i < 4 - RAW.length(); i++) { BGSetList.append(""); }
		if (BGSetList[0] == "") { BGSetList[0] = "�ڳ�"; }
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
				qDebug().noquote() << "�����" + QString::number(LineNum) + "�б������������ڵ���ֵ�趨����";
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

	//���ֿ���������Ч������
	else if (Line[0] == "{" || Line[0] == "<") {
		QStringList RAW = Line.mid(1, Line.length() - 2).split(",");
		QStringList MusicSetList = RAW;
		for (int i = 0; i < 2 - RAW.length(); i++) { MusicSetList.append(""); }
		if (MusicSetList[0] == "") { MusicSetList[0] = "����"; }
		if (MusicSetList[1] == "") { MusicSetList[1] = "50"; }

		if (whichMode == InterpreterMode::debug) {
			if (RAW.length() > 2) { qDebug() << "�����" + QString::number(LineNum) + "�д��ڵ���Ƶ����Ч�����������������޵�����"; }
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

	//����������
	else if (Line.mid(0, 3) == ">>>") {
		//������ȡ�н�פ�������������У�
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

		//��ȡ����������ȫ��
		QStringList RAW = Line.mid(3, Line.length() - 3).split(">>>");
		QList<QStringList> CharaSetList;
		for (int i = 0; i < RAW.length(); i++) {
			CharaSetList.append({ RAW[i].split(":") });
		}
		//�ӽ���������ȫ����ȡ��������
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
		//�ӽ���������ȫ����ȡ�ı�����
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
			if (WordSetList[0][1] == "") { AvgSetList[0].append("(������Ĭ)"); }
			else if (WordSetList[0][1] != "") { AvgSetList[0].append("(��������)"); }
		}
		else if (Charanum == 2) {
			if (WordSetList[0][1] == "" && WordSetList[1][1] == "") {
				AvgSetList[0].append("(������Ĭ)");
				AvgSetList[1].append("(������Ĭ)");
				if (WordSetList[0][0] == "" && WordSetList[1][0] == "") { BGBlack = FALSE; }
			}
			else if (WordSetList[0][1] != "" && WordSetList[1][1] == "") {
				AvgSetList[0].append("(��������)");
				AvgSetList[1].append("(������Ĭ)");
			}
			else if (WordSetList[0][1] == "" && WordSetList[1][1] != "") {
				AvgSetList[0].append("(������Ĭ)");
				AvgSetList[1].append("(��������)");
			}else {
				AvgSetList[0].append("(��������)");
				AvgSetList[1].append("(��������)");
			}
		}
		if (whichMode == InterpreterMode::debug) {
			if (Charanum > 2) {
				qDebug().noquote() << "�����" + QString::number(LineNum) + "�д��ڵĽ�����������������";
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
				if (AvgSetList[i][6] == "(������Ĭ)") { FilterList.append(Filter::turnDark); }
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

	//�����ı�������
	else if (Line.mid(0, 3) == ">^>") {
	//������ȡ�н�פ�������������У�
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

		//��ȡ�����ı�������
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
				qDebug() << "�����" + QString::number(LineNum) + "���ڵ������ı�������������������";			}
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
	
	//���֧������
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

	//�Ƿ��ı�����
	else {
		if (whichMode == InterpreterMode::debug) {
			qDebug() << "�����" + QString::number(LineNum) + "�еķǷ��ı�";
		}
	}
	return { "NORMAL","NORMAL" };
};

