#pragma execution_character_set("utf-8")
#include "UIFolder/TopWindow.h"
#include "UIFolder/ArtificialUI.h"
#include "global_value.h"
#include "loadsettings.h"
#include "Aaspcommand/aaspcommand.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>
#include <QCoreApplication>
#include <QDebug>
#include <exception>
#include <codecvt>
#include <locale>
#include <QSysInfo>
#include "langcontrol.h"

using namespace std;

int main(int argc, char *argv[])
{
    sDebug("DebugInfo→Start path : "+QDir::currentPath());
    sDebug("DebugInfo→Program path : "+QString(argv[0]).section("\\", 0, -2));
    QDir::setCurrent(QString(argv[0]).section("\\", 0, -2));
    int DirectOpen = 0;
    string Usript;
    sDebug("DebugInfo→Number of parameters : "+QString::number(argc));
    sDebug("DebugInfo→Parameters 1 : " + QString::fromUtf8(argv[0]));
    sDebug("DebugInfo→Parameters 2 : " + QString::fromUtf8(argv[1]));
    if (argv[1] != "") {
        DirectOpen = 1;
        Usript = "ui";
    }else {
        DirectOpen = 1;
        Usript = "window";
    }
    Usript = "window";
    ensuredirs(0);

    langset("0");

    loadsettings();

    DeleteCache(0);

    //initreg();

    sDebug("DebugInfo→" + msg("System_Info") + QSysInfo::kernelVersion());
    sDebug("DebugInfo→" + msg("About_Info_Version") +Program_Info("Edition"));

    if (readreg("Language") == "zh_SC") {
        qDebug().noquote() << "##############################";
        qDebug().noquote() << "#抵制不良游戏，拒绝盗版游戏。#\n#注意自我保护，谨防受骗上当。#\n#适度游戏益脑，沉迷游戏伤身。#\n#合理安排时间，享受健康生活。#";
        qDebug().noquote() << "##############################";
    }

    qDebug().noquote() <<"sysinfo→"+msg("First_Print");

    bool programme_run = TRUE;
    while (programme_run) {
        if (DirectOpen != 1) {
            cout << "Userinput\u2192";
            cin >> Usript;
        }
        if (Usript == "help") {
            aasphelp();
        }elif (Usript == "") {
            continue;
        }elif (Usript == "lang") {
            langinput();
        }elif (Usript == "about") {
            about();
        }elif(Usript == "update") {
            checkupdate(argc,argv);
            DirectOpen = 0;
        }elif(Usript == "clear") {
            DeleteCache(0);
        }elif(Usript == "clrall") {
            DeleteCache(1);
        }elif (Usript == "ui") {
            QApplication app(argc, argv);
            PlayerWindow UIWindow(argc, argv);
            if (Program_Settings("Window_DisplayMode") == "Full") {
                UIWindow.gshowFullScreen();
            }elif(Program_Settings("Window_DisplayMode") == "Window") {
                UIWindow.gshow();
            }else {
                UIWindow.gshowFullScreen();
            }
            int a = app.exec();
            qDebug().noquote() << "UI";
            Usript = "window";
            DirectOpen = 1;
        }elif (Usript == "window") {
            QApplication app(argc, argv);
            TopWindow MainWindow;
            MainWindow.show();
            int a = app.exec();
            DirectOpen = 1;
            if (a == 1) {
                Usript = "ui";
            }elif(a == 2) {
                Usript = "exit";
            }else { 
                DirectOpen = 0;
            }
            
        }else if (Usript == "exit") {
            qDebug().noquote() << "Safety Exit";
            Sleep(500);
            return 0;
        }

        else {
            qDebug().noquote() << "sysinfo→" + msg("Command_Error").arg(QString::fromStdString(Usript));
        }
    }
}

