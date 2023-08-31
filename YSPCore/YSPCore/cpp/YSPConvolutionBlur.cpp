#include "../ImageFilter/YSPConvolutionBlur.h"

/*
* 此文件有较为详尽的注释，因为作者不知道完成这个玩意的时候是个什么精神状态
*
*/


def_init YSPConvolutionBlurThread::YSPConvolutionBlurThread(QImage* raw, QImage* target, int d, int start, int step, int* kernal1DInt, bool considerAlpha) :QThread() {
	Raw = raw;
	Target = target;
	D = d;
	R = (d - 1) / 2;
	x = 0;
	y = start;
	PixelPointer = (QARGB32_32*)Raw->bits();
	xFirst = 0;
	TargetPixelPointer = (QARGB32_32*)Target->bits();
	Kernel1D = kernal1DInt;
	Buffer = new QARGB32_32[d];
	yStep = step;
	ConsiderAlpha = considerAlpha;
	r = 0; g = 0; b = 0; a = 0;
}
void YSPConvolutionBlurThread::run() {
	if (ConsiderAlpha) {
		while (this->y + this->yStep < this->Target->height()) {
			this->blurIteratorFirstColumn();
			for (int x = 1; x < this->Target->width(); x++) {
				this->blurIterator();
			}
		}
	}
	else {
		while (this->y + this->yStep < this->Target->height()) {
			this->blurIteratorFirstColumnNoAlpha();
			for (int x = 1; x < this->Target->width(); x++) {
				this->blurIteratorNoAlpha();
			}
		}
	}
}
void YSPConvolutionBlurThread::rgbaBound(int* value) {
	if (((unsigned)(*value)) <= (unsigned)255) { return; }
	if (*value > 255) { *value = 255; return; }
	*value = 0;
}
void YSPConvolutionBlurThread::blurIteratorFirstColumn() {
	xFirst = y * Raw->width();
	TargetPixelPointer = (QARGB32_32*)Target->bits() + y * Target->width();
	x = 0;
	for (int x0 = 0; x0 < D; x0++) {
		r = 0, g = 0, b = 0, a = 0;
		PixelPointer = (QARGB32_32*)Raw->bits() + x0 + xFirst;
		for (int y0 = 0; y0 < D; y0++) {
			a += ((*PixelPointer & 0xff000000) >> 24) * Kernel1D[y0];
			r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[y0];
			g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[y0];
			b += (*PixelPointer & 0x000000ff) * Kernel1D[y0];
			PixelPointer += Raw->width();
		}
		r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);
		rgbaBound(&a);
		QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
		Buffer[x0] = color;
	}
	y += yStep;
	r = 0, g = 0, b = 0, a = 0;
	for (int i = 0; i < D; i++) {
		a += ((Buffer[i] & 0xff000000) >> 24) * Kernel1D[i];
		r += ((Buffer[i] & 0x00ff0000) >> 16) * Kernel1D[i];
		g += ((Buffer[i] & 0x0000ff00) >> 8) * Kernel1D[i];
		b += (Buffer[i] & 0x000000ff) * Kernel1D[i];
	}
	r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
	rgbaBound(&r);
	rgbaBound(&g);
	rgbaBound(&b);
	rgbaBound(&a);
	QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
	*TargetPixelPointer = color;
	TargetPixelPointer++;
}
void YSPConvolutionBlurThread::blurIterator() {
	x++;
	r = 0, g = 0, b = 0, a = 0;
	PixelPointer = (QARGB32_32*)Raw->bits() + (x + R) + xFirst;
	for (int i = 0; i < D; i++) {
		a += ((*PixelPointer & 0xff000000) >> 24) * Kernel1D[i];
		r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[i];
		g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[i];
		b += (*PixelPointer & 0x000000ff) * Kernel1D[i];
		PixelPointer += Raw->width();
	}
	int cbindex = (x - 1) % D;
	r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
	rgbaBound(&r);
	rgbaBound(&g);
	rgbaBound(&b);
	rgbaBound(&a);
	QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
	Buffer[cbindex] = color;
	r = 0, g = 0, b = 0, a = 0;
	int j = cbindex + 1;
	if (j == D) { j = 0; }
	for (int i = 0; i < D; i++) {
		a += ((Buffer[j] & 0xff000000) >> 24) * Kernel1D[i];
		r += ((Buffer[j] & 0x00ff0000) >> 16) * Kernel1D[i];
		g += ((Buffer[j] & 0x0000ff00) >> 8) * Kernel1D[i];
		b += (Buffer[j] & 0x000000ff) * Kernel1D[i];
		j++;
		if (j == D) { j = 0; }
	}
	r = r >> 16; g = g >> 16; b = b >> 16; a = a >> 16;
	rgbaBound(&r);
	rgbaBound(&g);
	rgbaBound(&b);
	rgbaBound(&a);
	color = (a << 24) + (r << 16) + (g << 8) + b;
	*TargetPixelPointer = color;
	TargetPixelPointer++;
}
void YSPConvolutionBlurThread::blurIteratorFirstColumnNoAlpha() {
	xFirst = y * Raw->width();
	TargetPixelPointer = (QARGB32_32*)Target->bits() + y * Target->width();
	x = 0; a = 255;
	for (int x0 = 0; x0 < D; x0++) {
		r = 0, g = 0, b = 0;
		PixelPointer = (QARGB32_32*)Raw->bits() + x0 + xFirst;
		for (int y0 = 0; y0 < D; y0++) {
			r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[y0];
			g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[y0];
			b += (*PixelPointer & 0x000000ff) * Kernel1D[y0];
			PixelPointer += Raw->width();
		}
		r = r >> 16; g = g >> 16; b = b >> 16;
		rgbaBound(&r);
		rgbaBound(&g);
		rgbaBound(&b);

		QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
		Buffer[x0] = color;
	}
	y += yStep;
	r = 0, g = 0, b = 0;
	for (int i = 0; i < D; i++) {
		r += ((Buffer[i] & 0x00ff0000) >> 16) * Kernel1D[i];
		g += ((Buffer[i] & 0x0000ff00) >> 8) * Kernel1D[i];
		b += (Buffer[i] & 0x000000ff) * Kernel1D[i];
	}
	r = r >> 16; g = g >> 16; b = b >> 16;
	rgbaBound(&r);
	rgbaBound(&g);
	rgbaBound(&b);
	QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
	*TargetPixelPointer = color;
	TargetPixelPointer++;
}
void YSPConvolutionBlurThread::blurIteratorNoAlpha() {
	x++;
	r = 0, g = 0, b = 0, a = 255;
	PixelPointer = (QARGB32_32*)Raw->bits() + (x + R) + xFirst;
	for (int i = 0; i < D; i++) {
		r += ((*PixelPointer & 0x00ff0000) >> 16) * Kernel1D[i];
		g += ((*PixelPointer & 0x0000ff00) >> 8) * Kernel1D[i];
		b += (*PixelPointer & 0x000000ff) * Kernel1D[i];
		PixelPointer += Raw->width();
	}
	int cbindex = (x - 1) % D;
	r = r >> 16; g = g >> 16; b = b >> 16;
	rgbaBound(&r);
	rgbaBound(&g);
	rgbaBound(&b);
	QARGB32_32 color = (a << 24) + (r << 16) + (g << 8) + b;
	Buffer[cbindex] = color;
	r = 0, g = 0, b = 0;
	int j = cbindex + 1;
	if (j == D) { j = 0; }
	for (int i = 0; i < D; i++) {
		r += ((Buffer[j] & 0x00ff0000) >> 16) * Kernel1D[i];
		g += ((Buffer[j] & 0x0000ff00) >> 8) * Kernel1D[i];
		b += (Buffer[j] & 0x000000ff) * Kernel1D[i];
		j++;
		if (j == D) { j = 0; }
	}
	r = r >> 16; g = g >> 16; b = b >> 16;
	rgbaBound(&r);
	rgbaBound(&g);
	rgbaBound(&b);
	color = (a << 24) + (r << 16) + (g << 8) + b;
	*TargetPixelPointer = color;
	TargetPixelPointer++;
}
 def_del YSPConvolutionBlurThread::~YSPConvolutionBlurThread() {
	delete[] Buffer;
}

