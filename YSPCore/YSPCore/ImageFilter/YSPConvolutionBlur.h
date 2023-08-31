#pragma once
#include <VICore>
#include "../YSPCorePackageMeta.h"
/*
* 此文件有较为详尽的注释，因为作者不知道完成这个玩意的时候是个什么精神状态
* 
*/

typedef uchar QARGB32_8;
typedef uint QARGB32_32;
class YSPConvolutionBlur;
class YSPCorePublicAPI YSPConvolutionBlurThread :public QThread
{
	Q_OBJECT;
	friend class YSPConvolutionBlur;
	_Private bool ConsiderAlpha;
	_Protected QImage* Raw;
	_Protected QImage* Target;
	_Private int D;
	_Private int R;
	_Private QARGB32_32* Buffer;
	_Private int x;
	_Private int y;
	_Private int xFirst;
	_Protected int yStep;
	_Protected int* Kernel1D;
	_Private QARGB32_32* PixelPointer;
	_Private QARGB32_32* TargetPixelPointer;
	_Private int r, g, b, a;
	_Protected def_init YSPConvolutionBlurThread(QImage* raw, QImage* target, int d, int start, int step, int* kernal1DInt, bool considerAlpha);
	_Public void run();
	_Public static void rgbaBound(int* value);
	_Public void blurIteratorFirstColumn();
	_Public void blurIterator();
	_Public void blurIteratorFirstColumnNoAlpha();
	_Public void blurIteratorNoAlpha();
	_Public def_del ~YSPConvolutionBlurThread();
};
class YSPCorePublicAPI YSPConvolutionBlur :public VIObject {
	_Public static void blur(QImage* raw, QImage* target, int d, bool considerAlpha = false);
};
