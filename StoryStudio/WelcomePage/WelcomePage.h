#pragma once
#include <VICore>
#include <VIWidgets>
#include <YSPCore>
#include "../StoryStudio/StoryStudioPackageMeta.h"

class StoryStudioPublicAPI WidgetFadeAnimation :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Private QGraphicsOpacityEffect* Effect;
	_Private QWidget* Target;
	_Private bool isFadeIn = true;
	_Public def_init WidgetFadeAnimation(QWidget* target) {
		this->Target = target;
		this->Effect = new QGraphicsOpacityEffect(this->Target);
		this->Effect->setOpacity(0);
		this->Target->setGraphicsEffect(this->Effect);
	}
	_Public void activeFadeInAnimation(VIMilliSecond duration) {
		this->setDuration(duration);
		this->Effect->setOpacity(0);
		this->isFadeIn = true;
		this->start();
	}
	_Public void activeFadeOutAnimation(VIMilliSecond duration) {
		this->setDuration(duration);
		this->Effect->setOpacity(1);
		this->isFadeIn = false;
		this->start();
	}
	_Public virtual void onStart() HalfVirtual;
	_Public virtual void onTick() {
		if (this->isFadeIn) {
			this->Effect->setOpacity(VICommonMapping::sin_0_1(this->Duration->getPercent()));
		}
		else {
			this->Effect->setOpacity(1 - VICommonMapping::sin_0_1(this->Duration->getPercent()));
		}
	}
	_Public virtual void onStop() {
		if (this->isFadeIn) {
			this->Effect->setOpacity(1);
		}
		else {
			this->Effect->setOpacity(0);
		}
		emit finished();
	}
};
class StoryStudioPublicAPI WelcomePage :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Signal void closed();
	_Public QFrame* MainFrame;
	_Public QLabel* Background;
	_Public QLabel* Text;
	_Public QGridLayout* MainLayout;
	_Public WidgetFadeAnimation* FadeAnimation;
	_Public def_init WelcomePage() {
		StoryStudio::PackageMeta::getInstance()->addTranslatableObject(this);
		QSize size = QGuiApplication::primaryScreen()->size();
		this->setFixedSize(size.height() , size.height() / 2);
		this->setWindowFlags(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);

		MainFrame = new QFrame(this);
		MainLayout = new QGridLayout(MainFrame);
		Background = new QLabel(MainFrame);
		Background->setScaledContents(true);
		Background->setAlignment(Qt::AlignCenter);
		MainLayout->addWidget(Background);
		Text = new QLabel(MainFrame);
		FadeAnimation = new WidgetFadeAnimation(this);
		connect(FadeAnimation, &WidgetFadeAnimation::finished, this, &WelcomePage::onAnimationEnd);

		onTranslating();
	}
	_Public virtual void onTranslating() override {
		this->setWindowTitle(getTranslation("Welcome_Window_Title_Text"));
	}
	_Public virtual void resizeEvent(QResizeEvent* event) override {
		MainFrame->resize(this->width(), this->height());
		MainFrame->setStyleSheet("QFrame{background-color:#00CACEFF;border-radius:10px}");
		Background->setStyleSheet("QLabel{border-image:url("+ StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() +"/resource/YayinStoryStudio.png);border:0px solid black; border-radius:10px}");
		Text->setStyleSheet("QLabel{color:#FFFFFF;font-size:20px;font-family:Microsoft YaHei;background-color:#00FFFFFF}");
	}
	_Public void onAnimationEnd() {
		QTimer::singleShot(1500, this, &WelcomePage::close);
	}
	_Public virtual void showEvent(QShowEvent* event) override {
		FadeAnimation->activeFadeInAnimation(500);
	}
	_Public virtual void closeEvent(QCloseEvent* event) override {
		emit closed();
	}
};