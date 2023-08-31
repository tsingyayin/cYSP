#pragma once
#include "YSPConvolutionBlur.h"
/*
ImageFilter
此文件是YSP的core_B.h文件的精神续作
精神续作：指除了干一样的活之外就没一样的玩意
*/
class YSPCorePublicAPI YSPImageFilter : public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_STATIC_CLASS(YSPImageFilter);
	_Public enum class FilterName {
		unknown = 0,
		topFadeCover = 1,
		blackCover = 2,
		changeSaturation = 3,
		grayScale = 4,
		reverse = 5,
		changeLightness = 6,
		mirror = 7,
		gaussianBlur = 8,
		edgeExtension = 9,
	};
	_Public static void filterOperation(FilterName name, QImage& rawImage, float p_a = 0, float p_b = 0, float p_c = 0, float p_d = 0);
	_Public static void topFadeCover(QImage* image, float endP);
	_Public static void grayScale(QImage* image);
	_Public static void blackCover(QImage* image);
	_Public static void changeSaturation(QImage* image, float saturation);
	_Public static void changeLightness(QImage* image, float lightness);
	_Public static void mirror(QImage* image, float direction);
	_Public static void gaussianBlur(QImage* image, int d, bool considerAlpha = false);
	_Public static void edgeExtension(QImage* image, int d);
	_Private static QImage* _edgeExtension(QImage* image, int d);
	_Public static void reverse(QImage* image);
};