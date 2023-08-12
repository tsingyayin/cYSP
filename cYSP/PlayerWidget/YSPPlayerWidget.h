#pragma once
#include <VICore>
#include <VIWidgets>
#include <SPDF>
#include "YSPPlayerView.h"
#include "YSPStoryLogWidget.h"

class YSPPlayerTerminal;
class YSPPlayerWidget :public VIWidget
{
	Q_OBJECT;
	VI_OBJECT;
	_Public YSPPlayerView* PlayerView;
	_Public YSPPlayerTerminal* PlayerTerminal;
	_Public YSPStoryLogWidget* StoryLogWidget;
	_Public def_init YSPPlayerWidget(QWidget* parent = VI_NULL);
	_Public void resizeEvent(QResizeEvent* event)override;
};

class YSPPlayerTerminal :public SPDFAbstractTerminal
{
	Q_OBJECT;
	VI_OBJECT;
	_Public YSPPlayerWidget* PlayerWidget;
	_Public def_init YSPPlayerTerminal(YSPPlayerWidget* widget);
	_Slot virtual void onSPOLDocumentChanged(const QStringList& spol, SPDF::SPOLExecutionMode mode) override;
	_Slot virtual void onSceneFinished(SPDF::SPOLExecutionMode mode) override;
	_Slot virtual void onControllers(SPDFBottomInterfaceList* list, SPDF::SPOLExecutionMode mode) override;
	_Public void onSpeaking(SPDFBottomInterface* data, SPDF::SPOLExecutionMode mode);
	_Public void onChara(SPDFBottomInterface* data, SPDF::SPOLExecutionMode mode);
	_Public void onBackground(SPDFBottomInterface* data, SPDF::SPOLExecutionMode mode);
};