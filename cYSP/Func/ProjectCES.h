#pragma once
#include <QtCore>
namespace CE {
    class CESettings :public QObject
    {
        Q_OBJECT
    public:
        enum class savePolicy {
            unknown = 0,
            saveAtOnce = 1,
            doNotSave = 2,
        };
    private:
        QMap<QString, QString> SettingsPair;
        QString gCESDir;
    public:
        CESettings(QString CESDir, QObject* parent = Q_NULLPTR) {
            gCESDir = CESDir;
        }
        void setKVPair(QMap<QString, QString> KVPair) {
            SettingsPair = KVPair;
        }
        bool loadSettings() {
            QFile settingsFile;
            settingsFile.setFileName(gCESDir);
            settingsFile.open(QIODevice::ReadOnly | QIODevice::Text);
            if (!settingsFile.isOpen()) {
                return false;
            }
            else {
                QTextStream settingsFileText(&settingsFile);
                settingsFileText.setCodec("UTF-8");
                QString stSingleLine;
                for (;;) {
                    stSingleLine = settingsFileText.readLine();
                    if (stSingleLine[0] == '#' || stSingleLine[0] == '\n') { continue; }
                    SettingsPair[stSingleLine.section("=", 0, 0)] = stSingleLine.section("=", 1, -1);
                    if (settingsFileText.atEnd()) { break; }
                }
            }
            return true;
        }
        QString valueOf(QString key) {
            return SettingsPair[key];
            
        }
        void setValue(QString Key, QString Value, savePolicy SavePolicy = savePolicy::saveAtOnce)
        {
            SettingsPair[Key] = Value;
            switch (SavePolicy) {
            case savePolicy::saveAtOnce:
                save();
                break;
            }
        }
        void save() {
            QMap<QString, QString>::const_iterator i = SettingsPair.constBegin();
            QString SettingsText = "";
            for (i; i != SettingsPair.constEnd(); i++) {
                SettingsText += (i.key() + "=" + i.value() + "\n");
            }

            QFile SettingsFile;
            SettingsFile.setFileName(gCESDir);
            SettingsFile.open(QIODevice::WriteOnly | QIODevice::Text);
            SettingsFile.write(SettingsText.toStdString().data());
            SettingsFile.close();
        }
    };
}