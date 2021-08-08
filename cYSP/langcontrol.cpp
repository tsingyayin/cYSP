#pragma once
#pragma execution_character_set("utf-8")
#include <QApplication>
#include <QtWidgets>
#include <map>
#include <iostream>
#include <string>
#include <list>
#include <QCoreApplication>
#include <QDebug>
#include <ctime>
#include "langcontrol.h"
#include <exception>
using namespace std;
static QMap<QString, QString> msglist;
clock_t timeStart, timeEnd;

int langset(QString langname) {
    timeStart = clock();
    QString langnameraw = langname;
    if (langnameraw == "0") {
        QFile spLangSettingsFile;
        spLangSettingsFile.setFileName(".\\Language\\base.ini");
        spLangSettingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
        if (!spLangSettingsFile.isOpen()) {
            langname = "zh_SC";
        }else {
            QTextStream spLangSettingsText(&spLangSettingsFile);
            spLangSettingsText.setCodec("UTF-8");
            langname = spLangSettingsText.readLine();
            spLangSettingsFile.close();
        }
        if (langname == "") { langname = "zh_SC"; }
    }
    QFile spLanguageFile;
    spLanguageFile.setFileName(".\\Language\\"+langname+".splang");
    spLanguageFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!spLanguageFile.isOpen()) { 
        qDebug().noquote() << "sysinfo��" + msg("Lang_Not_In_Support").arg(langname);
        return 0; 
    }else {
        QFile spLangSettingsFile;
        spLangSettingsFile.setFileName(".\\Language\\base.ini");
        spLangSettingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
        if (!spLangSettingsFile.isOpen()) { return 0; }
        spLangSettingsFile.write(langname.toStdString().data());
        spLangSettingsFile.close();

    }
    QTextStream spLanguageText(&spLanguageFile);
    spLanguageText.setCodec("UTF-8");
    QString spSingleLine;
    for (;;) {
        spSingleLine = spLanguageText.readLine();
        if (spSingleLine[0] == '#' || spSingleLine[0] == '\n') { continue; }
        msglist[spSingleLine.section(":", 0, 0)] = spSingleLine.section(":", 1, -1);
        if (spLanguageText.atEnd()) { break; }
    }
    timeEnd = clock();
    qDebug().noquote()<< "sysinfo��" + msg("First_Print_Load_Lang_End").arg(timeEnd-timeStart);
    return 1;
}

QString msg(QString Usript) {
    try {
        if (msglist[Usript] == "") {
            throw "FAQ";
        }else {
            return msglist[Usript];
        }
    }
    catch (...) {
        return "UNKNOWNMSG:" + Usript;
    }
}
