#pragma once
#include "loadsettings.h"
#include "global_value.h"
#include "langcontrol.h"
#include <QtCore>
static QMap<QString, QString> SettingsList;
QString Initial_prompt_statement = "#����ĵ��ǳ������õļ�¼�ĵ���\n#������ٳ�ʼ�������趨������ֱ��ɾ�����ĵ������⣨���ܣ���Ӱ�������ɾ�����ĵ�����״������ٶȡ�\n\n";
void writesettings(QString SettingsKey, QString SettingsValue)
{
    if (SettingsKey != "" && SettingsValue != "") {
        SettingsList[SettingsKey] = SettingsValue; 
    }
    QMap<QString, QString>::const_iterator i = SettingsList.constBegin();
    QString SettingsText;
    SettingsText += Initial_prompt_statement;
    for (i; i != SettingsList.constEnd(); i++) {
        SettingsText += (i.key() + "=" + i.value() + "\n");
    }

    QFile SettingsFile;
    SettingsFile.setFileName("./options.txt");
    SettingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
    SettingsFile.write(SettingsText.toStdString().data());
    SettingsFile.close();
}

int loadsettings(void) {
    SettingsList["Filter_Level"] = "Full";
    SettingsList["Forced_Debugging_Info"] = "False";
    SettingsList["GCPMode"] = "False";
    SettingsList["Update_Channel"] = "Auto";
    SettingsList["Window_DisplayMode"] = "Full";
    SettingsList["Window_Geometry"] = "1366_768";
    SettingsList["Window_Monitor"] = "0";
    QFile settingsFile;
    settingsFile.setFileName("./options.txt");
    settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
    if (!settingsFile.isOpen()) {
        qDebug().noquote() << "CAN NOT FIND INIT SETTINGS!";
        writesettings();
    }else{
        QTextStream settingsFileText(&settingsFile);
        settingsFileText.setCodec("UTF-8");
        QString stSingleLine;
        for (;;) {
            stSingleLine = settingsFileText.readLine();
            if (stSingleLine[0] == '#' || stSingleLine[0] == '\n') { continue; }
            SettingsList[stSingleLine.section("=", 0, 0)] = stSingleLine.section("=", 1, -1);
            if (settingsFileText.atEnd()) { break; }
        }
    }
    return 0;
}

QString Program_Settings(QString SettingsName) 
{
    try {
        if (SettingsList[SettingsName] == "") {
            throw "FAQ";
        }
        else {
            return SettingsList[SettingsName];
        }
    }
    catch (...) {
        return "UNKNOWNSET:" + SettingsName;
    }
}

void writereg(QString RegKeyName, QString RegValue) {
    QSettings ProgramSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\YixuSoftware\\cYSP", QSettings::NativeFormat);
    ProgramSettings.setValue(RegKeyName, RegValue);
}

QString readreg(QString RegKeyName) {
    QSettings ProgramSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\YixuSoftware\\cYSP", QSettings::NativeFormat);
    QString RegValue = ProgramSettings.value(RegKeyName, "POI_ERROR").toString();
    if ( RegValue== "POI_ERROR") {
        initreg();
        return "ERROR";
    }else {
        return RegValue;
    }
}

void initreg(void) {
    QSettings ProgramSettings("HKEY_LOCAL_MACHINE\\SOFTWARE\\YixuSoftware\\cYSP",QSettings::NativeFormat);
    if (ProgramSettings.value("Adult", "POI_ERROR") == "POI_ERROR") { ProgramSettings.setValue("Adult", "UNKOWN"); }
    if (ProgramSettings.value("Version", "POI_ERROR") == "POI_ERROR") { ProgramSettings.setValue("Version", Program_Info("Edition")); }
    if (ProgramSettings.value("Language", "POI_ERROR") == "POI_ERROR") { ProgramSettings.setValue("Language","zh_SC"); }
}