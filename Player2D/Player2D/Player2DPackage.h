/*
* 此文件含有您的项目的包类的定义，您可以将包类的构造函数当做您的项目的入口函数。
*/
#pragma once
#include "Player2DPackageMeta.h"

namespace Player2D {
	class Player2DPublicAPI Package :public VIPackage, VITranslatableObject
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackage);
		VI_Singleton(Package);
		_Private QString t;
		_Public def_init Package() {
			VI_Singleton_Init;
			setPackageMeta(new Player2D::PackageMeta);
			getPackageMeta()->addTranslatableObject(this);
			getPackageMeta()->initTranslation();
		}
		_Public virtual void onTranslating() override {

		}

	};
}