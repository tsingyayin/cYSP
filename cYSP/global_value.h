#pragma once
#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>

void setCurrentPath(QString CurrentPath, QString User_Path = "", bool FromLauncher = FALSE);

class PROINFO
{
public:
    static QString Main;
    static QString Channel;
    static QString Sub;
    static QString Build;
    static QString SPOL;
    static QString Kernal;
    static QString Day;
    static QString Dev;
    static QString urlAFD;
    static QString urlGithub;
    static QString Total;
};

class PROPATH
{
public:
    static QString Program;
    static QString Users;
};

/*��ѡ������Ϣ�������sDebug
DebugInfo
O======O
�����ַ�������������ڲ�ģʽ��ǿ�Ƶ���ģʽ������õ�����Ϣ*/
void sDebug(QString DebugInfo);

/*�����������randint
min,max
O======O
�������Ҷ˵�ֵ�������ȡһ�������ڵ�����
>>>Ayano Aishi��ɴ˺���*/
int randint(int min, int max);

/*���޺���limitmax
num,max
O======O
������ֵnum����С��up�򷵻�num��������up�򷵻�up*/
int limitmax(int num, int max);

/*���޺���limitmin
num,min
O======O
������ֵnum��������min�򷵻�num����С��min�򷵻�min*/
int limitmin(int num, int min);

enum class EIFL {
    URE = 0,
    SSE = 1,
    PRE = 2,
    GFE = 3,
    SRI = 4,
    PRI = 5,
    GRI = 6,
    NWI = 7,
};