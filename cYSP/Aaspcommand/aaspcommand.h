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

void checkupdate(int argc, char* argv[]);

void langinput(void);

void about(void);

void aasphelp(void);

void DeleteCache(int num);

void ensuredirs(int num); 

void OpenFolder(int num);


class hServiceFramework :public QObject {
	Q_OBJECT
signals:
	void Anyinfo(int, QString);
public:
	hServiceFramework(void) {
	}
	void ui_aasphelp(void) {
		aasphelp();
	}
	QStringList ui_CheckUpdate(void) {
		uCheckUpdate Check;
		QList<QStringList> VerList = Check.getUpdate();
		QList<QStringList> VerNew;
		if (VerList[0][0] == "UNKNOWNNETERROR") {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Net_Error");
		}
		else if (VerList[0][0] == "UNKNOWNBLOG") {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Ver_Error");
		}
		
		for (int i = 0; i < VerList.length(); i++) {
			if (Program_Settings("Update_Channel") == "Pre" && VerList[i][2] == "Pre") {
				qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Pre");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
			else if (Program_Settings("Update_Channel") == "Pub" && VerList[i][2] == "Pub") {
				qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Pub");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
			else if (Program_Settings("Update_Channel") == "Auto") {
				if (VerList[i][2] == "Pre" && Program_Info("Sub").contains("Pre")) {
					qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Pre");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
				else if (VerList[i][2] == "Pub" && Program_Info("Sub").contains("Pub")) {
					qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Pub");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
				else if (VerList[i][2] == "Branch" && (!Program_Info("Sub").contains("Pre") || !Program_Info("Sub").contains("Pub"))) {
					qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Branch");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
			}
			else {
				if (VerList[i][2] == "Pub") {
					qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Pub");
					VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
					break;
				}
			}
		}
		qDebug().noquote() << VerNew;
		if (VerNew.isEmpty()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Ver_Error");
			emit Anyinfo(2, msg("Check_Update_Info_Ver_Error"));
		}
		else if (VerNew[0][2].toFloat() > Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Latest").arg(VerNew[0][0]).arg(VerNew[0][1]);
			return {VerNew[0][1],VerNew[0][3]};
		}
		else if (VerNew[0][2].toFloat() == Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_New");
			emit Anyinfo(1, msg("Check_Update_Info_New"));
		}
		else if (VerNew[0][2].toFloat() < Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Insider");
			emit Anyinfo(1, msg("Check_Update_Info_Insider"));
		}
		return {"NODIALOG","NODIALOG"};
	}
	void ui_Tospol(QString fileNameIpt) {
		//bool func = HLtoSPOL(fileNameIpt);
		/*
		if (func) {
			emit Anyinfo(1, msg("Ui_To_Spol_End"));
		}else {
			emit Anyinfo(2, msg("Ui_To_Spol_End_Error"));
		}*/
	}
	void ui_DeleteEmptyMap(void) {
		DeleteCache(0);
		emit Anyinfo(1, msg("File_Searching_Wrong_End"));
	}
	void ui_DeleteAllCache(void) {
		DeleteCache(1);
		emit Anyinfo(1, msg("File_Cache_Deleted"));
	}
	void ui_langset(QString filename) {
		langset(filename);
		emit Anyinfo(1, msg("Lang_Set_Success").arg(filename));
	}
	void ui_OpenFolder(int num) {
		OpenFolder(num);
	}
};
