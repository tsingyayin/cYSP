#pragma once
#include "ProjectActionUnit.h"

class StoryStudioPublicAPI ProjectLine :public VIAbstractRatioWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VILabel* TypeLabel;
	_Public VILabel* ThemeLabel;
	_Public VILabel* ProjectNameLabel;
	_Public VILabel* ProjectOpenedTimeLabel;
	_Public VILabel* ProjectDirLabel;
	_Public QGridLayout* CurrentLayout;
	_Public YSPProjectConfig::MetaInfo Meta;
	_Public def_init ProjectLine(QWidget* parent = VI_NULL) :VIAbstractRatioWidget(parent) {
		Meta = YSPProjectConfig::MetaInfo();
		setFixedHeight(qMax(qGuiApp->primaryScreen()->availableSize().height() / 12, 90));
		TypeLabel = new VILabel(this);
		ThemeLabel = new VILabel(this);
		TypeLabel->setScaledContents(true);
		ThemeLabel->setScaledContents(true);
		ProjectNameLabel = new VILabel(this);
		ProjectNameLabel->setObjectName("ProjectNameLabel");
		ProjectNameLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
		ProjectOpenedTimeLabel = new VILabel(this);
		ProjectOpenedTimeLabel->setObjectName("ProjectOpenedTimeLabel");
		ProjectOpenedTimeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		ProjectDirLabel = new VILabel(this);
		ProjectDirLabel->setObjectName("ProjectDirLabel");
		ProjectDirLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->addWidget(TypeLabel, 0, 0, 2, 1);
		CurrentLayout->addWidget(ThemeLabel, 0, 1, 2, 1);
		CurrentLayout->addWidget(ProjectNameLabel, 0, 2, 1, 1);
		CurrentLayout->addWidget(ProjectOpenedTimeLabel, 0, 3, 1, 1);
		CurrentLayout->addWidget(ProjectDirLabel, 1, 2, 1, 2);
		CurrentLayout->setSpacing(2);
		/*TypeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
		ThemeLabel->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);*/
		

		this->setVIDStyleSheet("normal", "\
			QWidget{color:ACLR_"+VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Text) + "_CLR;}\
			VIWidget{background-color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Background) + "_CLR;\
				border:0px solid white;border-radius:10px;\
			}\
			VILabel#ProjectNameLabel{font-size:APR_30_PR;}\
			VILabel#ProjectOpenedTimeLabel{font-size:APR_20_PR;}\
			VILabel#ProjectDirLabel{font-size:APR_20_PR;}\
			");
		this->applyVIDSS("normal");
		this->setVIDStyleSheet("hover", "\
			QWidget{color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Text) + "_CLR;}\
			VIWidget{background-color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Hover) + "_CLR;\
				border:2px solid ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Foreground) + "_CLR;border-radius:10px;\
			}\
			VILabel#ProjectNameLabel{font-size:APR_30_PR;}\
			VILabel#ProjectOpenedTimeLabel{font-size:APR_20_PR;}\
			VILabel#ProjectDirLabel{font-size:APR_20_PR;}\
			");
		this->setVIDStyleSheet("selected", "\
			QWidget{color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Text) + "_CLR;}\
			VIWidget{background-color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Selected) + "_CLR;\
				border:2px solid ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Foreground) + "_CLR;border-radius:10px;\
			}\
			VILabel#ProjectNameLabel{font-size:APR_30_PR;}\
			VILabel#ProjectOpenedTimeLabel{font-size:APR_20_PR;}\
			VILabel#ProjectDirLabel{font-size:APR_20_PR;}\
			");
	}
	_Public void initFromProjectMeta(YSPProjectConfig::MetaInfo& meta) {
		Meta = meta;
		TypeLabel->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath()+"/resource/Player2DIcon.png"));
		ThemeLabel->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/ArknightsThemeIcon.png"));
		ProjectNameLabel->setText(meta.Name);
		ProjectOpenedTimeLabel->setText(meta.LastOpened);
		ProjectDirLabel->setText(meta.ProjectPath);
	}
	_Public void resizeEvent(QResizeEvent* event) {
		TypeLabel->setFixedSize(this->height()-22, this->height()-22);
		ThemeLabel->setFixedSize(this->height()-22, this->height()-22);
		this->refreshVIDStyleSheet();
	}
};

