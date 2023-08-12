#include "YSPConvolutionBlur.h"
/*
ImageFilter
此文件是YSP的core_B.h文件的精神续作
*/
class YSPImageFilter : public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
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
	_Public static void filterOperation(FilterName name, QImage& rawImage, float p_a = 0, float p_b = 0, float p_c = 0, float p_d = 0) {
		QImage* image = &rawImage;
		switch (name)
		{
		case YSPImageFilter::FilterName::topFadeCover:
			topFadeCover(image, p_a);
			break;
		case YSPImageFilter::FilterName::grayScale:
			grayScale(image);
			break;
		case YSPImageFilter::FilterName::blackCover:
			blackCover(image);
			break;
		case YSPImageFilter::FilterName::changeSaturation:
			changeSaturation(image, p_a);
			break;
		case YSPImageFilter::FilterName::changeLightness:
			changeLightness(image, p_a);
			break;
		case YSPImageFilter::FilterName::mirror:
			mirror(image, p_a);
			break;
		case YSPImageFilter::FilterName::gaussianBlur:
			gaussianBlur(image, p_a);
			break;
		case YSPImageFilter::FilterName::edgeExtension:
			edgeExtension(image, p_a);
			break;
		case YSPImageFilter::FilterName::reverse:
			reverse(image);
			break;
		}
	}
	_Public static void topFadeCover(QImage* image, float endP) {
		if (endP < 0) { endP = 0; }
		if (endP > 1) { endP = 1; }
		int end = image->height() * endP;
		for (int i = 0; i < end; i++) {
			float delta = ((float)i + 1) / end;
			for (int j = 0; j < image->width(); j++) {
				QColor color = image->pixel(j, i);
				float p = 1.0 - VICommonMapping::sin_0_1(1.0 - (float)i / end);
				int r = color.red() * p;
				int g = color.green() * p;
				int b = color.blue() * p;
				image->setPixelColor(j, i, QColor(r, g, b, color.alpha()));
			}
		}
	}
	_Public static void grayScale(QImage* image) {
		for (int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				QColor color = image->pixel(i, j);
				int gray = (color.red() * 11 + color.green() * 16 + color.blue() * 5) / 32;
				image->setPixel(i, j, qRgba(gray, gray, gray, color.alpha()));
			}
		}
	}
	_Public static void blackCover(QImage* image) {
		QARGB32_32* pixel = (QARGB32_32*)image->bits();
		for(int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				if (*pixel >> 24 != 0xFF) {
					*pixel = 0x00000000;
				}
			}
		}
	}
	_Public static void changeSaturation(QImage* image, float saturation) {
		if (saturation < -1) { saturation = -1; }
		if (saturation > 1) { saturation = 1; }
		for (int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				float delta = 1 + saturation;
				QColor color = image->pixel(i, j);
				int saturation = color.hsvSaturation() * delta;
				if (saturation > 255) { saturation = 255; }
				image->setPixel(i, j, QColor::fromHsv(color.hsvHue(), saturation, color.value(), color.alpha()).rgba());
			}
		}
	}
	_Public static void changeLightness(QImage* image, float lightness) {
		if (lightness < -1) { lightness = -1; }
		if (lightness > 1) { lightness = 1; }
		for (int i = 0; i < image->width(); i++) {
			for (int j = 0; j < image->height(); j++) {
				float delta = 1 + lightness;
				QColor color = image->pixel(i, j);
				int value = color.value() * delta;
				if (value > 255) { value = 255; }
				image->setPixel(i, j, QColor::fromHsv(color.hsvHue(), color.hsvSaturation(), value, color.alpha()).rgba());
			}
		}
	}
	_Public static void mirror(QImage* image, float direction) {
		int d = direction;
		if (d != 0 && d != 1 && d != 2) { d = 0; }
		QImage t = image->mirrored(d == 0 || d == 2, d == 1 || d == 2);
		*image = t;
	}
	_Public static void gaussianBlur(QImage* image, int d, bool considerAlpha = false) {
		if (d % 2 == 0) { d++; }
		if (image->format() != QImage::Format_ARGB32) { *image = image->convertToFormat(QImage::Format_ARGB32); qDebug() << "convert"; }
		QImage* temp = _edgeExtension(image, d);
		YSPConvolutionBlur::blur(temp, image, d, considerAlpha);
		delete temp;
	}
	_Public static void edgeExtension(QImage* image, int d) {
		*image = *_edgeExtension(image, d);
	}
	_Private static QImage* _edgeExtension(QImage* image, int d) {
		if (d % 2 == 0) { d++; }
		int r = (d - 1) / 2;
		int d2 = d * d;
		QImage* temp = new QImage(image->width() + r * 2, image->height() + r * 2, QImage::Format_ARGB32);
		//fill temp with image in the center
		QPainter painter(temp);
		painter.drawImage(QPoint(r, r), *image);
		painter.end();
		//top left corner
		QColor color = image->pixel(0, 0);
		QARGB32_8 red = color.red();
		QARGB32_8 green = color.green();
		QARGB32_8 blue = color.blue();
		QARGB32_8 alpha = color.alpha();
		QARGB32_32 color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		QARGB32_32* pixels;
		for (int i = 0; i < r; i++) {
			pixels = (QARGB32_32*)temp->scanLine(i);
			for (int j = 0; j < r; j++) {
				*pixels = color32;
				pixels++;
			}
		}
		//bottom left corner
		color = image->pixel(0, image->height() - 1);
		red = color.red();
		green = color.green();
		blue = color.blue();
		alpha = color.alpha();
		color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		for (int j = image->height() + r; j < temp->height(); j++) {
			pixels = (QARGB32_32*)temp->scanLine(j);
			for (int i = 0; i < r; i++) {
				*pixels = color32;
				pixels++;
			}
		}
		//top right corner
		color = image->pixel(image->width() - 1, 0);
		red = color.red();
		green = color.green();
		blue = color.blue();
		alpha = color.alpha();
		color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		for (int j = 0; j < r; j++) {
			pixels = (QARGB32_32*)temp->scanLine(j);
			for (int i = image->width() + r; i < temp->width(); i++) {
				*pixels = color32;
				pixels++;
			}
		}
		//bottom right corner
		color = image->pixel(image->width() - 1, image->height() - 1);
		red = color.red();
		green = color.green();
		blue = color.blue();
		alpha = color.alpha();
		color32 = (alpha << 24) + (red << 16) + (green << 8) + blue;
		for (int i = image->height() + r; i < temp->height(); i++) {
			pixels = (QARGB32_32*)temp->scanLine(i);
			for (int j = image->width() + r; j < temp->width(); j++) {
				*pixels = color32;
				pixels++;
			}
		}
		QARGB32_32* pixelRaw;
		//Top
		for (int i = 0; i < r; i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(0);
			pixels = (QARGB32_32*)temp->scanLine(i) + r;
			memcpy(pixels, pixelRaw, image->width() * sizeof(QARGB32_32));
		}
		//Bottom
		for (int i = image->height() + r; i < temp->height(); i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(image->height() - 1);
			pixels = (QARGB32_32*)temp->scanLine(i) + r;
			memcpy(pixels, pixelRaw, image->width() * sizeof(QARGB32_32));
		}
		//Left
		for (int i = r; i < image->height() + r; i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(i - r);
			pixels = (QARGB32_32*)temp->scanLine(i);
			for (int j = 0; j < r; j++) {
				*pixels = *pixelRaw;
				pixels++;
			}
		}
		//Right
		for (int i = r; i < image->height() + r; i++) {
			pixelRaw = (QARGB32_32*)image->scanLine(i - r) + (image->width() - 1);
			pixels = (QARGB32_32*)temp->scanLine(i) + r + (image->width() - 1);
			for (int j = 0; j < r; j++) {
				*pixels = *pixelRaw;
				pixels++;
			}
		}
		return temp;
	}

	_Public static void reverse(QImage* image) {
		unsigned int length = image->width() * image->height();
		if (image->format() != QImage::Format_ARGB32) { *image = image->convertToFormat(QImage::Format_ARGB32); }
		QARGB32_32* pixel = (QARGB32_32*)image->bits();
		for (int i = 0; i < length; i++) {
			*pixel = ~(*pixel) & 0x00FFFFFF | (*pixel) & 0xFF000000;
			pixel++;
		}
	}
};