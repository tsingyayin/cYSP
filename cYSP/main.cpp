#pragma execution_character_set("utf-8")
#include "UIFolder/TopWindow.h"
#include "UIFolder/ArtificialUI.h"
#include "global_value.h"
#include "loadsettings.h"
#include "Aaspcommand/aaspcommand.h"
#include <QApplication>
#include <QtWidgets>
#include <iostream>

#include <exception>

#include "langcontrol.h"
#include <stdexcept>
#include <windows.h>
#include <shellapi.h>
#include "UIFolder/WindowsWarn.h"
#include <time.h>

using namespace std;

int main(int argc, char* argv[])
{
    try {
        qRegisterMetaType<EIFL>("EIFL");
        srand((unsigned)time(NULL));
        qDebug().noquote() << Program_Info("SPEnv") + "\t" + Program_Info("Edition");
        qDebug().noquote() << "The kernel is checking startup parameters. Some information may not be displayed when the program is not in Forced Debugging Mode";
        sDebug("DebugInfo→Start path : " + QDir::currentPath());
        cout << argv[0] << endl;
        sDebug("DebugInfo→Program path : " + QString::fromLocal8Bit(argv[0]).section("\\", 0, -2));
        if (QString(argv[1]) != "Launcher") {
            QDir::setCurrent(QString::fromLocal8Bit(argv[0]).section("\\", 0, -2));
            setCurrentPath(QString::fromLocal8Bit(argv[0]));

        }
        else {
            setCurrentPath(QString::fromLocal8Bit(argv[0]), QString::fromLocal8Bit(argv[2]), TRUE);
            QApplication::addLibraryPath(QDir::currentPath());
            //qDebug() << QApplication::libraryPaths();
        }
        qDebug() << QDir::currentPath();

        int DirectOpen = 0;
        string Usript;
        sDebug("DebugInfo→Number of parameters : " + QString::number(argc));
        sDebug("DebugInfo→Parameters 1 : " + QString::fromUtf8(argv[0]));
        sDebug("DebugInfo→Parameters 2 : " + QString::fromUtf8(argv[1]));
        sDebug("DebugInfo→Your system version : " + QSysInfo::kernelVersion());
        QString KernelVersion = QSysInfo::kernelVersion();
        KernelVersion = "10.0.22000";
        if (KernelVersion.split(".")[0].toInt() < 10) {

            qDebug() << "##########\nWe are sorry to inform you that because the program uses the API provided by the new version of Windows10 (11), the YSP program cannot work on your old version of Windows System.\n\
This program has poor compatibility with Windows Systems released in and before 2018. Consider upgrading to the latest version of Windows to use the program\n\
我们很抱歉的告知您，由于程序使用了由新版本Windows10（11）提供的API，因此YSP程序无法在您的老旧版本Windows系统上工作。\n\
本程序对于2018年及之前发布的Windows系统的兼容性差。请考虑升级到最新版本的Windows以使用程序\n##########";
            QApplication app(argc, argv);
            WindowsWarn UIWindow;
            UIWindow.show();
            ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
            int i = app.exec();
            return 0;
        }
        if (KernelVersion.split(".")[2].toInt() < 22000) {
            QApplication app(argc, argv);
            WindowsWarn11 UIWindow;
            UIWindow.show();
            ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
            int i = app.exec();
            ShowWindow(GetConsoleWindow(), SW_NORMAL);
        }
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
        //Sleep(1000);
        DeleteCache(0);
        //Sleep(1000);
        if (Program_Settings("First_Start") != "False") {
            QApplication app(argc, argv);
            WindowsWarnSPOL_6 SPOL_6_Window;
            SPOL_6_Window.show();
            ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
            int i = app.exec();
            ShowWindow(GetConsoleWindow(), SW_NORMAL);
            writesettings("First_Start", "False");
        }
        //initreg();

        /*if (readreg("Language") == "zh_SC") {
            qDebug().noquote() << "##############################";
            qDebug().noquote() << "#抵制不良游戏，拒绝盗版游戏。#\n#注意自我保护，谨防受骗上当。#\n#适度游戏益脑，沉迷游戏伤身。#\n#合理安排时间，享受健康生活。#";
            qDebug().noquote() << "##############################";
        }*/

        qDebug().noquote() << "sysinfo→" + msg("Kernal_Text_IFL_Version").arg("IFL_20211227");
        qDebug().noquote() << "sysinfo→" + msg("Kernal_Text_First_Print").arg(Program_Info("SPEnv"));
        Sleep(1000);
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
            }elif(Usript == "exception") {
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
                TopWindow* MainWindow = new TopWindow();
                MainWindow->show();
                ShowWindow(GetConsoleWindow(), SW_MINIMIZE);
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
                    ShowWindow(GetConsoleWindow(), SW_NORMAL);
                }
            }elif(Usript == "escape") {
                for (;;) {
                    string a;
                    getline(cin, a);
                    if (a == "exit") { break; }
                    cout << spolEscape(QString::fromStdString(a)).toStdString();
                }
            }elif(Usript == "spoldev") {
                QString SPOLDevPath = QDir::currentPath() + "/SPOLDev.exe";
                system(SPOLDevPath.toStdString().c_str());
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

