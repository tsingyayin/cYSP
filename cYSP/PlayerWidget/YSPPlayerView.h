#pragma once
#include <VICore>
#include <VIWidgets>
#include <SPDF>
#include "YSPPlayerObjectAnimations.h"
#include "YSPRenderThread.h"

class YSPPlayerBackground :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public VILabel* Background_Top;
	_Public VILabel* Background_Bottom;
	_Public QGraphicsOpacityEffect* OPEffect;
	_Public bool BackgroundState = false;
	_Public YSPPlayerBackgroundChangeAnimation* ChangeBackgroundAnimation;
	_Public def_init YSPPlayerBackground(QWidget* parent = VI_NULL);
	_Public void changeBackground(QImage image, VIMilliSecond duration);
	_Public void resizeEvent(QResizeEvent* event)override;
};
class YSPPlayerView :public QGraphicsView, VIBaseObject
{
	Q_OBJECT;
	VI_WIDGET;
	_Public QGraphicsScene* Scene;
	_Public YSPRenderThread* RenderThread = VI_NULL;
	_Public YSPPlayerBackground* Background;
	_Public QImage CurrentImage;
	_Public def_init YSPPlayerView(QWidget* parent = VI_NULL);
	_Public void resizeEvent(QResizeEvent* event)override;
	_Slot void renderImage();
};
