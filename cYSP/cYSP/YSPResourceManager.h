#pragma once
#include <VICore>
#include "YSPProject.h"
/*
YSPResourceManager
No matter what path this class shows you, its end will definitely not be a backslash
*/
class YSPResourceManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Singleton(YSPResourceManager);
	_Signal void currentProjectChanged();
	_Public QString CurrentProjectPath;
	_Public def_init YSPResourceManager(VISuper* parent = VI_NULL):VIObject(parent) {
		VI_Singleton_Init;
		CurrentProjectPath = "";
	};
	_Public void executeInRawPath() {
		// ensure the program is running in the raw path
		QString path = QCoreApplication::applicationDirPath();
		QDir::setCurrent(path);
	}
	_Public bool checkStartWithProject() {
		QStringList args = QCoreApplication::arguments();
		if (args.size() > 1) {
			QString path = args[1];
			if (path.endsWith(".ysp")) {
				changeCurrentProjectPath(path.replace("\\", "/").section("/", 0, -2));
				return true;
			}
		}
		return false;
	}
	_Public QString getCurrentProjectPath() {
		return CurrentProjectPath;
	}
	_Public void changeCurrentProjectPath(QString path) {
		if (YSPProject::getInstance() != VI_NULL) {
			YSPProject::getInstance()->deleteLater();
		}
		new YSPProject(path);
		CurrentProjectPath = path;
		emit currentProjectChanged();
	}
	_Public QString getUsersPath() {
		return "./UsersData";
	}
	_Public QString getGlobalResourcesPath() {
		return "./UsersData/Global";
	}
	_Public QString getProjectPath() {
		return "./UsersData/Projects";
	}
	_Public QString getCachesPath() {
		if (CurrentProjectPath != "") {
			return CurrentProjectPath + "/.ysp/Caches";
		}
		else {
			return "./UsersData/Caches";
		}
	}
};