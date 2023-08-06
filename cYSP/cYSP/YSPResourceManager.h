#pragma once
#include <VICore>

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
	_Public def_init YSPResourceManager() {
		VI_Singleton_Init;
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
				CurrentProjectPath = path.replace("\\", "/").section("/", 0, -2);
				emit currentProjectChanged();
				return true;
			}
		}
		return false;
	}
	_Public QString getCurrentProjectPath() {
		return CurrentProjectPath;
	}
	_Public void changeCurrentProjectPath(QString path) {
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
};