#pragma once
#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>

/*程序信息函数Program_Info
SearchParameter
O======O
Edition查询全版本号、Main查询主版本号
Sub查询更新号、Build查询构建号
SPOL查询SPOL版本、SPEnv查询解释器环境类型
Day查询发行日期、Developer查询开发者
O======O
默认值“UNKNOWN_PROGRAM_INFO”*/
QString Program_Info(QString SearchParameter = "None");

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