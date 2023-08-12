#pragma once
#include <VIWidgets>

class YSPHomeWidget :public VIWidget
{
	Q_OBJECT;
	VI_WIDGET;
	_Public def_init YSPHomeWidget(QWidget* parent = nullptr):VIWidget(parent) {
		setObjectName("YSPHomeWidget");
		setStyleSheet("background-color:rgb(255,255,255);");
	}
};

