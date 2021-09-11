#pragma once
#include <QtCore>

int writesettings(QString SettingsKey="",QString SettingsValue="");

int loadsettings(void);

QString Program_Settings(QString SettingsName);

void writereg(QString RegKeyName, QString RegValue);

QString readreg(QString RegKeyName);

void initreg(void);
