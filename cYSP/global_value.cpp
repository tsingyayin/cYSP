#include "global_value.h"
#include "loadsettings.h"
#include <QCoreApplication>
#include <QDebug>

QString urlGithub = "https://github.com/tsingyayin/YSP-Yayin_Story_Player";
QString urlAFD = "https://afdian.net/@ysp_Dev?tab=home";
QString Edition("Ver0.8.0_Pre1_PT2(Build110.0010)_SPOL0.6.0;C++_Qt");
QString ReleaseDay("20210801");
QString InsiderMainVer = Edition.mid(Edition.indexOf("Ver") + 3, Edition.indexOf("_P") - Edition.indexOf("Ver") - 3);
QString InsiderSubVer = Edition.mid(Edition.indexOf("_P") + 1, Edition.indexOf("(Build") - Edition.indexOf("_P") -1);
QString InsiderBuildVer = Edition.mid(Edition.indexOf("(Build") + 6, Edition.indexOf(")") - Edition.indexOf("(Build") - 6);
QString InsiderSPOLVer = Edition.mid(Edition.indexOf("SPOL") + 4, Edition.indexOf(";C++_Qt") - Edition.indexOf("SPOL") - 4);
QString InsiderSPOLEnvVer = "C++_Qt";

QString Program_Info(QString SearchParameter) {
	if (SearchParameter == "Edition") {
		return Edition;
	}
	else if (SearchParameter == "Main") {
		return InsiderMainVer;
	}
	else if (SearchParameter == "Sub") {
		return InsiderSubVer;
	}
	else if (SearchParameter == "Build") {
		return InsiderBuildVer;
	}
	else if (SearchParameter == "SPOL") {
		return InsiderSPOLVer;
	}
	else if (SearchParameter == "SPEnv") {
		return InsiderSPOLEnvVer;
	}
	else if (SearchParameter == "Day") {
		return ReleaseDay;
	}
	else {
		return "UNKNOWN_PROGRAME_INFO";
	}
}

void sDebug(QString DebugInfo) {
	if (Program_Info("Sub").contains("Pre") || (Program_Settings("Force_Debugging_Info")=="True")) {
		qDebug().noquote() << DebugInfo;
	}
}

int randint(int min, int max)
{
	srand((unsigned)time(NULL));
	return rand() % (max - min + 1) + min;
}