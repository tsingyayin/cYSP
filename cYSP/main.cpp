#pragma execution_character_set("utf-8")
#include "UIFolder/TopWindow.h"
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
    qDebug()<<QDir::currentPath();
    qDebug() << QString(argv[0]).section("\\", 0, -2);
    QDir::setCurrent(QString(argv[0]).section("\\", 0, -2));
    int DirectOpen = 0;
    string Usript;
    qDebug() << argc;
    qDebug() << argv[0];
    qDebug() << argv[1];
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

    DeleteCache(0);

    qDebug().noquote() << "sysinfo→" + msg("System_Info") + QSysInfo::kernelVersion();
    qDebug().noquote() << "sysinfo→" + msg("About_Info_Version") +Program_Info("Edition");
    qDebug().noquote() <<"sysinfo→"+msg("First_Print");
    //DirectOpen = 0;

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
            qDebug().noquote() << "UI";
            DirectOpen = 0;
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
 
    
    /*
    cout << "请输入内部索引" << endl;
    string usript;
    QString temp;
    QString sysopt;
    for (;;) {
        cin >> usript;
        temp = usript.c_str();
        sysopt = msg(temp);
        qDebug() << sysopt;
    }
    return 0;
    */
}

