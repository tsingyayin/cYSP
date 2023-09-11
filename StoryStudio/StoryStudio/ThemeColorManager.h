#pragma once
#include <VICore>
#include "private/StoryStudioCompileMacro.h"

class StoryStudioPublicAPI ThemeColorManager :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public enum class ThemeType {
		Light, Dark, User
	};
	_Public VIDocument::VIJSON* ColorConfig;
	_Public ThemeType Type;
	_Public def_init ThemeColorManager(VISuper* parent = VI_NULL) :VIObject(parent) {
		ColorConfig = new VIDocument::VIJSON(this);
	}
	_Public bool loadConfig(const QString& configName);
	_Public static QString getThemeTypeStr(ThemeType s) {
		switch (s) {
			VI_ENUMSTR(ThemeType, Light);
			VI_ENUMSTR(ThemeType, Dark);
			VI_ENUMSTR(ThemeType, User);
		}
	}
	_Public QString getValueOf(const QString& key) {
		return ColorConfig->getValueOf(key).toString();
	}
	_Public QString getThemeName() {
		return ColorConfig->getValueOf("ThemeName").toString();
	}
	_Public static QStringList getAllThemeFileNames();
	_Public static bool createNewTheme(ThemeType t, const QString& name);
	_Public void setValueOf(const QString& key, const QString& value) {
		if (Type == ThemeType::User) {
			ColorConfig->setValueOf(key, value);
		}
	}
};