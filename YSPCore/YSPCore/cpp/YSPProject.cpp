#include "../YSPProject.h"

VI_Singleton_StaticInit(YSPProject);

def_init YSPProject::YSPProject(QString ProjectFolder) {
	VI_Singleton_Init;
	ProjectConfig = new VIDocument::VIJSON(this);
	ProjectConfig->setSaveOnSet(true);
	ProjectConfig->loadDefault(YSPCore::PackageMeta::getInstance()->getPackageInternalPath() +
		"/resource/defaultProjectSettings.json");
}

QString YSPProject::getProjectSettingsFilePath() {
	return YSPRM->getCurrentProjectPath() + "/" + YSPRM->getCurrentProjectName() + ".ysp";
}

void YSPProject::initProject() {
	ProjectConfig->loadSettings(getProjectSettingsFilePath(), true);
	//在项目文件夹下新建文件夹
	QDir Dir;
	for (int i = 0; (YSPResourceManager::ProjectResourceType)i != YSPResourceManager::ProjectResourceType::__END__; i++) {
		Dir.mkpath(YSPRM->getProjectResourcePath() + "/" +
			YSPResourceManager::getProjectResourceTypeStr((YSPResourceManager::ProjectResourceType)i)
		);
	}
	Dir.mkpath(YSPRM->getProjectCachesPath());
	//在项目文件夹下新建main.js
	QFile MainJSInternal;
	MainJSInternal.setFileName(YSPCore::PackageMeta::getInstance()->getPackageInternalPath() +
		"/resource/defaultmain.js");
	MainJSInternal.open(QIODevice::ReadOnly);
	QFile MainJS;
	MainJS.setFileName(YSPRM->getCurrentProjectPath() + "/main.js");
	MainJS.open(QIODevice::WriteOnly);
	MainJS.write(MainJSInternal.readAll());
	MainJS.close();
	MainJSInternal.close();
	//Notice: 新建项目时不需要手动写入打开main.js，因为已经写在默认配置值了
}

bool YSPProject::loadProject() {
	bool procfg = ProjectConfig->loadSettings(getProjectSettingsFilePath());
	if (!procfg) {
		return false;
	}
	QString CTimeStr = QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss");
	ProjectConfig->setValueOf("ProjectMetaInfo.LastOpened", CTimeStr);
	QVariantList FileInfoList = ProjectConfig->getValueOf("ProjectEditorFileInfo.OpenedFiles").toList();
	for (auto i : FileInfoList) {
		YSPProjectConfig::OpenedFile Info;
		Info.FilePath = i.toMap().value("FilePath").toString();
		Info.CursorColumn = i.toMap().value("CursorColumn").toULongLong();
		Info.CursorLine = i.toMap().value("CursorLine").toULongLong();
		OpenedFiles.append(Info);
	}
	return true;
}

bool YSPProject::saveProject() {
	QVariantList FileInfoList;
	for (auto i : OpenedFiles) {
		QVariantMap Info;
		Info.insert("FilePath", i.FilePath);
		Info.insert("CursorColumn", i.CursorColumn);
		Info.insert("CursorLine", i.CursorLine);
		FileInfoList.append(Info);
	}
	ProjectConfig->setValueOf("ProjectEditorFileInfo.OpenedFiles", FileInfoList);
	return true;
}

QString YSPProject::getProjectAuthor() {
	return ProjectConfig->getValueOf("ProjectMetaInfo.Author").toString();
}

void YSPProject::setProjectAuthor(QString Author) {
	ProjectConfig->setValueOf("ProjectMetaInfo.Author", Author);
}

QString YSPProject::getProjectDescription() {
	return ProjectConfig->getValueOf("ProjectMetaInfo.Description").toString();
}

void YSPProject::setProjectDescription(QString Description) {
	ProjectConfig->setValueOf("ProjectMetaInfo.Description", Description);
}

QString YSPProject::getProjectEntry() {
	return ProjectConfig->getValueOf("ProjectMetaInfo.Entry").toString();
}

void YSPProject::setProjectEntry(QString Entry) {
	ProjectConfig->setValueOf("ProjectMetaInfo.Entry", Entry);
}

QString YSPProject::getProjectName() {
	return ProjectConfig->getValueOf("ProjectMetaInfo.Name").toString();
}

void YSPProject::setProjectName(QString Name) {
	ProjectConfig->setValueOf("ProjectMetaInfo.Name", Name);
}

YSPProjectConfig::MetaInfo YSPProject::getMetaInfoFromFile(const QString& filePath) {
	VIDocument::VIJSON* FileConfig = new VIDocument::VIJSON();
	bool filecfg = FileConfig->loadSettings(filePath);
	YSPProjectConfig::MetaInfo Info;
	Info.ProjectPath = filePath.section('/', 0, -2);
	Info.Type = FileConfig->getValueOf("MetaInfo.Type").toString();
	Info.Theme = FileConfig->getValueOf("MetaInfo.Theme").toString();
	Info.Name = FileConfig->getValueOf("MetaInfo.Name").toString();
	Info.Author = FileConfig->getValueOf("MetaInfo.Author").toString();
	Info.Description = FileConfig->getValueOf("MetaInfo.Description").toString();
	Info.SPOLVersion = FileConfig->getValueOf("MetaInfo.SPOLVersion").toString();
	Info.SPDFVersion = FileConfig->getValueOf("MetaInfo.SPDFVersion").toString();
	Info.ProgramVersion = FileConfig->getValueOf("MetaInfo.ProgramVersion").toString();
	Info.Entry = FileConfig->getValueOf("MetaInfo.Entry").toString();
	Info.LastOpened = FileConfig->getValueOf("MetaInfo.LastOpened").toString();
	Info.IsEffective = filecfg;
	delete FileConfig;
	return Info;
}

YSPProjectConfig::MetaInfo YSPProject::getMetaInfoInFolder(const QString& folderPath) {
	QString fileName = folderPath.section('/', -1);
	return getMetaInfoFromFile(folderPath + "/" + fileName + ".ysp");
}