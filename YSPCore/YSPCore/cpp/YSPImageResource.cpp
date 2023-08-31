#include "../YSPImageResource.h"

VI_Singleton_StaticInit(YSPImageResource);

def_init YSPImageThreadGenerator::YSPImageThreadGenerator(const QString& hashName, const QString& md5, const QImage& rawImage, const YSPFilterInfoList& info) {
	HashName = hashName;
	Info = info;
	MD5 = md5;
	RawImage = rawImage;
}

void YSPImageThreadGenerator::run() {
	for (auto i = Info.begin(); i != Info.end(); i++) {
		switch (i->paras.length()) {
		case 0:
			YSPImageFilter::filterOperation(i->filterName, RawImage);
			break;
		case 1:
			YSPImageFilter::filterOperation(i->filterName, RawImage, i->paras[0].toDouble());
			break;
		case 2:
			YSPImageFilter::filterOperation(i->filterName, RawImage, i->paras[0].toDouble(), i->paras[1].toDouble());
			break;
		case 3:
			YSPImageFilter::filterOperation(i->filterName, RawImage, i->paras[0].toDouble(), i->paras[1].toDouble(), i->paras[2].toDouble());
			break;
		case 4:
			YSPImageFilter::filterOperation(i->filterName, RawImage, i->paras[0].toDouble(), i->paras[1].toDouble(), i->paras[2].toDouble(), i->paras[3].toDouble());
			break;
		}
	}
	RawImage.save(YSPRM->getProjectCachesPath() + "/" + HashName + ".png");
}