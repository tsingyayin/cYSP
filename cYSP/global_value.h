#pragma once
#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QtWidgets>
#include <QCoreApplication>
#include <QDebug>

/*������Ϣ����Program_Info
SearchParameter
O======O
Edition��ѯȫ�汾�š�Main��ѯ���汾��
Sub��ѯ���ºš�Build��ѯ������
SPOL��ѯSPOL�汾��SPEnv��ѯ��������������
Day��ѯ�������ڡ�Developer��ѯ������
O======O
Ĭ��ֵ��UNKNOWN_PROGRAM_INFO��*/
QString Program_Info(QString SearchParameter = "None");

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