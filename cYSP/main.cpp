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
#include <QSysInfo>
#include "langcontrol.h"
#include <stdexcept>
#include <windows.h>

using namespace std;

int main(int argc, char *argv[])
{
    try {
        qDebug().noquote() << Program_Info("SPEnv");
        qDebug().noquote() << "The kernel is checking startup parameters. Some information may not be displayed when the program is not in Forced Debugging Mode";
        sDebug("DebugInfo→Start path : " + QDir::currentPath());
        sDebug("DebugInfo→Program path : " + QString(argv[0]).section("\\", 0, -2));
        QDir::setCurrent(QString(argv[0]).section("\\", 0, -2));
        int DirectOpen = 0;
        string Usript;
        sDebug("DebugInfo→Number of parameters : " + QString::number(argc));
        sDebug("DebugInfo→Parameters 1 : " + QString::fromUtf8(argv[0]));
        sDebug("DebugInfo→Parameters 2 : " + QString::fromUtf8(argv[1]));
        sDebug("DebugInfo→Your system version : " + QSysInfo::kernelVersion());
        if (argv[1] != "") {
            DirectOpen = 1;
            Usript = "ui";
        }
        else {
            DirectOpen = 1;
            Usript = "window";
        }
        Usript = "window";
        qDebug().noquote() << "======Execute program initialization======";
        
        ensuredirs(0);

        langset("0");

        loadsettings();

        DeleteCache(0);

        //initreg();
        
        /*if (readreg("Language") == "zh_SC") {
            qDebug().noquote() << "##############################";
            qDebug().noquote() << "#抵制不良游戏，拒绝盗版游戏。#\n#注意自我保护，谨防受骗上当。#\n#适度游戏益脑，沉迷游戏伤身。#\n#合理安排时间，享受健康生活。#";
            qDebug().noquote() << "##############################";
        }*/
        
        qDebug().noquote() << "sysinfo→" + msg("Kernal_Text_IFL_Version").arg("IFL_20211009");
        qDebug().noquote() << "sysinfo→" + msg("Kernal_Text_First_Print").arg(Program_Info("SPEnv"));

        bool programme_run = TRUE;
        while (programme_run) {
            if (DirectOpen != 1) {
                cout << "Userinput\u2192";
                cin >> Usript;
            }
            if (Usript == "help") {
                aasphelp();
            }elif(Usript == "") {
                continue;
            }elif(Usript == "lang") {
                langinput();
            }elif(Usript == "about") {
                about();
            }elif(Usript == "update") {
                checkupdate(argc, argv);
                DirectOpen = 0;
            }elif(Usript == "clear") {
                DeleteCache(0);
            }elif(Usript == "clrall") {
                DeleteCache(1);
            }elif(Usript=="exception") {
                throw overflow_error(0);
            }elif(Usript == "ui") {
                QApplication app(argc, argv);
                PlayerWindow UIWindow(argc, argv);
                if (Program_Settings("Window_DisplayMode") == "Full") {
                    UIWindow.gshowFullScreen();
                }elif(Program_Settings("Window_DisplayMode") == "Window") {
                    UIWindow.gshow();
                }
                else {
                    UIWindow.gshowFullScreen();
                }
                int a = app.exec();
                qDebug().noquote() << "UI";
                Usript = "window";
                DirectOpen = 1;
            }elif(Usript == "window") {
                QApplication app(argc, argv);
                TopWindow *MainWindow = new TopWindow();
                MainWindow->show();
                int a = app.exec();
                delete MainWindow;
                
                
                DirectOpen = 1;
                if (a == 1) {
                    Usript = "ui";
                }elif(a == 2) {
                    Usript = "exit";
                }
                else {
                    DirectOpen = 0;
                }

            }
            else if (Usript == "exit") {
                qDebug().noquote() << "Safety Exit";
                Sleep(500);
                return 0;
            }

            else {
                qDebug().noquote() << "sysinfo→" + msg("Kernel_Text_Command_Error").arg(QString::fromStdString(Usript));
            }
        }
    }
    catch (exception& e) {
        cout << e.what() << endl;
        getchar();
        getchar();
    }
    catch (...) {
        cout << "UNKNOWN_EXCEPTION" << endl;
        getchar();
        getchar();
    }
}

