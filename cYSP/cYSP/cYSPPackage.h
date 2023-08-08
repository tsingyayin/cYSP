/*
* 此文件含有您的项目的包类的定义，您可以将包类的构造函数当做您的项目的入口函数。
*/
#pragma once
#include "cYSPPackageMeta.h"
#include "YSPResourceManager.h"
#include "YSPImageResource.h"
namespace cYSP {
	class cYSPPublicAPI Package :public VIPackage, VITranslatableObject
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackage);
		VI_Singleton(Package);
		_Private QString t;
		_Public def_init Package() {
			VI_Singleton_Init;
			setPackageMeta(new cYSP::PackageMeta);
			getPackageMeta()->addTranslatableObject(this);
			getPackageMeta()->initTranslation();
			YSPResourceManager* rm = new YSPResourceManager(this);
			YSPImageResource* ir = new YSPImageResource(this);
			YSPResourceManager::getInstance()->executeInRawPath();
		}
		_Public virtual void onTranslating() override {

		}

	};
}