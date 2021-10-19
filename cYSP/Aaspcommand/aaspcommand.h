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

/*命令行下更新检查函数checkupdate
argc,argv
O======O
顺手把main的两个参数传进来就行，给QApplication初始化用。
该函数在命令行下获取更新状态*/
void checkupdate(int argc, char* argv[]);

/*命令行下语言更换函数langinput
无参数
O======O
该函数负责构成命令行下键入语言名称的交互
以及依langset函数返回值判断是否成功设置语言*/
void langinput(void);

/*命令行下程序信息展示函数about
无参数
O======O
对命令行输出一些程序信息
“真的有人放着UI的关于信息不看，转过头来看这些‘黑纸白字’么”*/
void about(void);

/*命令行下命令一览函数aasphelp
无参数
O======O
对命令行输出命令一览
“记得更新这玩意”*/
void aasphelp(void);

/*文件清理函数DeleteCache
num
O======O
整合了Python版本的DeleteEmptyMap和DeleteAllCache两个函数
用初始值0 和 1区分上述两个功能。*/
void DeleteCache(int num);

/*文件系统保全函数ensuredirs
num
O======O
这个num随便写一个值，并没有啥用，鬼知道为啥当初写的并不是void
该函数调用后补齐缺失的目录
*/
void ensuredirs(int num); 

/*文件夹打开函数OpenFolder
num
O======O
数值1打开缓存文件夹，数值2打开资源文件夹
数值3打开官方剧情文件夹，数值4打开用户剧情文件夹
“赞美cmd.exe”*/
void OpenFolder(int num);

/*主页功能实现框架hServiceFramework
构造函数无参数
O======O
提供多种实现主页的功能的函数*/
class hServiceFramework :public QObject {
	Q_OBJECT
signals:
	/*信息递送函数Anyinfo
	int , QString
	O======O
	第一个参数代表文本显示颜色，约定0为黑色，1为蓝色，2为红色
	第二个参数为文本内容*/
	void Anyinfo(int, QString);

public:
	hServiceFramework(void) {
	}

	//UI下更新检查函数
	QStringList ui_CheckUpdate(void) {
		uCheckUpdate Check;
		QList<QStringList> VerList = Check.getUpdate();
		QList<QStringList> VerNew;
		if (!VerList.isEmpty()) {
			if (VerList[0][0] == "UNKNOWNNETERROR") {
				qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Net_Error");
			}
			else if (VerList[0][0] == "UNKNOWNBLOG") {
				qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Ver_Error");
			}
		}
		for (int i = 0; i < VerList.length(); i++) {
			if (Program_Settings("Update_Channel") == "Pre" && VerList[i][2] == "Pre") {
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
			emit Anyinfo(2, msg("Check_Update_Info_Ver_Error"));
		}
		else if (VerNew[0][2].toFloat() > Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Latest").arg(VerNew[0][0]).arg(VerNew[0][1]);
			return {VerNew[0][1],VerNew[0][3]};
		}
		else if (VerNew[0][2].toFloat() == Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_New");
			emit Anyinfo(1, msg("Check_Update_Info_New"));
		}
		else if (VerNew[0][2].toFloat() < Program_Info("Build").toFloat()) {
			qDebug().noquote() << "sysinfo→" + msg("Check_Update_Info_Insider");
			emit Anyinfo(1, msg("Check_Update_Info_Insider"));
		}
		return {"NODIALOG","NODIALOG"};
	}

	//SPOL转换核心启动函数（暂时无用）
	void ui_Tospol(QString fileNameIpt) {
		//bool func = HLtoSPOL(fileNameIpt);
		/*
		if (func) {
			emit Anyinfo(1, msg("Ui_To_Spol_End"));
		}else {
			emit Anyinfo(2, msg("Ui_To_Spol_End_Error"));
		}*/
	}

	//损坏图像清理函数
	void ui_DeleteEmptyMap(void) {
		DeleteCache(0);
		emit Anyinfo(1, msg("Function_Filecheck_Run_End"));
	}

	//缓存图像全清函数
	void ui_DeleteAllCache(void) {
		DeleteCache(1);
		emit Anyinfo(1, msg("Function_Filecheck_Cache_Clean"));
	}

	//UI下设置语言函数——注意filename是文件（语言）名而非路径
	void ui_langset(QString filename) {
		langset(filename);
		emit Anyinfo(1, msg("Function_Language_Loading_Success"));
	}

	/*文件夹打开函数
	num
	O======O
	数值1打开缓存文件夹，数值2打开资源文件夹
	数值3打开官方剧情文件夹，数值4打开用户剧情文件夹
	“赞美cmd.exe”*/
	void ui_OpenFolder(int num) {
		OpenFolder(num);
	}
};
