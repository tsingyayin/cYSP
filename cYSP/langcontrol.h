#pragma once
#include <QApplication>
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>

using namespace std;

/*�������ú���langset
langname
O======O
��һ������Ϊ�������ơ�
�����Ƿ�ɹ��������ԡ�1Ϊ�ɹ���0Ϊʧ��
���Ҵ�ŵ�ȷӦ�ð�int�ĳ�bool��*/
int langset(QString langname);

/*���뷵�غ���msg
Usript
O======O
�����ڲ�����
���ط����ı�*/
QString msg(QString Usript);
