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

//�źű�
class InterpreterSignals :public QObject {
	Q_OBJECT
	signals:
	//���ͽ�����������������
	void can_update_chara(QList<QStringList>, int, bool);
	//���ͽ����������ı�
	void update_chara_num(QStringList, QString, int, QStringList);
	//���ͱ���������ͼ��
	void can_update_bg(QStringList);
	//���ͱ�����������ֵ����Ч
	void update_num_bg(float, QStringList);
	//����BGM
	void can_update_bgm(QString, int);
	//������Ч
	void can_update_sound(QString, int);
	//���س�ʼ��Ļ
	void can_hide_hello(int);
	//�ָ���ʼ��Ļ
	void can_reprint_hello(int);
	//չʾ����ҳ��
	void can_show_title(QStringList);
	//չʾҳ��ڶ�����
	void can_hide_title(void);
	//չʾҳ��������֡�׼������ҳ��
	void can_prepare_play(void);
	//���ʹ�С��֧������ͨ�õķ�֧����
	void need_to_choose(QStringList);
	//�ı����½�����ҳ����
	void show_next(void);
	//��֪UI�̣߳��������Ѿ�������
	void inrunning(void);
	//��֪UI�̣߳�����������ֹͣ
	void willstop(void);
	//���������ı�����������
	void can_update_freedom(QStringList, QStringList);
	//���������ı�����
	void update_num_freedom(QString);
	//���������ı�������
	void can_clear_freedom(int);
	//������ת�б�
	void clr_line_list(void);
	//������ת��Ϣ
	void save_line_list(QStringList);
	//�ϳ���ת�б�
	void set_scroll_info(void);
	//��֪UIˢ�µ�ǰ��
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
