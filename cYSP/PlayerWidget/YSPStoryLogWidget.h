#pragma once
#include <VIWidgets>

class YSPStoryLogWidget :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VIWidget* LogPad;
	_Public VIPushButton* CloseButton;
};