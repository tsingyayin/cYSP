#pragma once

#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <algorithm>

using namespace std;

class InterpreterSignals :public QObject {
	Q_OBJECT
	signals:
	void can_update_chara(QList<QStringList>, int, int);
	void update_chara_num(QStringList, QString, int, QStringList);

	void can_update_bg(QStringList);
	void update_num_bg(float, QStringList);

	void can_update_bgm(QString, int);
	void can_update_sound(QString, int);

	void can_hide_hello(int);
	void can_reprint_hello(int);

	void can_show_title(QStringList);
	void can_hide_title(void);
	void can_prepare_play(void);

	void need_to_choose(QStringList);

	void show_next(void);
	void inrunning(void);
	void willstop(void);

	void can_update_freedom(QStringList, QStringList);
	void update_num_freedom(QString);
	void can_clear_freedom(int);

	void send_file_info(void);

	void clr_line_list(void);
	void save_line_list(QStringList);
	void set_scroll_info(void);

	void now_which_line(int);
public:
	InterpreterSignals() {
		
	}
};

enum InterpreterMode {
	presource = 0,
	spawn = 1,
	line = 2,
};

class ReciveUserControl :public QObject
{
	Q_OBJECT
public:
	ReciveUserControl(void) {}
public slots:
	void LineNumNow(int Num); 
	void SpeedNow(float Num);
};

void Interpreter(QString storyFilename, InterpreterMode whichMode,InterpreterSignals *signalsName);

