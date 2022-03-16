#include "global_value.h"
#include "loadsettings.h"
#include <QCoreApplication>
#include <QDebug>

QString PROINFO::Main = "0.10.0";
QString PROINFO::Channel = "Pre";
QString PROINFO::Sub = "1";
QString PROINFO::Build = "145.0";
QString PROINFO::SPOL = "0.9.0";
QString PROINFO::Kernal = "K10UT0";
QString PROINFO::Day = "20210310";
QString PROINFO::Dev = "青雅音、Ayano_Aishi、v0v_tempest";
QString PROINFO::urlGithub = "https://github.com/tsingyayin/YSP-Yayin_Story_Player";
QString PROINFO::urlAFD = "https://afdian.net/@ysp_Dev?tab=home";
QString PROINFO::Total = "Ver" + PROINFO::Main + "_" +
PROINFO::Channel + PROINFO::Sub + "(Build" +
PROINFO::Build + ")_SPOL" + PROINFO::SPOL + ";" + PROINFO::Kernal;

QString PROPATH::Program = "";
QString PROPATH::Users = "";

float PlayerBaseInfo::SpeedFloat = 1.0;

QString GlobalValue::CurrentProject = "";
QString GlobalValue::NewWhichProject = "";
QString GlobalValue::CurrentVideo = "";
int GlobalValue::CurrentDuration = 1;
int GlobalValue::CurrentFrame = 1;
int GlobalValue::CurrentPixmapNum = 0;
int GlobalValue::CurrentSelectFrame = 1;
int GlobalValue::loadEditFrame = -1;
QList<float> GlobalValue::RectangleGeo = { 0,0,0,0 };
QList<float> GlobalValue::RoundGeo = { 0,0,0,0 };
QList<float> GlobalValue::RecGeo = { 0,0,0,0 };
QList<float> GlobalValue::RdGeo = { 0,0,0,0 };
QList<float> GlobalValue::ColorHSLMax = { 0,0,0 };
QList<float> GlobalValue::ColorHSLMin = { 0,0,0 };
QList<float> GlobalValue::ColorHSLAvg = { 0,0,0 };
QList<QColor> GlobalValue::ColorList = {};
double GlobalValue::MpP = 0;
int GlobalValue::CurrentAliveThread = 0;
int GlobalValue::MaxAliveThread = 4;
QMutex GlobalValue::ThreadMutex;
double GlobalValue::CurrentVideoRate = 0;
QList<int> GlobalValue::CurrentRec = { 0,0 };
QMutex GlobalValue::AnaListMutex;
QList<QList<double>> GlobalValue::AnaList;

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