class StoryStudioPublicAPI ProjectList :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Signal void projectSelected(ProjectLine*);
	_Public VIRatioWidgetContainer* Container;
	_Public QScrollArea* ScrollArea;
	_Private bool isInit = false;
	_Public def_init ProjectList(QWidget* parent = VI_NULL):VIWidget(parent) {
		ScrollArea = new QScrollArea(this);
		Container = new VIRatioWidgetContainer(Qt::Vertical, ScrollArea);
		ScrollArea->setWidget(Container);
		ScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		ScrollArea->setStyleSheet("QScrollArea{border:0px solid white;}");
		connect(Container, &VIRatioWidgetContainer::selectWidgetChanged, this, &ProjectList::onSelectProjectChanged);
	}
	_Public virtual void onSelectProjectChanged(VIAbstractRatioWidget* widget) {
		if (!isInit) { return; }
		emit projectSelected((ProjectLine*)widget);
	}
	_Public void initProjects() {
		QStringList projects = YSPResourceManager::getAllEffectiveProjectPath();
		ProjectLine* firstLine = VI_NULL;
		for (auto i = projects.begin(); i != projects.end(); i++) {
			YSPProjectConfig::MetaInfo meta = YSPProject::getMetaInfoInFolder(*i);
			ProjectLine* line = new ProjectLine(Container);
			if (firstLine == VI_NULL) { firstLine = line; }
			line->initFromProjectMeta(meta);
			Container->addWidget(line);
			line->show();
			Container->resize(Container->width(), Container->height() + line->height());
		}
		isInit = true;
		if (firstLine != VI_NULL) {
			firstLine->select();
			//emit projectSelected(firstLine);
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
	_Public VILabel* Title;
	_Public VILabel* Cover;
	_Public VILabel* CountInfo;
	_Public VILabel* Type;
	_Public VILabel* Theme;
	_Public VILabel* SPDF_SPOLVersion;
	_Public VILabel* ProgramVersion;
	_Public VILabel* Author;
	_Public VILabel* Description;
	_Public VIPushButton* OpenButton;
	_Public VIPushButton* OpenDirButton;
	_Public QGridLayout* CurrentLayout;
	_Public YSPProjectConfig::MetaInfo* Meta = VI_NULL;
	_Public def_init ProjectInfoWidget(QWidget* parent = VI_NULL) :VIWidget(parent) {
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->setSpacing(7);
		CurrentLayout->setContentsMargins(33, 11, 33, 11);
		Title = new VILabel(this);
		Title->setObjectName("Title");
		Cover = new VILabel(this);
		Cover->setObjectName("Cover");
		Cover->setScaledContents(true);
		Cover->setStyleSheet("VILabel#Cover{border-radius:10px;background-color:#000000;color:#FFFFFF;border-image:url();}");
		Cover->setAlignment(Qt::AlignCenter);
		CountInfo = new VILabel(this);
		Type = new VILabel(this);
		Theme = new VILabel(this);
		SPDF_SPOLVersion = new VILabel(this);
		ProgramVersion = new VILabel(this);
		Author = new VILabel(this);
		Description = new VILabel(this);
		OpenButton = new VIPushButton(this);
		OpenDirButton = new VIPushButton(this);
		OpenButton->hide();
		OpenDirButton->hide();
		connect(OpenDirButton, &VIPushButton::clicked, this, &ProjectInfoWidget::onOpenDirButtonClicked);
		CurrentLayout->addWidget(Title, 0, 0, 1, 3);
		CurrentLayout->addWidget(Cover, 1, 0, 3, 1);
		CurrentLayout->addWidget(CountInfo, 4, 0, 1, 2);

		CurrentLayout->addWidget(Type, 1, 1, 1, 1);
		CurrentLayout->addWidget(Theme, 2, 1, 1, 1);
		CurrentLayout->addWidget(ProgramVersion, 3, 1, 1, 1);

		CurrentLayout->addWidget(Author, 1, 2, 1, 1);
		CurrentLayout->addWidget(Description, 2, 2, 2, 1);
		CurrentLayout->addWidget(SPDF_SPOLVersion, 4, 2, 1, 2);

		CurrentLayout->addWidget(OpenButton, 1, 4, 1, 1);
		CurrentLayout->addWidget(OpenDirButton, 2, 4, 1, 1);
		this->setVIDStyleSheet("default", "\
			QWidget{background-color:ACLR_"+VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Background) + "_CLR;}\
			VILabel{font-size:APR_8_PR;}\
			VILabel#Title{font-size:APR_15_PR;}\
			");
		this->applyVIDSS("default");
		onTranslating();
	}
	_Public void onOpenDirButtonClicked() {
		VIPathInfo::openExplorer(Meta->ProjectPath);
	}
	_Public void refreshWithProjectMeta(YSPProjectConfig::MetaInfo* info) {
		Meta = info;
		onTranslating();
		OpenButton->show();
		OpenDirButton->show();
	}
	_Public virtual void resizeEvent(QResizeEvent* e) override {
		this->refreshVIDStyleSheet();
		Cover->setFixedSize(this->height() * 0.5 / 9 * 16, this->height() * 0.5);
	}
	_Public virtual void onTranslating() override {
		OpenButton->setText(getTranslation("Project_MetaInfo_OpenButton_Text"));
		OpenDirButton->setText(getTranslation("Project_MetaInfo_OpenDirButton_Text"));
		if (Meta == VI_NULL) {
			Title->setText(getTranslation("Project_MetaInfo_Title_Text").arg(getTranslation("Project_MetaInfo_Title_Select")));
			CountInfo->setText(getTranslation("Project_MetaInfo_CountInfo_Text").arg( "——", "——"));
			Type->setText(getTranslation("Project_MetaInfo_Type_Text").arg("——"));
			Theme->setText(getTranslation("Project_MetaInfo_Theme_Text").arg("——"));
			SPDF_SPOLVersion->setText(getTranslation("Project_MetaInfo_SPDFSPOLVersion_Text").arg("——", "——"));
			ProgramVersion->setText(getTranslation("Project_MetaInfo_ProgramVersion_Text").arg("——"));
			Author->setText(getTranslation("Project_MetaInfo_Author_Text").arg("——"));
			Description->setText(getTranslation("Project_MetaInfo_Description_Text").arg("——"));
		}
		else {
			Title->setText(getTranslation("Project_MetaInfo_Title_Text").arg(Meta->Name));
			QFile file(Meta->ProjectPath+"/cover.png");
			Cover->clear();
			if (file.exists()) {
				Cover->setStyleSheet("VILabel{border-radius:10px;color:#FFFFFF;border-image:url(" + Meta->ProjectPath + "/cover.png);}");
			}
			else {
				Cover->setStyleSheet("VILabel{border-radius:10px;background-color:#000000;color:#FFFFFF;border-image:url();}");
				Cover->setText(getTranslation("Project_MetaInfo_Cover_None"));
			}
			CountInfo->setText(getTranslation("Project_MetaInfo_CountInfo_Text").arg(Meta->SizeCount, Meta->CacheSizeCount));
			Type->setText(getTranslation("Project_MetaInfo_Type_Text").arg(Meta->Type));
			Theme->setText(getTranslation("Project_MetaInfo_Theme_Text").arg(Meta->Theme));
			SPDF_SPOLVersion->setText(getTranslation("Project_MetaInfo_SPDFSPOLVersion_Text").arg(Meta->SPDFVersion, Meta->SPOLVersion));
			ProgramVersion->setText(getTranslation("Project_MetaInfo_ProgramVersion_Text").arg(Meta->ProgramVersion));
			Author->setText(getTranslation("Project_MetaInfo_Author_Text").arg(Meta->Author));
			Description->setText(getTranslation("Project_MetaInfo_Description_Text").arg(Meta->Description));
		}
	}
};

