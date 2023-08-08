#include "../YSPPlayerObjectAnimations.h"
#include "../YSPPlayerView.h"

def_init YSPPlayerBackground::YSPPlayerBackground(QWidget* parent):VIWidget(parent) {
	this->Background_Top = new VILabel(this);
	this->Background_Bottom = new VILabel(this);
	OPEffect = new QGraphicsOpacityEffect(this);
	Background_Top->setGraphicsEffect(OPEffect);
	ChangeBackgroundAnimation = new YSPPlayerBackgroundChangeAnimation(this);
	ChangeBackgroundAnimation->setBackground(this);
	this->show();
}
void YSPPlayerBackground::changeBackground(QImage image, VIMilliSecond second) {
	ChangeBackgroundAnimation->setBackgroundImage(image);
	ChangeBackgroundAnimation->setDuration(second);
	ChangeBackgroundAnimation->active();
}
void YSPPlayerBackground::resizeEvent(QResizeEvent* event) {
	Background_Top->resize(this->size());
	Background_Bottom->resize(this->size());
}
def_init YSPPlayerBackgroundChangeAnimation::YSPPlayerBackgroundChangeAnimation(VISuper* parent) :VIAnimationBehavior(parent) {
	this->Background = VI_NULL;
}
void YSPPlayerBackgroundChangeAnimation::setBackground(YSPPlayerBackground* background) {
	this->Background = background;
	this->Background->BackgroundState = false;
	this->Background->OPEffect->setOpacity(1.0);
}
void YSPPlayerBackgroundChangeAnimation::setBackgroundImage(QImage image) {
	this->Image = image;
}
void YSPPlayerBackgroundChangeAnimation::onActive() {
	if (this->Background->BackgroundState) {
		this->Background->Background_Top->setPixmap(QPixmap::fromImage(Image));
	}
	else {
		this->Background->Background_Bottom->setPixmap(QPixmap::fromImage(Image));
	}
}
void YSPPlayerBackgroundChangeAnimation::onTick() {
	if (this->Background->BackgroundState) {
		this->Background->OPEffect->setOpacity(this->Duration->getPercent());
	}
	else {
		this->Background->OPEffect->setOpacity(1.0 - this->Duration->getPercent());
	}
}
void YSPPlayerBackgroundChangeAnimation::onSubside() {
	if (this->Background->BackgroundState) {
		this->Background->OPEffect->setOpacity(1.0);
	}
	else {
		this->Background->OPEffect->setOpacity(0.0);
	}
	this->Background->BackgroundState = !this->Background->BackgroundState;
}

