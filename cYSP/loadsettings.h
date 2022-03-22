#pragma once
#include <QtCore>

void writesettings(QString SettingsKey = "", QString SettingsValue = "");

int loadsettings(void);

QString Program_Settings(QString SettingsName);

void writereg(QString RegKeyName, QString RegValue);

QString readreg(QString RegKeyName);

void initreg(void);
