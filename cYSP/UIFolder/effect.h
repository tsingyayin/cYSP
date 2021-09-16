#pragma once
#include <QtWidgets>
#include <QtCore>
#include <QtGui>
#include <math.h>
#include "..\global_value.h"

class ShakeFunc :public QThread
{
	Q_OBJECT
	signals:
		void shakeXY(int, int, int);
	public:
		float gSpeed;
		ShakeFunc(float SpeedNow) {
			gSpeed = SpeedNow;
		}
		void run(void) {
			for (int i = 0; i < 10; i++) {
				int a = randint(-10, 10);
				int b = randint(-10, 10);
				emit shakeXY(a, b, 0);
				Sleep(20 * gSpeed);
			}
			emit shakeXY(0, 0, 1);
			this->deleteLater();
			this->quit();
		}
};

class FlashFuncFast :public QThread
{
	Q_OBJECT
	signals:
		void FlashOPint(float, int);
	public:
		float gSpeed;
		FlashFuncFast(float SpeedNow) {
			gSpeed = SpeedNow;
		}
		void run(void) {
			emit FlashOPint(0, 0);
			for (int i = 0; i < 20; i++) {
				float a = sin(i * 0.157);
				emit FlashOPint(a, 1);
				Sleep(20 * gSpeed);
			}
			emit FlashOPint(0, 2);
			this->deleteLater();
			this->quit();
		}
};

class FlashFuncSlow :public QThread
{
	Q_OBJECT
signals:
	void FlashOPint(float, int);
public:
	float gSpeed;
	FlashFuncSlow(float SpeedNow) {
		gSpeed = SpeedNow;
	}
	void run(void) {
		emit FlashOPint(0, 0);
		for (int i = 0; i < 40; i++) {
			float a = sin(i * 0.0785);
			emit FlashOPint(a, 1);
			Sleep(20 * gSpeed);
		}
		emit FlashOPint(0, 2);
		this->deleteLater();
		this->quit();
	}
};