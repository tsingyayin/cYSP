#pragma once
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <iostream>
#include <algorithm>

using namespace std;

void GradientMask(int y, int Y, int* r, int* g, int* b) {
	*r = *r * ((y - Y / 3) / (Y / 3));
	*g = *g * ((y - Y / 3) / (Y / 3));
	*b = *b * ((y - Y / 3) / (Y / 3));
}

void BlackSilhouette(int* r, int* g, int* b) {
	*r = 0;
	*g = 0;
	*b = 0;
}

void Fade(int* r, int* g, int* b) {
	int Max = max(max(*r, *g), *b);
	int Min = min(min(*r, *g), *b);
	float delta = (Max - Min) / 255;
	float value = (Max + Min) / 255;
	float L = value / 2;
	float S, alpha;
	if (L <= 0.5) {
		if (value != 0) {
			S = delta / value;
		}
		else {
			S = delta / 0.00001;
		}
	}
	else {
		if (2 - value != 0) {
			S = delta / (2 - value);
		}
		else {
			S = delta / 0.00001;
		}
	}
	if (S - 1 >= 1) { alpha = S; }
	else { alpha = 2; }
	alpha = 1 / alpha - 1;

	*r = (int)(L * 255 + (*r - L * 255) * (1 + alpha)) * 0.75;
	*g = (int)(L * 255 + (*g - L * 255) * (1 + alpha)) * 0.8;
	*b = (int)(L * 255 + (*b - L * 255) * (1 + alpha)) * 0.8;
}

void OnlyBW(int* r, int* g, int* b) {
	*r = *g = *b = (int)((*r + *g + *b) / 3);
}

void ReverseColor(int* r, int* g, int* b) {
	*r = 255 - *r;
	*g = 255 - *g;
	*b = 255 - *b;
}

enum Filter {
	unknownFilter = 0,
	gradientMask = 1,
	blackSilhouette = 2,
	fade = 3,
	onlyBW = 4,
	reverseColor = 5,
};

void transformation(Filter whichFilter = Filter::unknownFilter, int* r = NULL, int* g = NULL, int* b = NULL, int* a = NULL, int* y = NULL, int* Y = NULL) {
	switch (whichFilter) {
	case unknownFilter:
		break;
	case gradientMask:
		GradientMask(*y, *Y, r, g, b);
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
	}
}


