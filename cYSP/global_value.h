#pragma once
#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>

#define tick int
#define None
#define DoNothing

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

namespace Controller {
    namespace Title {
        struct Data {
            QString Title;
            QString SubTitle;
            QString Backdrop;
            QString Logo;
        };
    }
    namespace Backdrop {
        struct Data {
            QString Backdrop;
            QString Filter;
            int Effect;
            float Time;
        };
    }
    namespace music {
        struct Data {
            QString music;
            float volume;
        };
    }
    namespace WordSet {
        struct Data {
            float Wait;
            float Stay;
        };
    }
    namespace Speak {
        namespace Speaker {
            struct Data {
                QString Name;
                QString Word;
            };
        }
        namespace AVG {
            struct Data {
                QString Name;
                QString SubName;
                QString Filter;
                bool Scale;
                float FadeIn;
                float FadeOut;
                bool Dark;
            };
        }
    }
    namespace Free {
        enum class Alignment {
            M = 0,
            L = 1,
            R = 2,
        };
        struct Data {
            float X;
            float Y;
            Alignment Align;
            QString Word;
        };
    }
    namespace Jump {
        struct SingleData {
            QString Branch;
            QString Mark;
            QString Notice;
        };
    }
    namespace Object {
        enum class PlayerPageList {
            unknown = 0,
            AVG_L = 1,
            AVG_M = 2,
            AVG_R = 3,
            BG = 4,
            Frame = 5,
            WordLabel = 6,
            NameLabel = 7,
            FreeLabel = 8,
            NextButton = 9,
            AutoButton = 10,
            SpeedButton = 11,
            LogButton = 12,
        };
        enum class Func {
            unknown = 0,
            moveTo = 1,
            moveDelta = 2,
            moveInit = 3,
            sizeTo = 4,
            sizeDelta = 5,
            sizeInit = 6,
            Opacity = 7,
            setText = 8,
            clrText = 9,
            setImage = 10,
            clrImage = 11,
        };
        struct Data {
            PlayerPageList TargetName;
            Func FuncName;
            QStringList Parameters;
            float time = 0;
            bool wait = TRUE;
        };
    }
}