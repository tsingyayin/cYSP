#pragma once
#pragma execution_character_set("utf-8")
#include <QDebug>
#include <QCoreApplication>
#include <QSysInfo>
#include <QDir>
#include <QApplication>
#include <QtWidgets>
#include "../langcontrol.h"
#include "checkupdate.h"
#include "../loadsettings.h"
#define elif else if
#define Debug qDebug().noquote()

using namespace std;

/*�������¸��¼�麯��checkupdate
argc,argv
O======O
˳�ְ�main�������������������У���QApplication��ʼ���á�
�ú������������»�ȡ����״̬*/
void checkupdate(int argc, char* argv[]);

/*�����������Ը�������langinput
�޲���
O======O
�ú������𹹳��������¼����������ƵĽ���
�Լ���langset��������ֵ�ж��Ƿ�ɹ���������*/
void langinput(void);

/*�������³�����Ϣչʾ����about
�޲���
O======O
�����������һЩ������Ϣ
��������˷���UI�Ĺ�����Ϣ������ת��ͷ������Щ����ֽ���֡�ô��*/
void about(void);

/*������������һ������aasphelp
�޲���
O======O
���������������һ��
���ǵø��������⡱*/
void aasphelp(void);

/*�ļ�������DeleteCache
num
O======O
������Python�汾��DeleteEmptyMap��DeleteAllCache��������
�ó�ʼֵ0 �� 1���������������ܡ�*/
void DeleteCache(int num);

/*�ļ�ϵͳ��ȫ����ensuredirs
num
O======O
���num���дһ��ֵ����û��ɶ�ã���֪��Ϊɶ����д�Ĳ�����void
�ú������ú���ȱʧ��Ŀ¼
*/
void ensuredirs(int num); 

/*�ļ��д򿪺���OpenFolder
num
O======O
��ֵ1�򿪻����ļ��У���ֵ2����Դ�ļ���
��ֵ3�򿪹ٷ������ļ��У���ֵ4���û������ļ���
������cmd.exe��*/
void OpenFolder(int num);

/*��ҳ����ʵ�ֿ��hServiceFramework
���캯���޲���
O======O
�ṩ����ʵ����ҳ�Ĺ��ܵĺ���*/
class hServiceFramework :public QObject {
	Q_OBJECT
signals:
	/*��Ϣ���ͺ���Anyinfo
	int , QString
	O======O
	��һ�����������ı���ʾ��ɫ��Լ��0Ϊ��ɫ��1Ϊ��ɫ��2Ϊ��ɫ
	�ڶ�������Ϊ�ı�����*/
	void Anyinfo(int, QString);

public:
	hServiceFramework(void) {
	}

	//UI�¸��¼�麯��
	QStringList ui_CheckUpdate(void) {
		uCheckUpdate Check;
		QList<QStringList> VerList = Check.getUpdate();
		QList<QStringList> VerNew;
		if (!VerList.isEmpty()) {
			if (VerList[0][0] == "UNKNOWNNETERROR") {
				qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Net_Error");
			}
			else if (VerList[0][0] == "UNKNOWNBLOG") {
				qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Ver_Error");
			}
		}
		for (int i = 0; i < VerList.length(); i++) {
			if (Program_Settings("Update_Channel") == "Pre" && VerList[i][2] == "Pre") {
				qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Pre");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
			else if (Program_Settings("Update_Channel") == "Pub" && VerList[i][2] == "Pub") {
				qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Pub");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
			else if (Program_Settings("Update_Channel") == "Auto") {
				if (VerList[i][2] == "Pre" && Program_Info("Sub").contains("Pre")) {
					qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Pre");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
				else if (VerList[i][2] == "Pub" && Program_Info("Sub").contains("Pub")) {
					qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Pub");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
				else if (VerList[i][2] == "Branch" && (!Program_Info("Sub").contains("Pre") || !Program_Info("Sub").contains("Pub"))) {
					qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Branch");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
			}
			else {
				if (VerList[i][2] == "Pub") {
					qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Pub");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
			}
		}
		if (VerNew.isEmpty()) {
			qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Ver_Error");
			emit Anyinfo(2, msg("Check_Update_Info_Ver_Error"));
		}
		else if (VerNew[0][2].toFloat() > Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Latest").arg(VerNew[0][0]).arg(VerNew[0][1]);
			return {VerNew[0][1],VerNew[0][3]};
		}
		else if (VerNew[0][2].toFloat() == Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_New");
			emit Anyinfo(1, msg("Check_Update_Info_New"));
		}
		else if (VerNew[0][2].toFloat() < Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo��" + msg("Check_Update_Info_Insider");
			emit Anyinfo(1, msg("Check_Update_Info_Insider"));
		}
		return {"NODIALOG","NODIALOG"};
	}

	//SPOLת������������������ʱ���ã�
	void ui_Tospol(QString fileNameIpt) {
		//bool func = HLtoSPOL(fileNameIpt);
		/*
		if (func) {
			emit Anyinfo(1, msg("Ui_To_Spol_End"));
		}else {
			emit Anyinfo(2, msg("Ui_To_Spol_End_Error"));
		}*/
	}

	//��ͼ��������
	void ui_DeleteEmptyMap(void) {
		DeleteCache(0);
		emit Anyinfo(1, msg("Function_Filecheck_Run_End"));
	}

	//����ͼ��ȫ�庯��
	void ui_DeleteAllCache(void) {
		DeleteCache(1);
		emit Anyinfo(1, msg("Function_Filecheck_Cache_Clean"));
	}

	//UI���������Ժ�������ע��filename���ļ������ԣ�������·��
	void ui_langset(QString filename) {
		langset(filename);
		emit Anyinfo(1, msg("Function_Language_Loading_Success"));
	}

	/*�ļ��д򿪺���
	num
	O======O
	��ֵ1�򿪻����ļ��У���ֵ2����Դ�ļ���
	��ֵ3�򿪹ٷ������ļ��У���ֵ4���û������ļ���
	������cmd.exe��*/
	void ui_OpenFolder(int num) {
		OpenFolder(num);
	}
};
