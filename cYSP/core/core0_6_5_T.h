#pragma once

#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <algorithm>

using namespace std;

class mQThread :public QThread {
public:
	QMutex* mutex;
	QWaitCondition* cond;
	void pause(void) {
		cond->wait(mutex);
	}
	void wake(void) {
		cond->wakeAll();
	}
};

//信号表
class InterpreterSignals :public QObject {
	Q_OBJECT
	signals:
	//递送讲述控制器人物立绘
	void can_update_chara(QList<QStringList>, int, bool);
	//递送讲述控制器文本
	void update_chara_num(QStringList, QString, int, QStringList);
	//递送背景控制器图像
	void can_update_bg(QStringList);
	//递送背景控制器数值和特效
	void update_num_bg(float, QStringList);
	//递送BGM
	void can_update_bgm(QString, int);
	//递送音效
	void can_update_sound(QString, int);
	//隐藏初始屏幕
	void can_hide_hello(int);
	//恢复初始屏幕
	void can_reprint_hello(int);
	//展示标题页面
	void can_show_title(QStringList);
	//展示页面第二部分
	void can_hide_title(void);
	//展示页面第三部分、准备播放页面
	void can_prepare_play(void);
	//递送大小分支控制器通用的分支设置
	void need_to_choose(QStringList);
	//文本更新结束后翻页函数
	void show_next(void);
	//告知UI线程，解释器已经在运行
	void inrunning(void);
	//告知UI线程，解释器即将停止
	void willstop(void);
	//递送自由文本控制器设置
	void can_update_freedom(QStringList, QStringList);
	//递送自由文本内容
	void update_num_freedom(QString);
	//清理自由文本控制器
	void can_clear_freedom(int);
	//清理跳转列表
	void clr_line_list(void);
	//保存跳转信息
	void save_line_list(QStringList);
	//合成跳转列表
	void set_scroll_info(void);
	//告知UI刷新当前行
	void now_which_line(int);
public:
	InterpreterSignals() {
		qRegisterMetaType<QList<QStringList>>("QList<QStringList>");
	}
};

enum InterpreterMode {
	presource = 0,
	run = 1,
	debug = 2,
};

class ReciveUserControl :public QObject
{
	Q_OBJECT
public:
	ReciveUserControl(void) {}
public slots:
	void LineNumNow(int Num); 
	void SpeedNow(float Num);
	void ChooseWhichBranch(QString Branchname);
	void ExitNow(void);
};



void Interpreter(QString storyFilename, InterpreterSignals *signalsName, mQThread* parent);

QStringList SingleLine(int LineNum, QString Line, InterpreterMode whichMode, InterpreterSignals* signalsName, mQThread* parent = Q_NULLPTR);
