#pragma once
#include <VICore>
#include <VIWidgets>
#include <YSPCore>
#include "../StoryStudio/StoryStudioPackageMeta.h"

class StoryStudioPublicAPI ProjectLine :public VIAbstractRatioWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VILabel* TypeLabel;
	_Public VILabel* ThemeLabel;
	_Public VILabel* ProjectNameLabel;
	_Public VILabel* ProjectOpenedTimeLabel;
	_Public VILabel* ProjectDirLabel;
	_Public VILabel* ProjectDescriptionLabel;
	_Public QGridLayout* CurrentLayout;
	_Public YSPProjectConfig::MetaInfo Meta;
	_Public def_init ProjectLine(QWidget* parent = VI_NULL) :VIAbstractRatioWidget(parent) {
		TypeLabel = new VILabel(this);
		ThemeLabel = new VILabel(this);
		TypeLabel->setScaledContents(true);
		ThemeLabel->setScaledContents(true);
		ProjectNameLabel = new VILabel(this);
		ProjectOpenedTimeLabel = new VILabel(this);
		ProjectDirLabel = new VILabel(this);
		ProjectDescriptionLabel = new VILabel(this);
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->addWidget(TypeLabel, 0, 0, 3, 1);
		CurrentLayout->addWidget(ThemeLabel, 0, 1, 3, 1);
		CurrentLayout->addWidget(ProjectNameLabel, 0, 2, 1, 1);
		CurrentLayout->addWidget(ProjectOpenedTimeLabel, 0, 3, 1, 1);
		CurrentLayout->addWidget(ProjectDirLabel, 1, 2, 1, 2);
		CurrentLayout->addWidget(ProjectDescriptionLabel, 2, 2, 1, 2);
		TypeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		ThemeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		ProjectNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		ProjectOpenedTimeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		ProjectDirLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		ProjectDescriptionLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
	}
	_Public void initFromProjectMeta(YSPProjectConfig::MetaInfo& meta) {
		Meta = meta;
		TypeLabel->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath()+"/resource/Player2DIcon.png"));
		ThemeLabel->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/ArknightsThemeIcon.png"));
		ProjectNameLabel->setText(meta.Name);
		ProjectOpenedTimeLabel->setText(meta.LastOpened);
		ProjectDirLabel->setText(meta.ProjectPath);
		ProjectDescriptionLabel->setText(meta.Description);
	}
	_Public void resizeEvent(QResizeEvent* event) {
		TypeLabel->setFixedSize(this->height()-22, this->height()-22);
		ThemeLabel->setFixedSize(this->height()-22, this->height()-22);
	}
};

class StoryStudioPublicAPI ProjectList :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VIRatioWidgetContainer* Container;
	_Public QScrollArea* ScrollArea;
	_Public def_init ProjectList(QWidget* parent = VI_NULL):VIWidget(parent) {
		ScrollArea = new QScrollArea(this);
		Container = new VIRatioWidgetContainer(Qt::Vertical, ScrollArea);
		ScrollArea->setWidget(Container);
		ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		initProjects();
	}
	_Public void initProjects() {
		QStringList projects = YSPResourceManager::getAllEffectiveProjectPath();
		for (auto i = projects.begin(); i != projects.end(); i++) {
			YSPProjectConfig::MetaInfo meta = YSPProject::getMetaInfoInFolder(*i);
			ProjectLine* line = new ProjectLine(Container);
			qDebug()<< meta.Name;
			line->initFromProjectMeta(meta);
			line->setFixedHeight(qGuiApp->primaryScreen()->availableSize().height() / 10);
			Container->addWidget(line);
			line->show();
			Container->resize(Container->width(), Container->height() + line->height());
		}
	}
	_Public virtual void resizeEvent(QResizeEvent* event) {
		ScrollArea->setGeometry(0, 0, width(), height());
		Container->resize(width(), Container->height());
	}
};

class StoryStudioPublicAPI ProjectInfoWidget :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
};