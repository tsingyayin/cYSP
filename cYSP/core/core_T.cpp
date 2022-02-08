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
���������ٶȹ��죬�̼߳���ֵ���п�����Ϊ�̳߳�ͻ�����������������ļ��������㣬����Python���м��������ڣ�����C++�汾�г�����
Ϊ�˱����ɴ˿��������Ǹ��������������5��ĵȴ����ޡ���5����Բ����㣬�����ִ�н������Ľ�����䡣
�������㣬5��ĵȴ�ʱ��Լ���ڴ󲿷����м������1080P����ʱԤ�ȴ���50��ͼ������Ҫ��ƽ���ٶȡ�
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
		//qDebug().noquote() << "-->��������Ԥ���ͺ���Դ����ģ��<--- ";
		emit signalsName->send_kernal_info("-->��������Ԥ���ͺ���Դ����ģ��<---");
		bool InNotes = FALSE;
		TransThreadCount = 0;
		TransPictureName.clear();
		MeaningfulLine.clear();
		BGPList.clear();
		BGMList.clear();
		CVRList.clear();
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
		if (MeaningfulLine.isEmpty()) { MeaningfulLine.append(">>>:"); }
		
		//װ����ת�б�
		emit signalsName->set_scroll_info();

		//���̵߳ȴ�����
		for (int i = 0; i < 10; i++) {
			QTest::qSleep(500);
			if (TransThreadCount <= 0) { break; }
		}
		//׷�ӳ�ʱ�������б�
		BGPList.append({ "51200","BGP(�ڳ�)" });
		BGMList.append({ "51200","BGM()" });
		CVRList.append({"51200","CVR()"});
		//qDebug().noquote() << "InterpreterInfo���ɹ�Ԥ�޳�ע����";
		emit signalsName->send_kernal_info("InterpreterInfo���ɹ�Ԥ�޳�ע����");
		
		
		//ʵʱ����ģ��
		//qDebug().noquote() << "-->��������ʵʱ����ģ��<--- ";
		emit signalsName->send_kernal_info("-->��������ʵʱ����ģ��<---");
		QTest::qSleep(2000);
		LineNum = -1;
		justJump = FALSE;
		QStringList LineResult;
		QString Note = "UNKOWN_NOTE";
		bool InBranch=FALSE;
		bool FindBranch = FALSE;
		exitNow = FALSE;

		emit signalsName->can_show_title();
		QTest::qSleep(4000);
		emit signalsName->can_hide_title();
		QTest::qSleep(900);
		//�滻���ؼ�
		if (FirstEnter) { emit signalsName->can_prepare_play(); }

		//������ѭ��
		for (;;) {
			LineNum += 1;

			//ȷ�ϱ�ѭ��Ŀ���кţ��Լ��Ƿ��Դ�������״̬�������������˳�������ѭ��
			if (LineNum == MeaningfulLine.length() || exitNow==TRUE) {
				LineResult[0] = "FILEEND";
				LineResult[1] = "FILEEND";
				break;
			}

			//���ڸո������ת�����������һ��ʱ������
			if (justJump == TRUE) {
				InBranch = FALSE;
				for (int i = BGPList.length() - 1; i >= 0; i--) {
					if (BGPList[i][0].toInt() <= LineNum) {
						SingleLine(BGPList[i][0].toInt() ,BGPList[i][1],InterpreterMode::run,signalsName, parent);
						break;
					}
				}
				for (int i = BGMList.length() - 1; i >= 0; i--) {
					if (BGMList[i][0].toInt() <= LineNum) {
						SingleLine(BGMList[i][0].toInt() ,BGMList[i][1], InterpreterMode::run, signalsName, parent);
						break;
					}
				}	
				for (int i = CVRList.length() - 1; i >= 0; i--) {
					if (CVRList[i][0].toInt() <= LineNum) {
						SingleLine(CVRList[i][0].toInt(), CVRList[i][1], InterpreterMode::run, signalsName, parent);
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
				storyFilename = "./Users_Data/story/"+LineResult[1]+".spol";
				FirstEnter = FALSE;
				break;
			}
		}
		//�˳��ĵ�ѭ��
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
		if (!TransPictureName.contains(NewPictureName) && gAddname!="") {
			TransPictureName.append(NewPictureName);
			//qDebug().noquote() << "InterpreterInfo����Ҫ���� :" + NewPictureName;
			gSignalsName->send_kernal_info("InterpreterInfo����Ҫ���� :" + NewPictureName);
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
						transformation(gFilterList[i], &r, &g, &b, &a, y, Y ,colorMatrix);
					}
					NewImage.setPixel(x, y, qRgba(r, g, b, a));
				}
			}
			NewImage.save(NewPictureName);
			//qDebug().noquote() << "InterpreterInfo���ɹ����� :" + NewPictureName;
			gSignalsName->send_kernal_info("InterpreterInfo���ɹ����� :" + NewPictureName);
		}
		TransThreadCount--;
		this->deleteLater();
	}
};

