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

/*可选调试信息输出函数sDebug
DebugInfo
O======O
传入字符串，程序仅在内测模式或强制调试模式下输出该调试信息*/
void sDebug(QString DebugInfo);

/*随机整数函数randint
min,max
O======O
传入左右端点值，随机获取一个区间内的整数
>>>Ayano Aishi完成此函数*/
int randint(int min, int max);

/*上限函数limitmax
num,max
O======O
传入数值num，若小于up则返回num，若大于up则返回up*/
int limitmax(int num, int max);

/*下限函数limitmin
num,min
O======O
传入数值num，若大于min则返回num，若小于min则返回min*/
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