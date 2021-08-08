#pragma once
#pragma execution_character_set("utf-8")
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <QCoreApplication>
#include <QDebug>
#include "SPOLDevFunc.h"
#include "..\global_value.h"
#include "aaspcommand.h"
using namespace std;


QString setColor(QString TextInfo) {
	TextInfo = TextInfo.replace(" ", "&nbsp;");
	TextInfo = TextInfo.replace("<", "&lt;");
	//TextInfo = TextInfo.replace(">", "&gt;");
	QStringList LineList = TextInfo.split("\n");
	QString CurrentLine;
	QString CurrentLineR;
	QString CurrentLineN;
	bool inLinesJud = 0;
	for (int i = 0; i < LineList.length(); i++) {
		CurrentLineR = LineList[i];
		CurrentLine = CurrentLineR;
		CurrentLineN = "";

		if (CurrentLineR.mid(0, 3) == "###") {
			if (!inLinesJud) {
				inLinesJud = 1;
				CurrentLineR.replace("###", "<font color = #00BB5F><b>###");
			}
			else {
				CurrentLineR.replace("###", "###</b></font>");
				inLinesJud = 0;
			}
			LineList[i] = CurrentLineR;
			continue;
		}
		if (inLinesJud) { continue; }

		if (CurrentLineR[0] == "#") {
			CurrentLineR.prepend("<font color = #00BB5F><b>");
			CurrentLineR.append("</b></font>");
			LineList[i] = CurrentLineR;
			continue;
		}

		if (CurrentLineR.mid(0, 3) == "|||") {
			CurrentLineR.prepend("<font color = #909000>");
			CurrentLineR.append("</font>");
			CurrentLine = "";
			CurrentLineN = CurrentLineR;
		}
		else if (CurrentLineR.mid(0, 2) == "||") {
			CurrentLineR.prepend("<font color = #909000>");
			CurrentLineR.append("</font>");
			CurrentLine = "";
			CurrentLineN = CurrentLineR;
		}
		else if (CurrentLineR[0] == "|") {
			CurrentLineN = "<font color = #909000>|</font>";
			CurrentLine = CurrentLineR.mid(1);
		}

		if (CurrentLine.mid(0, 4) == "&lt;" && CurrentLine.mid(CurrentLine.length() - 1, 1) == ">") {

			CurrentLine.prepend("<font color = #FF1111><b>");
			CurrentLine.append("</b></font>");
		}
		else if (CurrentLine[0] == "/" && (CurrentLine.contains("SPOL") || CurrentLine.contains("GPOL"))) {
			CurrentLine.prepend("<font color = #FF0080>");
			CurrentLine.append("</font>");
		}
		else if (CurrentLine[0] == ":" && CurrentLine.count(":") == 4) {
			CurrentLine.prepend("<font color = #FF0080>");
			CurrentLine.append("</font>");
		}
		else if (CurrentLine.mid(0, 3) == ">>>" && CurrentLine.contains(":")) {
			CurrentLine.replace(">>>", "<font color = #3F48CC><b>>>>");
			CurrentLine.replace(":", ":</b></font>");
			if (CurrentLine[CurrentLine.length() - 1] == ")" && CurrentLine.contains("(")) {
				CurrentLine.replace("(", "<font color = #E07100><b>(");
				CurrentLine.replace(")", ")</font></b>");
			}
		}
		else if (CurrentLine.mid(0, 3) == ">^>" && CurrentLine.contains(":")) {
			CurrentLine.replace(">^>", "<font color = #3F48CC><b>>^>");
			CurrentLine.replace(":", ":</b></font>");
			if (CurrentLine[CurrentLine.length() - 1] == ")" && CurrentLine.contains("(")) {
				CurrentLine.replace("(", "<font color = #E07100><b>(");
				CurrentLine.replace(")", ")</font></b>");
			}
		}
		else if (CurrentLine.mid(0, 3) == "-->" && CurrentLine.contains(":")) {
			CurrentLine.replace("-->", "<font color = #909000><b>-->");
			CurrentLine.replace(":", ":</b></font>");
		}
		else if (CurrentLine[0] == "[" && CurrentLine[CurrentLine.length() - 1] == "]") {
			CurrentLine.replace("[", "<font color = #FF00FF><b>[");
			CurrentLine.replace("]", "]</b></font>");
		}
		else if (CurrentLine[0] == "{" && CurrentLine[CurrentLine.length() - 1] == "}") {
			CurrentLine.replace("{", "<font color = #FF0080><b>{");
			CurrentLine.replace("}", "}</b></font>");
		}

		LineList[i] = CurrentLineN + CurrentLine;
	}
	//LineList.append("<A href='./story'>Try</a>");
	return LineList.join("<br>");
}