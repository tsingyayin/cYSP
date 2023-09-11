#pragma once
#include <VICore>
#include <VIWidgets>
#include <YSPCore>
#include "../StoryStudio/StoryStudioPackageMeta.h"

class StoryStudioPublicAPI ProjectActionLine :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Signal void clicked();
	_Public VILabel* Icon;
	_Public VILabel* Title;
	_Public VILabel* SubText;
	_Public QGridLayout* CurrentLayout;
	_Public def_init ProjectActionLine(QWidget* parent = VI_NULL) :VIWidget(parent) {
		CurrentLayout = new QGridLayout(this);
		Icon = new VILabel(this);
		Icon->setScaledContents(true);
		Title = new VILabel(this);
		Title->setObjectName("Title");
		SubText = new VILabel(this);
		SubText->setObjectName("SubText");
		SubText->setWordWrap(true);
		CurrentLayout->addWidget(Icon, 0, 0, 2, 1);
		CurrentLayout->addWidget(Title, 0, 1, 1, 1);
		CurrentLayout->addWidget(SubText, 1, 1, 1, 1);
		CurrentLayout->setSpacing(2);
		this->setFixedHeight(qMax(qGuiApp->primaryScreen()->availableSize().height() / 10, 108));
		this->setVIDStyleSheet("normal", "\
			QWidget{color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Text) + "_CLR;}\
			VIWidget{background-color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Background) + "_CLR;\
				border:0px solid white;border-radius:10px;\
			}\
			VILabel#Title{font-size:APR_30_PR;}\
			VILabel#SubText{font-size:APR_15_PR;}\
			");
		this->applyVIDSS("normal");
		this->setVIDStyleSheet("hover", "\
			QWidget{color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Text) + "_CLR;}\
			VIWidget{background-color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Hover) + "_CLR;\
				border:2px solid ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Foreground) + "_CLR;border-radius:10px;\
			}\
			VILabel#Title{font-size:APR_30_PR;}\
			VILabel#SubText{font-size:APR_15_PR;}\
			");
		this->setVIDStyleSheet("selected", "\
			QWidget{color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Text) + "_CLR;}\
			VIWidget{background-color:ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Selected) + "_CLR;\
				border:2px solid ACLR_" + VIPalette::getDefaultColorName(VIPalette::DefaultColorName::Foreground) + "_CLR;border-radius:10px;\
			}\
			VILabel#Title{font-size:APR_30_PR;}\
			VILabel#SubText{font-size:APR_15_PR;}\
			");
		this->applyVIDSS("normal");
		
	}
	_Public virtual void resizeEvent(QResizeEvent* event) override {
		this->refreshVIDStyleSheet();
		this->Icon->setFixedSize(this->height() *0.8, this->height() *0.8);
	}
	_Public virtual void enterEvent(QEvent* event) override {
		this->applyVIDSS("hover");
	}
	_Public virtual void leaveEvent(QEvent* event) override {
		this->applyVIDSS("normal");
	}
	_Public virtual void mousePressEvent(QMouseEvent* event) override {
		this->applyVIDSS("selected");
	}
	_Public virtual void mouseReleaseEvent(QMouseEvent* event) override {
		this->applyVIDSS("hover");
		emit clicked();
	}
};

class StoryStudioPublicAPI CreateNewProjectLine :public ProjectActionLine
{
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init CreateNewProjectLine(QWidget* parent = VI_NULL) :ProjectActionLine(parent) {
		this->Icon->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath()+"/resource/NewProjectIcon.png"));
		onTranslating();
	}
	_Public virtual void onTranslating() override{
		this->Title->setText(getTranslation("Project_ProjectAction_NewProject_Text"));
		this->SubText->setText(getTranslation("Project_ProjectAction_NewProject_SubText"));
	}
};

class StoryStudioPublicAPI CreateEgProjectLine :public ProjectActionLine
{
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init CreateEgProjectLine(QWidget* parent = VI_NULL) :ProjectActionLine(parent) {
		this->Icon->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/NewEgProjectIcon.png"));
		onTranslating();
	}
	_Public virtual void onTranslating() override {
		this->Title->setText(getTranslation("Project_ProjectAction_NewEgProject_Text"));
		this->SubText->setText(getTranslation("Project_ProjectAction_NewEgProject_SubText"));
	}
};

class StoryStudioPublicAPI OpenProjectLine :public ProjectActionLine
{
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init OpenProjectLine(QWidget* parent = VI_NULL) :ProjectActionLine(parent) {
		this->Icon->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/OpenProjectIcon.png"));
		onTranslating();
	}
	_Public virtual void onTranslating() override {
		this->Title->setText(getTranslation("Project_ProjectAction_OpenProject_Text"));
		this->SubText->setText(getTranslation("Project_ProjectAction_OpenProject_SubText"));
	}
};

class StoryStudioPublicAPI CloneProjectLine :public ProjectActionLine
{
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init CloneProjectLine(QWidget* parent = VI_NULL) :ProjectActionLine(parent) {
		this->Icon->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/CloneGitProjectIcon.png"));
		onTranslating();
	}
	_Public virtual void onTranslating() override {
		this->Title->setText(getTranslation("Project_ProjectAction_CloneProject_Text"));
		this->SubText->setText(getTranslation("Project_ProjectAction_CloneProject_SubText"));
	}
};

class StoryStudioPublicAPI StudioSettingsLine :public ProjectActionLine
{
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init StudioSettingsLine(QWidget* parent = VI_NULL) :ProjectActionLine(parent) {
		this->Icon->setPixmap(QPixmap(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/StudioSettingsIcon.png"));
		onTranslating();
	}
	_Public virtual void onTranslating() override {
		this->Title->setText(getTranslation("Project_ProjectAction_StudioSettings_Text"));
		this->SubText->setText(getTranslation("Project_ProjectAction_StudioSettings_SubText"));
	}
};