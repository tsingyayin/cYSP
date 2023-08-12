#include "../YSPPlayerWidget.h"
#include "../../SPDFYSP/SPDFYSP.h"
#include "../../cYSP/YSPImageResource.h"

def_init YSPPlayerWidget::YSPPlayerWidget(QWidget* parent) {
	this->PlayerView = new YSPPlayerView(this);
	this->PlayerTerminal = new YSPPlayerTerminal(this);
	SPDF::Package::getInstance()->attachNewHostToTerminal(this->PlayerTerminal);
	PlayerTerminal->Host->installParser(new YSP_10X::Speaking);
	PlayerTerminal->Host->installParser(new YSP_10X::Background);
	connect(PlayerTerminal->Host->Scripts, &SPDFScripts::finished, YSPImageResource::getInstance(), &YSPImageResource::clearCache);
	this->setMinimumSize(800, 600);
}

void YSPPlayerWidget::resizeEvent(QResizeEvent* event) {
	this->PlayerView->resize(this->size());
}