/*
高斯模糊器
raw: 原图指针
target: 目标指针
d: 高斯核直径，必须为奇数
considerAlpha: 如果是true，那么会考虑alpha通道，否则不考虑。对于非透明图可以显著提高性能
目标的长宽必须和原图相差 d - 1
*/
void YSPConvolutionBlur::blur(QImage* raw, QImage* target, int d, bool considerAlpha) {
	if (d % 2 == 0) { d++; }
	int CPUCount = QThread::idealThreadCount();
	QList<QThread*> handlers;
	double* Kernal1D = new double[d];
	double sum = 0;
	double sigma = 0.3 * ((d - 1) * 0.5 - 1) + 0.8; // reference OpenCV
	double sigma2 = sigma * sigma;
	for (int i = 0; i < d; i++) {
		double x = i - (d - 1) / 2;
		Kernal1D[i] = qExp(-(x * x) / (2 * sigma2)) / (qSqrt(2 * M_PI) * sigma);
		sum += Kernal1D[i];
	}
	for (int i = 0; i < d; i++) {
		Kernal1D[i] /= sum;
	}
	int* Kernal1DInt = new int[d];
	for (int i = 0; i < d; i++) {
		Kernal1DInt[i] = (int)(65536 * Kernal1D[i]); // reference Qt
	}
	for (int i = 0; i < CPUCount; i++) {
		YSPConvolutionBlurThread* thread = new YSPConvolutionBlurThread(raw, target, d, i, CPUCount, Kernal1DInt, considerAlpha);
		handlers.append(thread);
		thread->start();
	}
	for (int i = 0; i < handlers.size(); i++) {
		handlers[i]->wait();
		handlers[i]->deleteLater();
	}
	delete[] Kernal1D;
	delete[] Kernal1DInt;
}

