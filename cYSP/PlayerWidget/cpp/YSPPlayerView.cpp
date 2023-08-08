#include "../YSPPlayerView.h"

def_init YSPPlayerView::YSPPlayerView(QWidget* parent) :QGraphicsView(parent) {
	this->Scene = new QGraphicsScene(this);
	this->setScene(this->Scene);
	this->Background = new YSPPlayerBackground();
	this->Scene->addWidget(this->Background);
	// close scroll bar
	this->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
	this->show();
}

void YSPPlayerView::resizeEvent(QResizeEvent* event) {
	this->Background->resize(this->size());
	
}