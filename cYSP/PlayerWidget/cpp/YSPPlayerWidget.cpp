#include "../YSPPlayerWidget.h"
#include "../../SPDFYSP/SPDFYSP.h"

def_init YSPPlayerWidget::YSPPlayerWidget(QWidget* parent) {
	this->PlayerView = new YSPPlayerView(this);
	this->PlayerTerminal = new YSPPlayerTerminal(this);
	SPDF::Package::getInstance()->attachNewHostToTerminal(this->PlayerTerminal);
	PlayerTerminal->Host->installParser(new YSP_10X::Speaking);
	PlayerTerminal->Host->installParser(new YSP_10X::Background);
	PlayerTerminal->Host->exec("./spoltest.js");
	this->setMinimumSize(800, 600);
}

void YSPPlayerWidget::resizeEvent(QResizeEvent* event) {
	this->PlayerView->resize(this->size());
}