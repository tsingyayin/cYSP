#pragma once
#include <QtCore>
#include "../global_value.h"
class GPOLSubInterpreterForSPOL :public QObject
{
public:
	QString output;
	QString edition;
	GPOLSubInterpreterForSPOL() {
	}
	bool Interpreter(QString storyFilename) {
		QFile CurrentSPOLFile;
		output.clear();
		CurrentSPOLFile.setFileName(storyFilename);
		CurrentSPOLFile.open(QIODevice::ReadOnly | QIODevice::Text);
		if (!CurrentSPOLFile.isOpen()) { return FALSE; }
		QTextStream CurrentSPOLText(&CurrentSPOLFile);
		CurrentSPOLText.setCodec("UTF-8");
		bool InNotes = FALSE;
		for (int i = 1;; i++) {
			QString CurrentLine = CurrentSPOLText.readLine();
			CurrentLine = CurrentLine.split("#")[0];
			if (CurrentLine.mid(0, 3) == "###") {
				InNotes = !InNotes;
			}
			if (!InNotes) {
				if (CurrentLine[0] == "/") {
					versionLine(CurrentLine);
				}
				if (edition == "SPOL0.9.0") {
					if (CurrentLine != "") {
						SPOL090SingleLine(CurrentLine, i);
					}
				}
			}
			if (CurrentSPOLText.atEnd()) { break; }
		}
		output.append("USE System.Player.PlayerPage.prepareStop VOID;\n");

		QFile CurrentGPOLFile;
		CurrentGPOLFile.setFileName(storyFilename + ".gpol");
		CurrentGPOLFile.open(QIODevice::WriteOnly | QIODevice::Text);
		//qDebug() << output;
		//qDebug() << edition;
		CurrentGPOLFile.write(output.toLocal8Bit().data());
		CurrentGPOLFile.close();
		return TRUE;
	}
	void versionLine(QString Line) {
		QString Edition = Line.mid(1, Line.length() - 1);
		QStringList EditionList = Edition.split("-");
		if (EditionList.length() == 2) {
			if (EditionList[1] == "FollowNew");
			Edition = "SPOL" + PROINFO::SPOL;
		}
		else {
			Edition = EditionList[0];
		}
		edition = Edition;
	}
	void SPOL090SingleLine(QString Line, int LineNum) {
		if (Line.mid(0, 5) == "title") {
			QStringList ArgList = Line.mid(6, Line.length() - 7).split(":");
			QString Out = "USE System.Player.TitlePage.setTitle";
			for (int i = 0; i < ArgList.length(); i++) {
				ArgList[i] = "\"" + ArgList[i] + "\"";
			}
			Out.append(" " + ArgList.join(" ") + ";\n");
			output.append(Out);
			output.append("USE System.Player.TitlePage.show VOID;\n");
			output.append("USE System.wait 3000;\n");
			output.append("USE System.Player.TitlePage.hide VOID;\n");
			output.append("USE System.Player.PlayerPage.preparePlay VOID;\n");
		}
		else if (Line.mid(0, 5) == "sound" || Line.mid(0, 3) == "SND") {
			output.append("EPT NONE VOID;\n");
			QStringList ArgList;
			QString Out = "USE System.Player.SoundService.setSound";
			if (Line.mid(0, 5) == "sound") {
				ArgList = Line.mid(6, Line.length() - 7).split(",");
			}
			else {
				Line.mid(4, Line.length() - 5).split(",");
			}
			int RAWLength = ArgList.length();
			for (int i = 0; i < 2 - RAWLength; i++) { ArgList.append(""); }
			ArgList[0] = (ArgList[0] == "" ? "__NONE__" : ArgList[0]);
			ArgList[1] = (ArgList[1] == "" ? "0" : ArgList[1]);
			Out.append(" \"" + ArgList[0] + "\" \"" + ArgList[1] + "\";\n");
			output.append(Out);
			output.append("USE System.Player.SoundService.playSound VOID;\n");
		}
		else if (Line.mid(0, 5) == "music" || Line.mid(0, 3) == "BGM") {
			output.append("EPT NONE VOID;\n");
			QStringList ArgList;
			QString Out = "USE System.Player.SoundService.setMusic";
			if (Line.mid(0, 5) == "music") {
				ArgList = Line.mid(6, Line.length() - 7).split(",");
			}
			else {
				Line.mid(4, Line.length() - 5).split(",");
			}
			int RAWLength = ArgList.length();
			for (int i = 0; i < 2 - RAWLength; i++) { ArgList.append(""); }
			ArgList[0] = (ArgList[0] == "" ? "__NONE__" : ArgList[0]);
			ArgList[1] = (ArgList[1] == "" ? "0" : ArgList[1]);
			Out.append(" \"" + ArgList[0] + "\" \"" + ArgList[1] + "\" \"Loop\";\n");
			output.append("USE System.Player.SoundService.tryStopMusic VOID;\n");
			output.append(Out);
			output.append("USE System.Player.SoundService.playMusic VOID;\n");
		}
		else if (Line.mid(0, 3) == "CVR" || Line.mid(0, 5) == "cover") {
			output.append("EPT NONE VOID;\n");
			QString UserSet;
			QString Cover = "TRUE";
			if (Line.mid(0, 3) == "CVR") {
				UserSet = Line.mid(4, Line.length() - 5);
			}
			else {
				UserSet = Line.mid(6, Line.length() - 7);
			}
			qDebug() << UserSet;
			if (UserSet == "true" || UserSet == "on") { Cover = "TRUE"; }
			else if (UserSet == "false" || UserSet == "off") { Cover = "FALSE"; }
			output.append("USE System.Player.PlayerPage.setCoverStatus " + Cover + ";\n");
		}
		else if (Line.mid(0, 3) == ">>>") {
			output.append("TAG FROM AUTO_WNFC;\n");
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
					WordSetList.append({ CharaSetList[i][1],CharaSetList[i][2] });
				}
			}

