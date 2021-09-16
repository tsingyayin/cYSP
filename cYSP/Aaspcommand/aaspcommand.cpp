#include "aaspcommand.h"
#include "../UIFolder/TopWindow.h"
#include "../global_value.h"
#include "checkupdate.h"
#include <QDebug>
#include <QCoreApplication>
#include <QSysInfo>
#include <QDir>
#include <QFile>
#include <QApplication>
#include <QtWidgets>
#pragma execution_character_set("utf-8")

using namespace std;

void checkupdate(int argc, char* argv[]) {
	QApplication app(argc, argv);
	uCheckUpdate Check;
	QList<QStringList> VerList = Check.getUpdate();
	QList<QStringList> VerNew;
	app.exit();
	if (VerList[0][0] == "UNKNOWNNETERROR") {
		qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Net_Error");
	}
	else if (VerList[0][0] == "UNKNOWNBLOG"){
		qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Ver_Error");
	}
	for (int i = 0; i < VerList.length(); i++) {
		if (Program_Settings("Update_Channel") == "Pre" && VerList[i][2]=="Pre") {
			qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Pre");
			VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
			break;
		}
		else if (Program_Settings("Update_Channel") == "Pub" && VerList[i][2] == "Pub") {
			qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Pub");
			VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
			break;	
		}
		else if (Program_Settings("Update_Channel") == "Auto") {
			if (VerList[i][2] == "Pre" && Program_Info("Sub").contains("Pre")) {
				qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Pre");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
			else if (VerList[i][2] == "Pub" && Program_Info("Sub").contains("Pub")) {
				qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Pub");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
			else if (VerList[i][2] == "Branch" && (!Program_Info("Sub").contains("Pre") || !Program_Info("Sub").contains("Pub"))) {
				qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Branch");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
		}
		else {
			if (VerList[i][2] == "Pub") {
				qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Pub");
				VerNew.append({ VerList[i][0], VerList[i][1], VerList[i][3] ,VerList[i][4] });
				break;
			}
		}
	}

	if (VerNew.isEmpty()) {
		qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Ver_Error");
	}else if (VerNew[0][2].toFloat() > Program_Info("Build").toFloat()) {
		qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Latest").arg(VerNew[0][0]).arg(VerNew[0][1]);
	}else if (VerNew[0][2].toFloat() == Program_Info("Build").toFloat()) {
		qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_New");
	}else if (VerNew[0][2].toFloat() < Program_Info("Build").toFloat()) {
		qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Insider");
	}
}

void langinput(void) {
	string Usript;
	qDebug().noquote() << "sysinfo→" + msg("Lang_Input_Msg");
	while (TRUE) {
		cout << "Userinput\\lang\u2192";
		cin >> Usript;
		if (Usript ==  "") { continue; }
		if (Usript == "exit") { return; }
		else { 
			int a=langset(QString::fromStdString(Usript)); 
			if (a) {
				qDebug().noquote() << "sysinfo→" + msg("Lang_Set_Success").arg(QString::fromStdString(Usript));
			}
		}
	}
}

void about(void) {
	qDebug().noquote() << msg("About_Info_Main_Ver") + Program_Info("Main");
	qDebug().noquote() << msg("About_Info_Sub_Ver") + Program_Info("Sub");
	qDebug().noquote() << msg("About_Info_Build_Ver") + Program_Info("Build");
	qDebug().noquote() << msg("About_Info_Spol_Ver") + Program_Info("SPOL");
	qDebug().noquote() << msg("About_Info_Spol_Env_Ver") + Program_Info("SPEnv");
	qDebug().noquote() << msg("About_Info_Developers") + "青雅音 Tsing Yayin";
	qDebug().noquote() << msg("About_Info_Environment") + "Visual Studio 2019";
	qDebug().noquote() << msg("About_Info_Support") + "亿绪联合协会 UYXA";
	qDebug().noquote() << msg("About_Info_Help").arg(urlGithub);
	qDebug().noquote() << msg("About_Info_Donate").arg(urlAFD);
}

void aasphelp(void) {
	qDebug().noquote()<<"about\t" + msg("Help_In_Main_Page_about_");
	qDebug().noquote()<<"clear\t" + msg("Help_In_Main_Page_clear");
	qDebug().noquote()<<"clrall\t" + msg("Help_In_Main_Page_clearall");
	qDebug().noquote()<<"exit\t" + msg("Help_In_Main_Page_exit");
	qDebug().noquote()<<"help\t" + msg("Help_In_Main_Page_help");
	qDebug().noquote()<<"lang\t" + msg("Help_In_Main_Page_lang");
	qDebug().noquote()<<"tospol\t" + msg("Help_In_Main_Page_tospol");
	qDebug().noquote()<<"ui\t" + msg("Help_In_Main_Page_ui");
	qDebug().noquote()<<"window\t" + msg("Help_In_Main_Page_window");
}

void DeleteCache(int num) {
	if (num == 0) {
		qDebug().noquote() << "sysinfo→" + msg("File_Searching_Wrong");
	}else if (num == 1) {
		qDebug().noquote() << "sysinfo→" + msg("File_Delete_Cache");
	}
	QDir visualCacheCharaDir("./Visual/cache/Chara/");
	visualCacheCharaDir.setFilter(QDir::Files | QDir::NoSymLinks); 
	QDir visualCacheBGPDir("./Visual/cache/BGP/");
	visualCacheBGPDir.setFilter(QDir::Files | QDir::NoSymLinks);
	for (int i = 0; i < visualCacheCharaDir.count(); i++) {
		QFile cacheFile("./Visual/cache/Chara/" + visualCacheCharaDir.entryList()[i]);
		if (cacheFile.size() == 0 && num==0) { 
			cacheFile.remove(); 
			qDebug().noquote() << msg("File_Info_Deleted") << visualCacheCharaDir.entryList()[i];
		}else if(num==1){
			cacheFile.remove();
		}
	}
	for (int i = 0; i < visualCacheBGPDir.count(); i++) {
		QFile cacheFile("./Visual/cache/BGP/" + visualCacheBGPDir.entryList()[i]);
		if (cacheFile.size() == 0 && num == 0) {
			cacheFile.remove();
			qDebug().noquote() << msg("File_Info_Deleted") << visualCacheBGPDir.entryList()[i];
		}else if (num == 1) {
			cacheFile.remove();
		}
	}
	qDebug().noquote() << "sysinfo→" + msg("File_Searching_Wrong_End");
}

void ensuredirs(int num) {
	qDebug().noquote() << "sysinfo→Checking the files in the directory";
	QStringList dirlst;
	dirlst << "./CrashReport" << "./Visual/cache/BGP" << "./Visual/cache/Chara" << "./arknights/story";
	int count = 0;
	QDir singleDir;
	for (int i = 0; i < dirlst.length(); i++) {
		if (!singleDir.exists(dirlst[i])) {
			qDebug().noquote() << "sysinfo→Directory '" << dirlst[i] << "'missed.Now rebuilding...";
			singleDir.mkpath(dirlst[i]);
			count += 1;
		}
	}
	if (count == dirlst.length()) {
		QString user_home = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
		qDebug().noquote() << user_home;
	}
	qDebug().noquote() << "sysinfo→Checked";
}

void OpenFolder(int num) {
	QString Path = "";
	if (num == 1) {
		Path = ".\\Visual\\cache";
	}elif(num == 2) {
		Path = ".\\Visual\\source";
	}elif(num == 3) {
		Path = ".\\arknights\\story";
	}elif(num == 4) {
		Path = ".\\story";
	}
	system(("start " + Path).toStdString().data());
}