class StoryStudioPublicAPI QuickActionsWidget :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public CreateNewProjectLine* NewLine;
	_Public CreateEgProjectLine* EgLine;
	_Public OpenProjectLine* OpenLine;
	_Public CloneProjectLine* CloneLine;
	_Public StudioSettingsLine* SettingsLine;
	_Public QGridLayout* CurrentLayout;
	_Public def_init QuickActionsWidget(QWidget* parent = VI_NULL) :VIWidget(parent) {
		NewLine = new CreateNewProjectLine(this);
		EgLine = new CreateEgProjectLine(this);
		OpenLine = new OpenProjectLine(this);
		CloneLine = new CloneProjectLine(this);
		SettingsLine = new StudioSettingsLine(this);
		CurrentLayout = new QGridLayout(this);
		CurrentLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 0, 0, 1, 1);
		CurrentLayout->addWidget(NewLine, 1, 0, 1, 1);
		CurrentLayout->addWidget(EgLine, 2, 0, 1, 1);
		CurrentLayout->addWidget(OpenLine, 3, 0, 1, 1);
		CurrentLayout->addWidget(CloneLine, 4, 0, 1, 1);
		CurrentLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 5, 0, 1, 1);
		CurrentLayout->addWidget(SettingsLine, 6, 0, 1, 1);
		CurrentLayout->addItem(new QSpacerItem(0, 0, QSizePolicy::Expanding, QSizePolicy::Expanding), 7, 0, 1, 1);
		this->setVIDStyleSheet("default", "\
			QuickActionsWidget{background-color:ACLR_"+VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Selected) + "_CLR;}\
			");
		this->applyVIDSS("default");
	}
};