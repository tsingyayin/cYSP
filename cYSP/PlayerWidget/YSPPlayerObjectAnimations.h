#pragma once
#include <VICore>

class YSPPlayerBackground;
class YSPPlayerBackgroundChangeAnimation :public VIAnimationBehavior
{
	Q_OBJECT;
	VI_OBJECT;
	_Public YSPPlayerBackground* Background;
	_Public QImage Image;
	_Public def_init YSPPlayerBackgroundChangeAnimation(VISuper* parent = VI_NULL);
	_Public void setBackground(YSPPlayerBackground* background);
	_Public void setBackgroundImage(QImage image);
	_Public void onActive() override;
	_Public void onTick() override;
	_Public void onSubside() override;
};