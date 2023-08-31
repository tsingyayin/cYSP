/*
* 此文件含有您的项目的包元定义，您可以在此进行包的基础设置
*/
#pragma once
#include <VICore>
#include "private/Player2DCompileMacro.h"

namespace Player2D {
	class Player2DPublicAPI PackageMeta :public VIPackageMeta
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public def_init PackageMeta() :VIPackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("Player2D");
			this->setPackageVersionMajor(Player2D_VERSION_MAJOR);
			this->setPackageVersionMinor(Player2D_VERSION_MINOR);
			this->setPackageVersionPatch(Player2D_VERSION_PATCH);
			this->setAuthor({ "Player2D `s author"});
			this->setDescription("Player2D do not have description yet!");
			this->setLicense("GPLv3.0");
			this->setURL("https://www.github.com/!!!YOUR_NAME!!!/Player2D");
			this->setOrganization("!!!YOUR_ORG_NAME!!!");
			this->setOrganizationDomain("https://www.github.com/!!!YOUR_ORG_NAME!!!");
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
		}
	};
}