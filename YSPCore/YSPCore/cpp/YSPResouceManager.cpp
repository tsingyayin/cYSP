#include "../YSPResourceManager.h"
#include "../YSPProject.h"

VI_Singleton_StaticInit(YSPResourceManager);

def_init YSPResourceManager::YSPResourceManager(VISuper* parent) :VIObject(parent) {
	VI_Singleton_Init;
	CurrentProjectPath = "";
};
void YSPResourceManager::executeInRawPath() {
	// ensure the program is running in the raw path
	QString path = QCoreApplication::applicationDirPath();
	QDir::setCurrent(path);
}
void YSPResourceManager::loadArguProject() {
	QStringList args = QCoreApplication::arguments();
	if (args.size() > 1) {
		QString path = args[1];
		if (path.endsWith(".ysp")) {
			changeCurrentProjectPath(path.replace("\\", "/").section("/", 0, -2));
		}
	}
}
QString YSPResourceManager::getCurrentProjectPath() {
	return CurrentProjectPath;
}
QString YSPResourceManager::getCurrentProjectName() {
	return CurrentProjectName;
}
void YSPResourceManager::changeCurrentProjectPath(QString path) {
	if (YSPProject::getInstance() != VI_NULL) {
		YSPProject::getInstance()->deleteLater();
	}
	new YSPProject(path);
	CurrentProjectPath = path;
	CurrentProjectName = path.split("/").last();
	emit currentProjectChanged();
}
QString YSPResourceManager::getUsersPath() { return "./UsersData"; }
QString YSPResourceManager::getGlobalPath() { return getUsersPath() + "/Global"; }
QString YSPResourceManager::getProjectPath() { return getUsersPath() + "/Projects"; }
QString YSPResourceManager::getPlayerThemePath() { return getGlobalPath() + "/PlayerTheme"; }
QString YSPResourceManager::getGlobalCachesPath() { return getGlobalPath() + "/Caches"; }
QString YSPResourceManager::getGlobalResourcePath() { return getGlobalPath() + "/Resources";}
QString YSPResourceManager::getProjectYSPPath() {
	if (CurrentProjectPath != "") {
		return CurrentProjectPath + "/.ysp";
	}
	else {
		return getGlobalPath();
	}
}
QString YSPResourceManager::getProjectCachesPath() { return getProjectYSPPath() + "/Caches"; }
QString YSPResourceManager::getProjectResourcePath() { 
	if (CurrentProjectPath != "") {
		return CurrentProjectPath + "/Resources";
	}
	else {
		return getGlobalResourcePath();
	}
}
QString YSPResourceManager::getProjectResourceTypeStr(ProjectResourceType type) {
	switch (type) {
		VI_ENUMSTR(ProjectResourceType, Background);
		VI_ENUMSTR(ProjectResourceType, Character);
		VI_ENUMSTR(ProjectResourceType, Music);
		VI_ENUMSTR(ProjectResourceType, Sound);
		VI_ENUMSTR(ProjectResourceType, UI);
		VI_ENUMSTR(ProjectResourceType, Item);
		VI_ENUMSTR(ProjectResourceType, Other);
	}
}
QStringList YSPResourceManager::getAllEffectiveProjectPath() {
	QString proPath = getProjectPath();
	qDebug()<< "project path: " + proPath;
	QDir dir(proPath);
	QStringList list = dir.entryList(QDir::Dirs | QDir::NoDotAndDotDot);
	qDebug()<< "project list: " + list.join(",");
	for (int i = 0; i < list.size(); i++) {
		list[i] = proPath + "/" + list[i] + "/"+list[i] + ".ysp";
	}
	QFile file;
	for (auto it = list.begin(); it != list.end();) {
		file.setFileName(*it);
		if (!file.exists()) {
			it = list.erase(it);
		}
		else {
			*it = (*it).section("/", 0, -2);
			qDebug()<<"find project: " + *it;
			it++;
		}
	}
	return list;
}