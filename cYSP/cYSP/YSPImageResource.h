#pragma once
#include "ImageFilter/YSPImageFilter.h"
#include "cYSPPackageMeta.h"
#include "YSPResourceManager.h"
struct YSPFilterInfo {
	YSPImageFilter::FilterName filterName;
	QStringList paras;
};
typedef QList<YSPFilterInfo> YSPFilterInfoList;
class YSPImageResource :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	VI_Singleton(YSPImageResource)
	_Public QHash<QString, QImage> ImageMap;
	_Public VIDocument::VIJSON* MD5Doc;
	_Public YSPImageResource(VISuper* parent) :VIObject(parent) {
		VI_Singleton_Init;
		MD5Doc = new VIDocument::VIJSON(this);
		MD5Doc->loadDefault(cYSP::PackageMeta::getInstance()->getPackageInternalPath() +
			"/resource/defaultEmptyJson.json");
		MD5Doc->loadSettings(YSPResourceManager::getInstance()->getUsersPath() + "/cacheData.json", true);
		MD5Doc->setSaveOnSet(true);
	}
	/*
	* rawFileName: 原始文件名，不包括扩展名
	*/
	_Public QImage getImage(const QString& rawFileName, const YSPFilterInfoList& paras) {
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
		consoleLog("The md5 of " + fileName + " is " + md5Current);
		QString md5Cache = MD5Doc->getValueOf(hashName).toString();
		consoleLog("The last md5 of " + fileName + " is " + md5Cache);
		if (md5Current == md5Cache) {
			consoleLog("The image is cached");
			QFile cacheFile;
			cacheFile.setFileName(YSPResourceManager::getInstance()->getCachesPath() + "/"+hashName + ".png");
			if (cacheFile.open(QIODevice::ReadOnly)) {
				ImageMap[hashName] = QImage(cacheFile.readAll());
				return ImageMap[hashName];
			}
			else {
				consoleLog(VIConsole::inWarningStyle("can't find image file: " + hashName));
			}
		}
		else {
			consoleLog("The image is not cached");
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
				QStringList paras = i->mid(left + 1, right - left - 1).split(",");
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
					info.paras.append("0.9");
				}
				break;
			case YSPImageFilter::FilterName::changeLightness:
				if (info.paras.length() == 0) {
					info.paras.append("0.6");
				}
				break;
			case YSPImageFilter::FilterName::topFadeCover:
				if (info.paras.length() == 0) {
					info.paras.append("0.5");
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

