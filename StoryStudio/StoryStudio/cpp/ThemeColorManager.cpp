#include "../ThemeColorManager.h"
#include "../StoryStudioPackageMeta.h"
bool ThemeColorManager::loadConfig(const QString& configName) {
	if (ColorConfig != nullptr) {
		ColorConfig->deleteLater();
		ColorConfig = new VIDocument::VIJSON(this);
	}
	if (configName == "Light") {
		ColorConfig->loadSettings(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeLight.json");
		Type = ThemeType::Light;
		return true;
	}
	else if (configName == "Dark") {
		ColorConfig->loadSettings(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeDark.json");
		Type = ThemeType::Dark;
		return true;
	}
	else {
		bool clrcfg = ColorConfig->loadSettings(StoryStudio::PackageMeta::getInstance()->getPackageRootPath() + "/theme/" + configName + ".json");
		if (!clrcfg) {
			ColorConfig->loadSettings(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeLight.json");
			Type = ThemeType::Light;
		}
		else {
			QString clrType = ColorConfig->getValueOf("ThemeType").toString();
			if (clrType == "Light") {
				ColorConfig->loadDefault(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeLight.json");
			}
			else if (clrType == "Dark") {
				ColorConfig->loadDefault(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeDark.json");
			}
			else {
				ColorConfig->loadDefault(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeLight.json");
				ColorConfig->setValueOf("ThemeType", "Light");
			}
			Type = ThemeType::User;
		}
		return clrcfg;
	}
}

QStringList ThemeColorManager::getAllThemeFileNames() {
	QStringList list;
	QDir dir(StoryStudio::PackageMeta::getInstance()->getPackageRootPath() + "/theme");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);
	dir.setSorting(QDir::Name);
	QFileInfoList fileInfoList = dir.entryInfoList();
	for (int i = 0; i < fileInfoList.size(); ++i) {
		QFileInfo fileInfo = fileInfoList.at(i);
		if (fileInfo.fileName().endsWith(".json")) {
			list.append(fileInfo.fileName());
		}
	}
	return list;
}

bool ThemeColorManager::createNewTheme(ThemeType t, const QString& name) {
	VIDocument::VIJSON* clr = new VIDocument::VIJSON();
	if (t == ThemeType::Light || t == ThemeType::User) {
		clr->loadDefault(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeLight.json");
	}
	else if (t == ThemeType::Dark) {
		clr->loadDefault(StoryStudio::PackageMeta::getInstance()->getPackageInternalPath() + "/resource/defaultThemeDark.json");
	}
	return clr->loadSettings(StoryStudio::PackageMeta::getInstance()->getPackageRootPath() + "/theme/" + name + ".json", true);
}