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
	int ui_CheckUpdate(void) {
		uCheckUpdate Check;
		QList<QStringList> VerList = Check.getUpdate();
		QStringList VerNew;
		if (VerList[0][0] == "UNKNOWNNETERROR") {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Net_Error");
		}
		else if (VerList[0][0] == "UNKNOWNBLOG") {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Ver_Error");
		}
		for (int i = 0; i < VerList.length(); i++) {
			if (VerList[i][2] == "Pre" && Program_Info("Sub").contains("Pre")) {
				qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Pre");
				VerNew.append((VerList[i][0], VerList[i][1]));
				break;
			}
			else if (VerList[i][2] == "Pub" && Program_Info("Sub").contains("Pub")) {
				qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Pub");
				VerNew.append((VerList[i][0], VerList[i][1]));
				break;
			}
			else if (VerList[i][2] == "Branch" && (!Program_Info("Sub").contains("Pre") || !Program_Info("Sub").contains("Pub"))) {
				qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Branch");
				VerNew.append((VerList[i][0], VerList[i][1]));
				break;
			}
		}
		if (VerNew.isEmpty()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Ver_Error");
			emit Anyinfo(2, msg("Check_Update_Info_Ver_Error"));
		}
		else if (VerNew[0].toInt() > Program_Info("Day").toInt()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Latest").arg(VerNew[0]).arg(VerNew[1]);
			return 1;
		}
		else if (VerNew[0].toInt() == Program_Info("Day").toInt()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_New");
			emit Anyinfo(1, msg("Check_Update_Info_New"));
		}
		else if (VerNew[0].toInt() < Program_Info("Day").toInt()) {
			qDebug().noquote() << "sysinfo¡ú" + msg("Check_Update_Info_Insider");
			emit Anyinfo(1, msg("Check_Update_Info_Insider"));
		}
		return 0;
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
