#pragma once
#include <QtCore>
#include "GPOLPointer.h"
class GPOLBaseSignal :public QObject
{
	Q_OBJECT
signals:
	void PlayerSignal(QStringList, QStringList);
public:
	GPOLBaseSignal(QObject* parent = Q_NULLPTR) {
		this->setParent(parent);
		connect(this, SIGNAL(PlayerSignal(QStringList, QStringList)), GPointer::PlayerPage, SLOT(GPSignalSlot(QStringList, QStringList)), Qt::BlockingQueuedConnection);
	}
	~GPOLBaseSignal() {
		this->disconnect();
	}
};