#pragma once
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <algorithm>
#include "..\langcontrol.h"
#include "..\global_value.h"
using namespace std;

void GradientMask(float y, float Y, int* r, int* g, int* b) {
	if (0 < y && y < Y / 3) {
		*r = 0;
		*g = 0;
		*b = 0;
	}
	else if (Y / 3 <= y && y <= 2 * Y / 3) {
		*r = *r * ((y - Y / 3) / (Y / 3));
		*g = *g * ((y - Y / 3) / (Y / 3));
		*b = *b * ((y - Y / 3) / (Y / 3));
	}
}

void BlackSilhouette(int* r, int* g, int* b) {
	*r = 0;
	*g = 0;
	*b = 0;
}

void Fade(int* r, int* g, int* b) {
	double Max = max(max(*r, *g), *b);
	double Min = min(min(*r, *g), *b);
	double ir = *r, ig = *g, ib = *b;
	double delta = (Max - Min) / 255;
	double value = (Max + Min) / 255;
	double L = value / 2;
	double S, alpha;
	if (L <= 0.5) {
		if (value != 0) {
			S = delta / value;
		}else {
			S = delta / 0.0000000000001;
		}
	}else {
		if (2 - value != 0) {
			S = delta / (2 - value);
		}else {
			S = delta / 0.0000000000001;
		}
	}
	if (S - 1 >= 1) { alpha = S; }
	else { alpha = 2; }
	alpha = 1 / alpha - 1;

	*r = (int)(L * 255 + (ir - L * 255) * (1 + alpha)) * 0.75;
	*g = (int)(L * 255 + (ig - L * 255) * (1 + alpha)) * 0.8;
	*b = (int)(L * 255 + (ib - L * 255) * (1 + alpha)) * 0.8;
}

void OnlyBW(int* r, int* g, int* b) {
	*r = *g = *b = (int)((*r + *g + *b) / 3);
}

void ReverseColor(int* r, int* g, int* b) {
	*r = 255 - *r;
	*g = 255 - *g;
	*b = 255 - *b;
}

void TurnDark(int* r, int* g, int* b) {
	*r = *r * 0.6;
	*g = *g * 0.6;
	*b = *b * 0.6;
}

void GaussianBlur5(int* r, int* g, int* b, QList<QList<int>> ColorMatrix) {
	
}

void GaussianBlur11(int* r, int* g, int* b, QList<QList<int>> ColorMatrix) {

}

enum Filter {
	unknownFilter = 0,
	gradientMask = 1,
	blackSilhouette = 2,
	fade = 3,
	onlyBW = 4,
	reverseColor = 5,
	turnDark = 6,
	gaussianBlur5 = 7,
	gaussianBlur11 = 8,
};

void transformation(Filter whichFilter = Filter::unknownFilter, int* r = NULL, int* g = NULL, int* b = NULL, int* a = NULL, int y = NULL, int Y = NULL, QList<QList<int>> ColorMatrix = {} ) {
	switch (whichFilter) {
	case unknownFilter:
		break;
	case gradientMask:
		GradientMask(y, Y, r, g, b);
		break;
	case blackSilhouette:
		BlackSilhouette(r, g, b);
		break;
	case fade:
		Fade(r, g, b);
		break;
	case onlyBW:
		OnlyBW(r, g, b);
		break;
	case reverseColor:
		ReverseColor(r, g, b);
		break;
	case turnDark:
		TurnDark(r, g, b);
		break;
	case gaussianBlur5:
		GaussianBlur5(r, g, b, ColorMatrix);
		break;
	case gaussianBlur11:
		GaussianBlur11(r, g, b, ColorMatrix);
		break;
	}
}

