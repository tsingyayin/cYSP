#pragma once
#include "YSPSPDFMacro.h"
#include <SPDF>

namespace YSP_10X {
	class Background :public SPDFAbstractControllerParser
	{
		Q_OBJECT;
		VI_OBJECT;
		_Public def_init Background() :SPDFAbstractControllerParser() {
			setControllerFlag("bg"); //此项设置您的控制器在SPOL中的行首标识符，必须设置且必须唯一
			setFunctionLike(true); //此项设置您的控制器看上去是否像是一个函数，如果是的话，那么您的控制器行首标识符后的正文内容必须在一对括号中
			setControllerColor(QColor(0, 0, 0)); //此项用于后期的语法高亮，您可以设置您的控制器的颜色
			setDefaultColor(true); //此项用于后期的语法高亮，设置为真时采用内部默认的颜色，否则采用您设置的颜色
		}
		_Public bool onParseLine(const QString& line, SPDF::SPOLExecutionMode mode) {
			QStringList paras = VICommandHost::scientificSplitter(line, ','); //科学分割函数允许反斜杠后跟逗号，这样可以避免逗号被分割
			if (paras.size() > 3) {
				consoleLog("Too many parameters");
				return false;
			}
			int length = paras.size();
			for (int i = 0; i < 3 - length; i++) { paras.append(""); }
			QString fileName = (paras[0] != "" ? paras[0] : "__NONE__");
			QString filter = (paras[1] != "" ? paras[1] : "");
			QString fadeInTime = (paras[2] != "" ? paras[2] : "0");
			consoleLog("Background: " + fileName + "," + filter + "," + fadeInTime);
			SPDFBottomInterface result;
			result.MethodName = SPDFYSP_Background;
			result.Parameters["FileName"] = fileName;
			result.Parameters["Filter"] = filter;
			result.Parameters["FadeInTime"] = fadeInTime;
			recordParserResult(result);
			return true;
		}
	};
}