#pragma once
#include <VICore>
#include "cYSPPackageMeta.h"
class YSPProject :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public QString ProjectDirPath;
	_Public QString ProjectName;
	_Public VIDocument::VIJSON* ProjectConfig;
	_Public def_init YSPProject(QString ProjectFolder) {
		ProjectConfig = new VIDocument::VIJSON(this);
		ProjectConfig->loadDefault(cYSP::PackageMeta::getInstance()->getPackageInternalPath() +
			"/resource/defaultProjectSettings.json");
		ProjectDirPath = ProjectFolder;
		ProjectName = ProjectFolder.split("/").last();	
	}
	_Public bool loadProject() {
		return ProjectConfig->loadSettings(ProjectDirPath + "/" + ProjectName + ".json");
	}
};