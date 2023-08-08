#include "../YSPPlayerWidget.h"
#include "../../cYSP/YSPImageResource.h"

def_init YSPPlayerTerminal::YSPPlayerTerminal(YSPPlayerWidget* parent) :SPDFAbstractTerminal(parent) {
	connect(parent->PlayerView->Background->ChangeBackgroundAnimation, &VIAnimationBehavior::finished,
		this, &YSPPlayerTerminal::controllerFinishedListener);
}
void YSPPlayerTerminal::onSPOLDocumentChanged(const QStringList& spol, SPDF::SPOLExecutionMode mode) {
	
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
	if (fileNameSuffix != "") {
		QImage image = YSPImageResource::getInstance()->getImage("chara/" + fileName + "_" + fileNameSuffix, filterInfoList);
	}
	else {
		QImage image = YSPImageResource::getInstance()->getImage("chara/" + fileName, filterInfoList);
	}
	if (mode == SPDF::SPOLExecutionMode::Preload) {
		
	}
}

void YSPPlayerTerminal::onBackground(SPDFBottomInterface* data, SPDF::SPOLExecutionMode mode) {
	QString fileName = data->Parameters["FileName"].toString();
	QString filterSuffix = data->Parameters["Filter"].toString();
	YSPFilterInfoList filterInfoList = YSPImageResource::getInstance()->spolFilterParser(filterSuffix);
	QImage image = YSPImageResource::getInstance()->getImage("background/" + fileName , filterInfoList);
	if (mode == SPDF::SPOLExecutionMode::Preload) {
		this->controllerFinishedListener();
	}
}