QList<cTransform*> TransThreadList;

QStringList SingleLine(int LineNum ,QString Line, InterpreterMode whichMode, InterpreterSignals* signalsName, mQThread* parent) {
	if (whichMode == InterpreterMode::presource) {
		MeaningfulLine.append(Line);
		if (Line[0] != "|" || Line.mid(0,3)=="|||" && Line!="|||" ) {
			emit signalsName->save_line_list({ QString::number(MeaningfulLine.length() - 1),Line });
		}
		if (Line[0] == "|") { Line = Line.mid(1, Line.length() - 1); }
	}
	if (whichMode == InterpreterMode::run) {
		emit signalsName->now_which_line(LineNum);
	}
	
	//����������
	if (Line.mid(0, 3) == "BGP" || Line.mid(0, 8) == "backdrop") {
		QStringList RAW = Line.mid(Line.indexOf("(") + 1, Line.lastIndexOf(")") - Line.indexOf("(") - 1).split(",");
		/*QStringList BGSetList = RAW;
		for (int i = 0; i < 4 - RAW.length(); i++) { BGSetList.append(""); }
		if (BGSetList[0] == "") { BGSetList[0] = "�ڳ�"; }
		if (BGSetList[1] == "") { BGSetList[1] = "0"; }
		if (BGSetList[2] == "") { BGSetList[2] = "0"; }
		if (BGSetList[3] == "") { BGSetList[3] = "0.5"; }	
		try {
			if (0 > BGSetList[2].toInt() || BGSetList[2].toInt() > 3) { throw "Exception"; }
			if (0 > BGSetList[3].toFloat()) { throw "Exception"; }
		}
		catch (...) {
			if (whichMode == InterpreterMode::debug) {
				qDebug().noquote() << "�����" + QString::number(LineNum) + "�б������������ڵ���ֵ�趨����";
			}
		}*/

		int RAWLength = RAW.length();
		for (int i = 0; i < 4 - RAWLength; i++) { RAW.append(""); }
		Controller::Backdrop::Data SetList;
		SetList.Backdrop = (RAW[0] == "" ? "�ڳ�" : RAW[0]);
		SetList.Filter = (RAW[1] == "" ? "0" : RAW[1]);
		SetList.Effect = (RAW[2] == "" ? "0" : RAW[2]).toInt();
		SetList.Time = (RAW[3] == "" ? "0.5" : RAW[3]).toFloat();

		if (whichMode == InterpreterMode::presource) {
			BGPList.append({ QString::number(MeaningfulLine.length() - 1),Line });
			QList<Filter> FilterList;
			QStringList FilterRaw=SetList.Filter.split("_");
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
					QTest::qSleep((float)15*SpeedFloat);
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

	//���ֿ���������Ч������
	else if (Line.mid(0, 3) == "BGM" || Line.mid(0, 5) == "music" || Line.mid(0, 3) == "SND" || Line.mid(0, 5) == "sound") {
		QStringList RAW = Line.mid(Line.indexOf("(") + 1, Line.lastIndexOf(")") - Line.indexOf("(") - 1).split(",");
		int RAWLength = RAW.length();
		for (int i = 0; i < RAWLength; i++) { RAW.append(""); }
		Controller::music::Data SetList;
		SetList.music = (RAW[0] == "" ? "����" : RAW[0]);
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

	//���ֿ��տ�����
	else if (Line.mid(0, 3) == "CVR" || Line.mid(0, 5) == "cover") {
		QString UserSet;
		bool Cover=TRUE;
		if (Line.mid(0, 3) == "CVR") {UserSet = Line.mid(4, Line.length() - 5);
		}
		else {UserSet = Line.mid(6, Line.length() - 7);
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
		if (PlaySetList[0] == "") { PlaySetList[0] = "0.04"; }
		if (PlaySetList[1] == "") { PlaySetList[1] = "1.75"; }

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
			if (AvgSetList[i][4] == "") { AvgSetList[i][4] = "0"; }
			if (AvgSetList[i][5] == "") { AvgSetList[i][5] = "0"; }
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

		if (Charanum == 1) {
			if (WordSetList[0][1] == "") { AvgSetList[0][6]=("(������Ĭ)"); }
			else if (WordSetList[0][1] != "") { AvgSetList[0][6]=("(��������)"); }
		}
		else if (Charanum == 2) {
			if (WordSetList[0][1] == "" && WordSetList[1][1] == "") {
				AvgSetList[0][6]=("(������Ĭ)");
				AvgSetList[1][6] = ("(������Ĭ)");
			}
			else if (WordSetList[0][1] != "" && WordSetList[1][1] == "") {
				AvgSetList[0][6] = ("(��������)");
				AvgSetList[1][6] = ("(������Ĭ)");
			}
			else if (WordSetList[0][1] == "" && WordSetList[1][1] != "") {
				AvgSetList[0][6] = ("(������Ĭ)");
				AvgSetList[1][6] = ("(��������)");
			}else {
				AvgSetList[0][6] = ("(��������)");
				AvgSetList[1][6] = ("(��������)");
			}
		}
		if (whichMode == InterpreterMode::debug) {
			if (Charanum > 2) {
				qDebug().noquote() << "�����" + QString::number(LineNum) + "�д��ڵĽ�����������������";
			}
		}
		if (whichMode == InterpreterMode::presource) {
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
				if (AvgSetList[i][6] == "(������Ĭ)") { FilterList.append(Filter::turnDark); }
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
		if (whichMode == InterpreterMode::run) {
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
			int AlphaCount = 0;
			for (int i = 0; i < WordSetList.length(); i++) {
				if (WordSetList[i][1] != "") { 
					DisplayName = WordSetList[i][0];
					DisplayWords = WordSetList[i][1];
					break;
				}
			}
			emit signalsName->update_chara_num(DisplayName, WordsAll, TRUE);
			for (int j = 0; j < DisplayWords.length(); j++) {				
				ushort chara = DisplayWords[j].unicode();
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
				WordsAll += DisplayWords[j];
				emit signalsName->update_chara_num(DisplayName, WordsAll, FALSE);
				if (PlaySetList[0].toFloat() != 0) {
					QTest::qSleep(1000 * PlaySetList[0].toFloat() * SpeedFloat);
				}
			}

			emit signalsName->willstop();
			QTest::qSleep((float)1000 * PlaySetList[1].toFloat() * SpeedFloat);
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
		if (PlaySetList[0] == "") { PlaySetList[0] = "0.04"; }
		if (PlaySetList[1] == "") { PlaySetList[1] = "1.75"; }

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
				qDebug() << "�����" + QString::number(LineNum) + "���ڵ������ı�������������������";
			}
		}

		if (whichMode == InterpreterMode::run) {
			emit signalsName->can_update_freedom(FreePoList, PlaySetList);
			int AlphaCount = 0;
			QString WordsAll = "";
			FreeSetList[1] = spolEscape(FreeSetList[1]);
			if (PlaySetList[0].toFloat() != 0) {
				for (int j = 0; j < FreeSetList[1].length(); j++) {
					QTest::qSleep(1000 * PlaySetList[0].toFloat() * SpeedFloat);
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
			QTest::qSleep((float)1000 * PlaySetList[1].toFloat() * SpeedFloat);
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

	//���������
	//��������������� ~~>ObjectName:TransName:Parameter:Keep
	//�����������ʼ������ ~~>ObjectName:initAll
	//������ϣ���������������岻���������������ֶε���д֮����κ�������д��
	else if (Line.mid(0, 3) == "~~>") {
		QStringList RAW = Line.mid(3, Line.length() - 3).split(":");
		QStringList ObjectSettings;
		if (RAW.contains("initAll")) {
			ObjectSettings.append(RAW[0]);
			ObjectSettings.append(RAW[1]);
			ObjectSettings.append("VOID");
			ObjectSettings.append("1");
		}
		else {
			ObjectSettings += RAW;
			for (int i = 0; i < 4 - ObjectSettings[0].split("/").length(); i++) { ObjectSettings.append(""); }
			if (ObjectSettings[0] == "") { ObjectSettings[0] = "EMPTYOBJECT"; }
			if (ObjectSettings[1] == "") { ObjectSettings[1] = "EMPTYTFUNC"; }
			if (ObjectSettings[2] == "") { ObjectSettings[2] = "EMPTYPARA"; }
			if (ObjectSettings[3] == "") { ObjectSettings[3] = "1"; }
		}
	}

	//�Ƿ��ı�����
	else {
		if (Line[0] != "/" && Line.mid(0, 5) != "title") {
			if (whichMode == InterpreterMode::debug) {
				qDebug() << "�����" + QString::number(LineNum) + "�еķǷ��ı�";
			}
			if (whichMode == InterpreterMode::run) {
				signalsName->send_EIFL_info("SPOL�﷨�쳣��", "����ʶ���� " + QString::number(LineNum) + " �е�����", Line, EIFL::SSE);
			}
		}
	}

	return { "NORMAL","NORMAL" };
};