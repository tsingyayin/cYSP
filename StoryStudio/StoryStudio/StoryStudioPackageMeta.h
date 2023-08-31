/*
* 此文件含有您的项目的包元定义，您可以在此进行包的基础设置
*/
#pragma once
#include <VICore>
#include "private/StoryStudioCompileMacro.h"

namespace StoryStudio {
	class StoryStudioPublicAPI PackageMeta :public VIPackageMeta
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public VIDocument::VIJSON* DefaultColorTheme;
		_Public def_init PackageMeta() :VIPackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("StoryStudio");
			this->setPackageVersionMajor(StoryStudio_VERSION_MAJOR);
			this->setPackageVersionMinor(StoryStudio_VERSION_MINOR);
			this->setPackageVersionPatch(StoryStudio_VERSION_PATCH);
			this->setAuthor({ "StoryStudio `s author"});
			this->setDescription("StoryStudio do not have description yet!");
			this->setLicense("GPLv3.0");
			this->setURL("https://www.github.com/!!!YOUR_NAME!!!/StoryStudio");
			this->setOrganization("!!!YOUR_ORG_NAME!!!");
			this->setOrganizationDomain("https://www.github.com/!!!YOUR_ORG_NAME!!!");
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
			this->initConfig();

			DefaultColorTheme = new VIDocument::VIJSON(this);
			DefaultColorTheme->loadDefault(getPackageInternalPath() + "/resource/defaultColorTheme.json");
			DefaultColorTheme->loadSettings(getPackageRootPath() + "/defaultColorTheme.json", true);
		}
	};
}