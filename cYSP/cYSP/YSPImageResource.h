#pragma once
#include "ImageFilter/YSPImageFilter.h"
#include "cYSPPackageMeta.h"
#include "YSPResourceManager.h"
struct YSPFilterInfo {
	YSPImageFilter::FilterName filterName;
	QStringList paras;
};
typedef QList<YSPFilterInfo> YSPFilterInfoList;

class YSPImageResource;
class YSPImageThreadGenerator :public QThread {
	Q_OBJECT;
	friend class YSPImageResource;
	_Protected QImage RawImage;
	_Protected QString MD5;
	_Protected YSPFilterInfoList Info;
	_Protected QString HashName;
	_Public def_init YSPImageThreadGenerator(const QString& hashName, const QString& md5, const QImage& rawImage,const YSPFilterInfoList& info) {
		HashName = hashName;
		Info = info;
		MD5 = md5;
		RawImage = rawImage;
	}
	_Public void run()override;
};
class YSPImageResource :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Singleton(YSPImageResource)
	friend class YSPImageThreadGenerator;
	_Signal void imageGenerated();
	_Public QHash<QString, QImage> ImageMap;
	_Public VIDocument::VIJSON* MD5Doc;
	QList<YSPImageThreadGenerator*> ThreadList;
	_Public YSPImageResource(VISuper* parent) :VIObject(parent) {
		VI_Singleton_Init;
		MD5Doc = VI_NULL;
		onProjectChanged();
	}
	/*
	* rawFileName: 原始文件名，不包括扩展名
	*/
	_Public void onProjectChanged() {
		if (MD5Doc != VI_NULL) {
			MD5Doc->deleteLater();
		}
		MD5Doc = new VIDocument::VIJSON(this);
		MD5Doc->loadDefault(cYSP::PackageMeta::getInstance()->getPackageInternalPath() +
			"/resource/defaultEmptyJson.json");
		MD5Doc->loadSettings(YSPResourceManager::getInstance()->getCachesPath() + "/cacheImageData.json", true);
		MD5Doc->setSaveOnSet(true);
	}
	_Public QImage getImage(const QString& rawFileName, const YSPFilterInfoList& paras) {
		return _getImage(rawFileName, paras, false);
	}
	_Public void loadImage(const QString& rawFileName, const YSPFilterInfoList& paras) {
		_getImage(rawFileName, paras, true);
	}
	_Public void generateTaskBegin() {
		if (ThreadList.length() == 0) {
			emit imageGenerated();
			return;
		}
		for (auto i = ThreadList.begin(); i != ThreadList.end(); i++) {
			(*i)->start();
		}

	}
	_Slot void clearCache() {
		ImageMap.clear();
	}
	_Private QImage _getImage(const QString& rawFileName, const YSPFilterInfoList& paras, bool threadGeneration = false) {
		QString hashName = rawFileName;
		for (int i = 0; i < paras.size(); i++) {
			hashName += "_" + QString::number((int)paras[i].filterName) + "[" + paras[i].paras.join(",") + "]";
		}
		if (ImageMap.contains(hashName)) {
			return ImageMap[hashName];
		}
		QString fileName = rawFileName;
		QFile file;
		QString fullFileName = "";
		file.setFileName(YSPResourceManager::getInstance()->getProjectPath()+"/resource/" + fileName+".png");
		if (!file.open(QIODevice::ReadOnly)) {
			file.setFileName(YSPResourceManager::getInstance()->getGlobalResourcesPath()+"/"+ fileName+".png");
			if (!file.open(QIODevice::ReadOnly)) {
				consoleLog(VIConsole::inWarningStyle("can't find image file: " + fileName));
				ImageMap[hashName] = QImage();
				return QImage();
			}
			fullFileName = YSPResourceManager::getInstance()->getGlobalResourcesPath() + "/" + fileName+".png";
		}
		else {
			fullFileName = YSPResourceManager::getInstance()->getProjectPath() + "/resource/" + fileName+".png";
		}
		QString md5Current = MD5Check(file.readAll());
		file.close();
		QString md5Cache = MD5Doc->getValueOf(hashName).toString();
		consoleLog("The last md5 of " + fileName + " is " + md5Cache + ", and current is " + md5Current);
		if (md5Current == md5Cache) {
			consoleLog(VIConsole::inNoticeStyle("The original image has not changed, attempting to load the cache: "+ 
				YSPResourceManager::getInstance()->getCachesPath() + "/" + hashName + ".png"));
			QFile cacheFile;
			cacheFile.setFileName(YSPResourceManager::getInstance()->getCachesPath() + "/"+hashName + ".png");
			if (cacheFile.exists()) {
				ImageMap[hashName] = QImage(YSPResourceManager::getInstance()->getCachesPath() + "/" + hashName + ".png");
				consoleLog(VIConsole::inSuccessStyle("The cache file is loaded successfully"));
				return ImageMap[hashName];
			}
			else {
				consoleLog(VIConsole::inWarningStyle("can't find cache file: " + hashName+", a generation task will be added to the task list later "));
			}
		}
		else {
			consoleLog(VIConsole::inWarningStyle("The image is not cached!"));
		}
		if (threadGeneration) {
			YSPImageThreadGenerator* generator = new YSPImageThreadGenerator(hashName, md5Current, QImage(fullFileName), paras);
			connect(generator, &YSPImageThreadGenerator::finished, this, &YSPImageResource::onThreadFinished);
			ThreadList.append(generator);
			return QImage();
		}
		QImage image(fullFileName);
		for (auto i = paras.begin(); i != paras.end(); i++) {
			switch (i->paras.length()) {
			case 0:
				YSPImageFilter::filterOperation(i->filterName, image);
				break;
			case 1:
				YSPImageFilter::filterOperation(i->filterName, image, i->paras[0].toDouble());
				break;
			case 2:
				YSPImageFilter::filterOperation(i->filterName, image, i->paras[0].toDouble(), i->paras[1].toDouble());
				break;
			case 3:
				YSPImageFilter::filterOperation(i->filterName, image, i->paras[0].toDouble(), i->paras[1].toDouble(), i->paras[2].toDouble());
				break;
			case 4:
				YSPImageFilter::filterOperation(i->filterName, image, i->paras[0].toDouble(), i->paras[1].toDouble(), i->paras[2].toDouble(), i->paras[3].toDouble());
				break;
			}
		}
		bool saved = image.save(YSPResourceManager::getInstance()->getCachesPath() + "/"+hashName + ".png");
		if (!saved) {
			consoleLog(VIConsole::inWarningStyle("can't save image file: " + fileName));
		}
		MD5Doc->setValueOf(hashName, md5Current);
		ImageMap[hashName] = image;
		return image;
	}
	_Private void onThreadFinished() {
		YSPImageThreadGenerator* generator = (YSPImageThreadGenerator*)sender();
		QString hashName = generator->HashName;
		QString md5Current = generator->MD5;
		QImage image = generator->RawImage;
		MD5Doc->setValueOf(hashName, md5Current);
		consoleLog("The image with hash name " + hashName + " is generated");
		ImageMap[hashName] = image;
		ThreadList.removeAll(generator);
		generator->deleteLater();
		if (ThreadList.length() == 0) {
			emit imageGenerated();
		}
	}
	_Public QString MD5Check(QByteArray fileArray) {
		return QCryptographicHash::hash(fileArray, QCryptographicHash::Md5).toHex();
	}
	_Public YSPFilterInfoList spolFilterParser(const QString& spol) {
		YSPFilterInfoList result = YSPFilterInfoList();
		QStringList filterList = spol.split("_");
		for (auto i = filterList.begin(); i != filterList.end(); i++) {
			YSPFilterInfo info;
			if (i->contains("[") && i->contains("]")) {
				int left = i->indexOf("[");
				int right = i->indexOf("]");
				QStringList paras = i->mid(left + 1, right - left - 1).split("|");
				*i = i->left(left);
				paras.removeAll("");
				paras.removeAll(" ");
				YSPImageFilter::FilterName filter = YSPImageFilter::FilterName(i->toInt());
				info.filterName = filter;
				info.paras = paras;
			}
			else {
				YSPImageFilter::FilterName filter = YSPImageFilter::FilterName(i->toInt());
				info.filterName = filter;
			}
			switch (info.filterName) {
			case YSPImageFilter::FilterName::changeSaturation:
				if (info.paras.length() == 0) {
					info.paras.append("-0.5");
				}
				break;
			case YSPImageFilter::FilterName::changeLightness:
				if (info.paras.length() == 0) {
					info.paras.append("-0.5");
				}
				break;
			case YSPImageFilter::FilterName::topFadeCover:
				if (info.paras.length() == 0) {
					info.paras.append("1.0");
				}
				break;
			case YSPImageFilter::FilterName::gaussianBlur:
				if (info.paras.length() == 0) {
					info.paras.append("7");
				}
				break;
			case YSPImageFilter::FilterName::edgeExtension:
				if (info.paras.length() == 0) {
					info.paras.append("1");
				}
				break;
			}
			result.append(info);
		}
		return result;
	}
	
}; 

