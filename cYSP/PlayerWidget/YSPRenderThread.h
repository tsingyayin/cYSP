#pragma once
#include <VICore>
#include "../../cYSP/cYSPOpenCVAPI.h"

class YSPPlayerView;
class YSPRenderThread :public QThread
{
	Q_OBJECT;
	_Public YSPPlayerView* PlayerView;
	_Private bool RenderFinished = false;
	_Public static QMutex Mutex;
	_Public int Width = 0;
	_Public int Height = 0;
	_Public QString FileName;
	_Public cv::VideoWriter writer;
	_Signal void onRender();
	_Signal void manualTickNextFrame(Visindigo::QuantifyTickType, int);
	_Public bool renderFinished();
	_Public void setRenderFinished();
	_Public def_init YSPRenderThread(YSPPlayerView* view, QString fileName);
	_Public def_del ~YSPRenderThread();
	_Public void run()override;
};