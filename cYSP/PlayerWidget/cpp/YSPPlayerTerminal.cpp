#include "../YSPPlayerWidget.h"
#include "../../cYSP/YSPImageResource.h"
#include "../YSPRenderThread.h"
def_init YSPPlayerTerminal::YSPPlayerTerminal(YSPPlayerWidget* parent) :SPDFAbstractTerminal(parent) {
	this->PlayerWidget = parent;
	connect(parent->PlayerView->Background->ChangeBackgroundAnimation, &VIAnimationBehavior::finished,
		this, &YSPPlayerTerminal::controllerFinishedListener);
	connect(YSPImageResource::getInstance(), &YSPImageResource::imageGenerated, this, &YSPPlayerTerminal::controllerHandled);
}
void YSPPlayerTerminal::onSPOLDocumentChanged(const QStringList& spol, SPDF::SPOLExecutionMode mode) {
	if (mode == SPDF::SPOLExecutionMode::Render) {
		if (PlayerWidget->PlayerView->RenderThread != VI_NULL) {
			PlayerWidget->PlayerView->RenderThread->setRenderFinished();
		}
		PlayerWidget->setFixedSize(1920, 1080);
		PlayerWidget->hide();
		PlayerWidget->PlayerView->RenderThread = new YSPRenderThread(PlayerWidget->PlayerView, this->Host->Scripts->Interpreter->getCurrentMetaName());
		VICoreFrame->getBehaviorHostInstance()->pauseQuantifyTickBehaviorHost();
		PlayerWidget->PlayerView->RenderThread->start();
	}
	controllerHandled();
}
void YSPPlayerTerminal::onSceneFinished(SPDF::SPOLExecutionMode mode) {
	if (mode == SPDF::SPOLExecutionMode::Preload) {
		YSPImageResource::getInstance()->generateTaskBegin();
	}
	else if (mode == SPDF::SPOLExecutionMode::Render) {
		PlayerWidget->PlayerView->RenderThread->setRenderFinished();
		VICoreFrame->getBehaviorHostInstance()->resumeQuantifyTickBehaviorHost();
		controllerHandled();
	}
	else {
		controllerHandled();
	}
}
void YSPPlayerTerminal::onControllers(SPDFBottomInterfaceList* list, SPDF::SPOLExecutionMode mode) {
	for (auto i = list->begin(); i != list->end(); i++) {
		if (i->MethodName == "YSP.10X.Speaking") {
			this->onSpeaking(i, mode);
		}
		else if (i->MethodName == "YSP.10X.Chara") {
			this->onChara(i, mode);
		}
		else if (i->MethodName == "YSP.10X.Background") {
			this->onBackground(i, mode);
		}
	}
}

void YSPPlayerTerminal::onSpeaking(SPDFBottomInterface* data, SPDF::SPOLExecutionMode mode) {
	switch (mode)
	{
	case SPDF::SPOLExecutionMode::SyntaxCheck:
		break;
	case SPDF::SPOLExecutionMode::Preload:
		break;
	case SPDF::SPOLExecutionMode::RunTime:
		break;
	default:
		break;
	}
}

void YSPPlayerTerminal::onChara(SPDFBottomInterface* data, SPDF::SPOLExecutionMode mode) {
	QString fileName = data->Parameters["FileName"].toString();
	QString fileNameSuffix = data->Parameters["FileNameSuffix"].toString();
	QString filterSuffix = data->Parameters["FilterSuffix"].toString();
	YSPFilterInfoList filterInfoList = YSPImageResource::getInstance()->spolFilterParser(filterSuffix);
	if (mode == SPDF::SPOLExecutionMode::Preload) {
		if (fileNameSuffix != "") {
			YSPImageResource::getInstance()->loadImage("chara/" + fileName + "_" + fileNameSuffix, filterInfoList);
		}
		else {
			YSPImageResource::getInstance()->loadImage("chara/" + fileName, filterInfoList);
		}
	}
}

void YSPPlayerTerminal::onBackground(SPDFBottomInterface* data, SPDF::SPOLExecutionMode mode) {
	QString fileName = data->Parameters["FileName"].toString();
	QString filterSuffix = data->Parameters["Filter"].toString();
	YSPFilterInfoList filterInfoList = YSPImageResource::getInstance()->spolFilterParser(filterSuffix);
	if (mode == SPDF::SPOLExecutionMode::Preload) {
		YSPImageResource::getInstance()->loadImage("background/" + fileName, filterInfoList);
		this->controllerFinishedListener();
	}
	else if (mode == SPDF::SPOLExecutionMode::RunTime || mode == SPDF::SPOLExecutionMode::Render) {
		this->PlayerWidget->PlayerView->Background->changeBackground(
			YSPImageResource::getInstance()->getImage("background/" + fileName, filterInfoList), 
			data->Parameters["FadeInTime"].toDouble()*1000
		);
	}
}