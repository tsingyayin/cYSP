#pragma once
#include "private/YSPCoreCompileMacro.h"
#include <VICore>

/*
YSPResourceManager
No matter what path this class shows you, its end will definitely not be a backslash
*/
class YSPCorePublicAPI YSPResourceManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Singleton(YSPResourceManager);
	_Signal void currentProjectChanged();
	_Public enum class ProjectResourceType {
		Background = 0, 
		UI, Character, Music, Sound, Item, Other, 
		__END__
	};
	_Private QString CurrentProjectPath;
	_Private QString CurrentProjectName;
	_Public def_init YSPResourceManager(VISuper* parent = VI_NULL);
	_Public static void executeInRawPath();
	_Public void loadArguProject();
	_Public QString getCurrentProjectPath();
	_Public QString getCurrentProjectName();
	_Public void changeCurrentProjectPath(QString path);
	_Public static QString getUsersPath();
	_Public static QString getGlobalPath();
	_Public static QString getProjectPath();
	_Public static QString getPlayerThemePath();
	_Public static QString getGlobalCachesPath();
	_Public static QString getGlobalResourcePath();
	_Public QString getProjectYSPPath();
	_Public QString getProjectCachesPath();
	_Public QString getProjectResourcePath();
	_Public static QString getProjectResourceTypeStr(ProjectResourceType type);
	_Public static QStringList getAllEffectiveProjectPath();
};
#define YSPRM YSPResourceManager::getInstance()