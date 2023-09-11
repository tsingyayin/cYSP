#pragma once
#include <VICore>
#include <VIWidgets>
#include <YSPCore>
#include "ProjectPageUnit.h"

class StoryStudioPublicAPI ProjectPage :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VILabel* VersionLabel;
	_Public ProjectList* ListArea;
	_Public ProjectInfoWidget* InfoArea;
	_Public QuickActionsWidget* QuickActions;
	_Public QGridLayout* CurrentLayout;
	_Private bool cfgIsMaximized = false;
	_Public def_init ProjectPage() {
		StoryStudio::PackageMeta::getInstance()->addTranslatableObject(this);
		VersionLabel = new VILabel(this);
		VersionLabel->setText("  Yayin Story Studio  " + StoryStudio::PackageMeta::getInstance()->getPackageVersion());
		VersionLabel->setVIDStyleSheet("default", "\
			VILabel{background-color:ACLR_"+VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Background) + "_CLR;\
			color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Text) + "_CLR;\
			font-size:APR_30_PR;\
			}\
		");
		VersionLabel->applyVIDSS("default");
		ListArea = new ProjectList(this);
		ListArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
		connect(ListArea, &ProjectList::projectSelected, this, &ProjectPage::onSelectProjectChanged);
		InfoArea = new ProjectInfoWidget(this);
		InfoArea->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
		ListArea->initProjects();

		QuickActions = new QuickActionsWidget(this);
		QuickActions->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

		CurrentLayout = new QGridLayout(this);
		CurrentLayout->setSpacing(0);
		CurrentLayout->setContentsMargins(0, 0, 0, 0);
		CurrentLayout->addWidget(VersionLabel, 0, 0, 1, 2);
		CurrentLayout->addWidget(QuickActions, 1, 0, 2, 1);
		CurrentLayout->addWidget(ListArea, 1, 1, 1, 1);
		CurrentLayout->addWidget(InfoArea, 2, 1, 1, 1);
		CurrentLayout->setColumnStretch(0, 1);
		CurrentLayout->setColumnStretch(1, 5);

		int w = StoryStudio::PackageMeta::getInstance()->getConfig("ProjectPage.Width").toInt();
		w = w < 1000 ? 1600 : w;
		w = w > qGuiApp->primaryScreen()->availableSize().width() ? qGuiApp->primaryScreen()->availableSize().width() : w;
		int h = StoryStudio::PackageMeta::getInstance()->getConfig("ProjectPage.Height").toInt();
		h = h < 800 ? 900 : h;
		h = h > qGuiApp->primaryScreen()->availableSize().height() ? qGuiApp->primaryScreen()->availableSize().height() : h;
		cfgIsMaximized = StoryStudio::PackageMeta::getInstance()->getConfig("ProjectPage.IsMaximized").toBool();
		this->resize(w, h);
		this->setMinimumSize(1000, 800);
		isMaximized();
		onTranslating();
	}
	_Public virtual void showEvent(QShowEvent* event)override {
		if (cfgIsMaximized) {
			this->showMaximized();
		}
	}
	_Slot void onSelectProjectChanged(VIAbstractRatioWidget* tar) {
		ProjectLine* line = dynamic_cast<ProjectLine*>(tar);
		if (line != nullptr) {
			InfoArea->refreshWithProjectMeta(&line->Meta);
		}
	}
	_Public virtual void resizeEvent(QResizeEvent* event)override {
		VersionLabel->setFixedHeight(this->height() / 6);
		VersionLabel->refreshVIDStyleSheet();
		QuickActions->setFixedWidth(this->width() / 4);
		InfoArea->setFixedHeight(this->height() / 4);
	}
	_Public virtual void onTranslating()override {
		this->setWindowTitle(getTranslation("Project_Window_Title_Text"));
	}
	_Public virtual void closeEvent(QCloseEvent* event) {
		if (!this->isMaximized()) {
			StoryStudio::PackageMeta::getInstance()->setConfig("ProjectPage.Width", QString::number(this->width()));
			StoryStudio::PackageMeta::getInstance()->setConfig("ProjectPage.Height", QString::number(this->height()));
		}
		StoryStudio::PackageMeta::getInstance()->setConfig("ProjectPage.IsMaximized", this->isMaximized());
		StoryStudio::PackageMeta::getInstance()->saveConfig();
	}
};