			int Charanum = WordSetList.length();

			if (Charanum == 1) {
				if (WordSetList[0][1] == "") { AvgSetList[0][6] = ("(亮，沉默)"); }
				else if (WordSetList[0][1] != "") { AvgSetList[0][6] = ("(亮，讲述)"); }
				for (int i = 0; i < AvgSetList[0].length(); i++) {
					AvgSetList[0][i] = "\"" + AvgSetList[0][i] + "\"";
				}
				output.append("USE System.Player.PlayerPage.AVG_L.hide VOID;\n");
				output.append("USE System.Player.PlayerPage.AVG_R.hide VOID;\n");
				output.append("USE System.Player.PlayerPage.AVG_M.setAVG " + AvgSetList[0].join(" ") + ";\n");
				output.append("USE System.Player.PlayerPage.AVG_M.show VOID;\n");
				output.append("USE System.Player.PlayerPage.NameLabel.setText \"" + WordSetList[0][0] + "\";\n");
				output.append("USE System.Player.PlayerPage.WordLabel.setText \"" + PlaySetList[0] + "\" \"" + WordSetList[0][1] + "\" \"" + PlaySetList[1] + "\";\n");
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
				for (int i = 0; i < AvgSetList[0].length(); i++) {
					AvgSetList[0][i] = "\"" + AvgSetList[0][i] + "\"";
					AvgSetList[1][i] = "\"" + AvgSetList[1][i] + "\"";
				}
				output.append("USE System.Player.PlayerPage.AVG_M.hide VOID;\n");
				output.append("USE System.Player.PlayerPage.AVG_L.setAVG " + AvgSetList[0].join(" ") + ";\n");
				output.append("USE System.Player.PlayerPage.AVG_R.setAVG " + AvgSetList[1].join(" ") + ";\n");
				output.append("USE System.Player.PlayerPage.showAVGLR VOID;\n");
				if (WordSetList[0][1] != "") {
					output.append("USE System.Player.PlayerPage.NameLabel.setText \"" + WordSetList[0][0] + "\";\n");
					output.append("USE System.Player.PlayerPage.WordLabel.setText \"" + PlaySetList[0] + "\" \"" + WordSetList[0][1] + "\" \"" + PlaySetList[1] + "\";\n");
				}
				else if (WordSetList[1][1] != "") {
					output.append("USE System.Player.PlayerPage.NameLabel.setText \"" + WordSetList[1][0] + "\";\n");
					output.append("USE System.Player.PlayerPage.WordLabel.setText \"" + PlaySetList[0] + "\" \"" + WordSetList[1][1] + "\" \"" + PlaySetList[1] + "\";\n");
				}
				else if (WordSetList[0][1] == "" && WordSetList[1][1] == "") {
					output.append("USE System.Player.PlayerPage.NameLabel.setText \"\";\n");
					output.append("USE System.Player.PlayerPage.WordLabel.setText \"" + PlaySetList[0] + "\" \"\" \"" + PlaySetList[1] + "\";\n");
				}
			}
		}
	}
};