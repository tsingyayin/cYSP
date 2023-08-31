/*
* 此文件含有您的项目的包类的定义，您可以将包类的构造函数当做您的项目的入口函数。
*/
#pragma once
#include "StoryStudioPackageMeta.h"
#include "../WelcomePage/WelcomePage.h"
#include "../ProjectPage/ProjectPage.h"

namespace StoryStudio {
	class StoryStudioPublicAPI Package :public VIPackage, VITranslatableObject
	{
		Q_OBJECT;
		VI_OBJECT;
		VI_HAS_INHERIT(VIPackage);
		VI_Singleton(Package);
		_Private QString t;
		_Public WelcomePage* welcomePage;
		_Public ProjectPage* projectPage;
		_Public def_init Package() {
			VI_Singleton_Init;
			setPackageMeta(new StoryStudio::PackageMeta);
			getPackageMeta()->addTranslatableObject(this);
			getPackageMeta()->initTranslation();

			QString theme = getPackageMeta()->getConfig("CurrentColorTheme").toString();
			QString clrStr = StoryStudio::PackageMeta::getInstance()->DefaultColorTheme->getValueOf(theme+".Global.ThemeColor").toString();
			QColor clr(clrStr);
			VIFrame->getPaletteGroup()->setColor(VIPalette::DefaultColorName::Foreground, clr);

			welcomePage = new WelcomePage();
			connect(welcomePage, &WelcomePage::closed, this, &Package::onWelcomePageClosed);
			welcomePage->show();
		}
		_Public virtual void onWelcomePageClosed() {
			welcomePage->deleteLater();
			projectPage = new ProjectPage();
			projectPage->show();
		}
		_Public virtual void onTranslating() override {

		}

	};
}