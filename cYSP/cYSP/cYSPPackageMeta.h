/*
* 此文件含有您的项目的包元定义，您可以在此进行包的基础设置
*/
#pragma once
#include <VICore>
#include "private/cYSPCompileMacro.h"

namespace cYSP {
	class cYSPPublicAPI PackageMeta :public VIPackageMeta
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackageMeta);
		VI_Singleton(PackageMeta);
		_Public def_init PackageMeta() :VIPackageMeta() {
			VI_Singleton_Init;
			this->setPackageName("cYSP");
			this->setPackageVersionMajor(cYSP_VERSION_MAJOR);
			this->setPackageVersionMinor(cYSP_VERSION_MINOR);
			this->setPackageVersionPatch(cYSP_VERSION_PATCH);
			this->setAuthor({ "cYSP `s author"});
			this->setDescription("cYSP do not have description yet!");
			this->setLicense("GPLv3.0");
			this->setURL("https://www.github.com/!!!YOUR_NAME!!!/cYSP");
			this->setOrganization("!!!YOUR_ORG_NAME!!!");
			this->setOrganizationDomain("https://www.github.com/!!!YOUR_ORG_NAME!!!");
			this->addTranslationFileName(Visindigo::Language::zh_SC, "zh_SC.vil", true);
			this->addTranslationFileName(Visindigo::Language::en_US, "en_US.vil", true);
			this->setDefaultLanguage(Visindigo::Language::zh_SC);
		}
	};
}