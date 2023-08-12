#pragma once
#include <VICore>
#include "cYSPPackageMeta.h"

struct YSPProjectEditorFileInfo
{
	QString FilePath;
	unsigned long long CursorColumn;
	unsigned long long CursorLine;
};
typedef QList<YSPProjectEditorFileInfo> YSPProjectEditorFileInfoList;
class YSPProject :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QString ProjectDirPath;
	_Public QString ProjectName;
	_Public VIDocument::VIJSON* ProjectConfig;
	_Public YSPProjectEditorFileInfoList OpenedFiles;
	VI_Singleton(YSPProject)
	_Public def_init YSPProject(QString ProjectFolder) {
		VI_Singleton_Init;
		ProjectConfig = new VIDocument::VIJSON(this);
		ProjectConfig->setSaveOnSet(true);
		ProjectConfig->loadDefault(cYSP::PackageMeta::getInstance()->getPackageInternalPath() +
			"/resource/defaultProjectSettings.json");
		ProjectDirPath = ProjectFolder;
		ProjectName = ProjectFolder.split("/").last();	
	}
	_Public void initProject() {
		ProjectConfig->loadSettings(ProjectDirPath + "/" + ProjectName + ".json", true);
		//在项目文件夹下新建文件夹
		QStringList Folders = { "/.ysp", "/resources", "/resources/background",
		"/resources/music","/resources/sound","/resources/chara","/resources/ui"};
		for (auto Folder : Folders) {
			QDir dir(ProjectDirPath + Folder);
			if (!dir.exists()) {
				dir.mkpath(ProjectDirPath + Folder);
			}
		}
		QFile MainJSInternal;
		MainJSInternal.setFileName(cYSP::PackageMeta::getInstance()->getPackageInternalPath() +
			"/resource/defaultmain.js");
		MainJSInternal.open(QIODevice::ReadOnly);
		QFile MainJS;
		MainJS.setFileName(ProjectDirPath + "/main.js");
		MainJS.open(QIODevice::WriteOnly);
		MainJS.write(MainJSInternal.readAll());
		MainJS.close();
		MainJSInternal.close();
	}
	_Public bool loadProject() {
		ProjectConfig->loadSettings(ProjectDirPath + "/" + ProjectName + ".json");
		QVariantList FileInfoList = ProjectConfig->getValueOf("ProjectEditorFileInfo.OpenedFiles").toList();
		for (auto i : FileInfoList) {
			YSPProjectEditorFileInfo Info;
			Info.FilePath = i.toMap().value("FilePath").toString();
			Info.CursorColumn = i.toMap().value("CursorColumn").toULongLong();
			Info.CursorLine = i.toMap().value("CursorLine").toULongLong();
			OpenedFiles.append(Info);
		}
	}
	_Public bool saveProject() {
		QVariantList FileInfoList;
		for (auto i : OpenedFiles) {
			QVariantMap Info;
			Info.insert("FilePath", i.FilePath);
			Info.insert("CursorColumn", i.CursorColumn);
			Info.insert("CursorLine", i.CursorLine);
			FileInfoList.append(Info);
		}
		ProjectConfig->setValueOf("ProjectEditorFileInfo.OpenedFiles", FileInfoList);
	}
	_Public QString getProjectAuthor() {
		return ProjectConfig->getValueOf("ProjectAuthor").toString();
	}
	_Public void setProjectAuthor(QString Author) {
		ProjectConfig->setValueOf("ProjectAuthor", Author);
	}
	_Public QString getProjectDescription() {
		return ProjectConfig->getValueOf("ProjectDescription").toString();
	}
	_Public void setProjectDescription(QString Description) {
		ProjectConfig->setValueOf("ProjectDescription", Description);
	}
	_Public QString getProjectEntry() {
		return ProjectConfig->getValueOf("ProjectEntry").toString();
	}
	_Public void setProjectEntry(QString Entry) {
		ProjectConfig->setValueOf("ProjectEntry", Entry);
	}
	_Public QString getProjectName() {
		return ProjectConfig->getValueOf("ProjectName").toString();
	}
	_Public void setProjectName(QString Name) {
		ProjectConfig->setValueOf("ProjectName", Name);
	}
};