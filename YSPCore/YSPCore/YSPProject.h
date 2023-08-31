#pragma once
#include <VICore>
#include "YSPCorePackageMeta.h"
#include "YSPResourceManager.h"

namespace YSPProjectConfig{
	struct YSPCorePublicAPI OpenedFile {
		QString FilePath;
		unsigned long long CursorColumn;
		unsigned long long CursorLine;
	};
	typedef QVector<OpenedFile> OpenedFiles;
	struct YSPCorePublicAPI MetaInfo {
		QString ProjectPath;
		QString Type;
		QString Theme;
		QString Name;
		QString Author;
		QString Description;
		QString SPOLVersion;
		QString SPDFVersion;
		QString ProgramVersion;
		QString Entry;
		QString LastOpened;
		bool IsEffective = false; // Pay attention to this default value
	};
};

class YSPCorePublicAPI YSPProject :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Singleton(YSPProject);
	_Public VIDocument::VIJSON* ProjectConfig;
	_Public YSPProjectConfig::OpenedFiles OpenedFiles;
	_Public def_init YSPProject(QString ProjectFolder);
	_Public QString getProjectSettingsFilePath();
	_Public void initProject();
	_Public bool loadProject();
	_Public bool saveProject();
	_Public QString getProjectAuthor();
	_Public void setProjectAuthor(QString Author);
	_Public QString getProjectDescription();
	_Public void setProjectDescription(QString Description);
	_Public QString getProjectEntry();
	_Public void setProjectEntry(QString Entry);
	_Public QString getProjectName();
	_Public void setProjectName(QString Name);
	_Public static YSPProjectConfig::MetaInfo getMetaInfoFromFile(const QString& filePath);
	_Public static YSPProjectConfig::MetaInfo getMetaInfoInFolder(const QString& folderPath);
};