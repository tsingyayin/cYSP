#pragma once
#include <VICore>
#include <VIWidgets>
#include <YSPCore>
#include "ProjectPageUnit.h"

class StoryStudioPublicAPI ProjectPage :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public ProjectList* ListArea;
	_Public QGridLayout* CurrentLayout;
	_Public def_init ProjectPage() {
		StoryStudio::PackageMeta::getInstance()->addTranslatableObject(this);
		int w = StoryStudio::PackageMeta::getInstance()->getConfig("ProjectPage.Width").toInt();
		w = w < 400 ? 1600 : w;
		w = w > qGuiApp->primaryScreen()->availableSize().width() ? qGuiApp->primaryScreen()->availableSize().width() : w;
		int h = StoryStudio::PackageMeta::getInstance()->getConfig("ProjectPage.Height").toInt();
		h = h < 400 ? 900 : h;
		h = h > qGuiApp->primaryScreen()->availableSize().height() ? qGuiApp->primaryScreen()->availableSize().height() : h;
		this->resize(w, h);
		ListArea = new ProjectList(this);
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->addWidget(ListArea, 0, 0);
		onTranslating();
	}
	_Public virtual void onTranslating()override {
		this->setWindowTitle(getTranslation("Project_Window_Title_Text"));
	}
	_Public virtual void closeEvent(QCloseEvent* event) {
		StoryStudio::PackageMeta::getInstance()->setConfig("ProjectPage.Width", QString::number(this->width()));
		StoryStudio::PackageMeta::getInstance()->setConfig("ProjectPage.Height", QString::number(this->height()));
		StoryStudio::PackageMeta::getInstance()->saveConfig();
	}
};
