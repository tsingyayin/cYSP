#pragma once
#include <QApplication>
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>

using namespace std;

/*语言设置函数langset
langname
O======O
第一个参数为语言名称。
返回是否成功更换语言。1为成功，0为失败
“我大概的确应该把int改成bool”*/
int langset(QString langname);

/*翻译返回函数msg
Usript
O======O
传入内部名称
返回翻译文本*/
QString msg(QString Usript);
