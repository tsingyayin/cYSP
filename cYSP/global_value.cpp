#include "global_value.h"
#include "loadsettings.h"
#include <QCoreApplication>
#include <QDebug>

QString PROINFO::Main = "0.9.2";
QString PROINFO::Channel = "Pre";
QString PROINFO::Sub = "2";
QString PROINFO::Build = "140.10100";
QString PROINFO::SPOL = "0.9.2";
QString PROINFO::Kernal = "K9U3";
QString PROINFO::Day = "20211111";
QString PROINFO::Dev = "青雅音、Ayano_Aishi、v0v_tempest";
QString PROINFO::urlGithub = "https://github.com/tsingyayin/YSP-Yayin_Story_Player";
QString PROINFO::urlAFD = "https://afdian.net/@ysp_Dev?tab=home";
QString PROINFO::Total = "Ver" + PROINFO::Main + "_" +
PROINFO::Channel + PROINFO::Sub + "(Build" +
PROINFO::Build + ")_SPOL" + PROINFO::SPOL + ";" + PROINFO::Kernal;

QString PROPATH::Program = "";
QString PROPATH::Users = "";

bool ResourceHost::isLocal = FALSE;
QString ResourceHost::Host = "";

void setCurrentPath(QString CurrentPath, QString User_Path, bool FromLauncher) {
#if DEPLOY == 1
	if (!FromLauncher) {
		PROPATH::Program = CurrentPath;
		PROPATH::Users = CurrentPath.replace("\\", "/").section("/", 0, -2) + "/Users_Data";
	}
	else {
		PROPATH::Program = CurrentPath;
		PROPATH::Users = User_Path;
	}
#elif DEPLOY == 2
	PROPATH::Program = CurrentPath;
	PROPATH::Users = "/sdcard/cysp/Users_Data";
#endif
};

void sDebug(QString DebugInfo) {
	if (PROINFO::Sub.contains("Pre") || (Program_Settings("Force_Debugging_Info") == "True")) {
		qDebug().noquote() << DebugInfo;
	}
}

int randint(int min, int max)
{
	return qrand() % (max - min + 1) + min;
}

int limitmax(int num, int max) {
	if (num < max) {
		return num;
	}
	else {
		return max;
	}
}

int limitmin(int num, int min) {
	if (num > min) {
		return num;
	}
	else {
		return min;
	}
}