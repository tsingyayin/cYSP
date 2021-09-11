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
float SpeedFloat;
void ReciveUserControl::LineNumNow(int Num) {
	LineNum = Num;
	justJump = TRUE;
}

void ReciveUserControl::SpeedNow(float Num) {
	SpeedFloat = Num;

}

void Interpreter(QString storyFilename, InterpreterMode whichMode, InterpreterSignals *signalsName) {
	qDebug().noquote() << "-->Attempt to execute the resource completion module<--- ";
	sDebug("成功启动核心");
};

QString SingleLine(QString Line, InterpreterMode whichMode, InterpreterSignals* signalsName) {
	return "TEST";
};

class cTransform :public QThread
{
	Q_OBJECT
public:
	QString gFilename;
	QList<Filter> gFilterList;
	int gFilterCount;
	cTransform(QString filename, QList<Filter> filterList) {
		gFilename = filename;
		gFilterList = filterList;
		gFilterCount = gFilterList.length();
	}
	void run(void) {
	}
};
