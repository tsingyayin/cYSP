#pragma once
#include "SPDFYSPMacro.h"
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
			/*此函数用于解析您的控制器，您可以在此函数中对您的控制器进行解析，请注意：
			0. 此函数在VIECMA（解释器）线程中调用，我们不建议您在此函数中对任何外部资源进行访问，否则可能会导致死锁
			1. 您拿到的line参数中已经剥离了行首标识符。如果您的控制器是函数形式的，那么您拿到的line参数相当于是括号中的内容
			2. mode参数代表当前的执行模式，目前分为预加载（Preload）和运行时（Runtime）模式，
					您可以根据不同的模式决定不同的解析行为（例如在预加载时进行语法检查或预载入数据），
					考虑到此函数不在主线程中运行，如果您在预加载时需要加载资源，您可以选择仅解析到资源加载方法位置，然后
					令抽象终端（前端）实际加载资源，这样可以避免死锁。
					无论何种模式，您必须返回一个布尔量代表解析是否成功。当返回为false时，当前SPOL会跳过此行，继续解析下一行（此行为以后可能会改变）
			3. 当您解析到一定的控制器时，您应该创建一个SPDFParserResult对象，在此对象中：
					a.MethodName字段标明您解析出了哪一种控制器
					b.Parameters字段承载控制器的具体参数
					c.NoWait字段标明解释器（后端）是否需要等待抽象终端（前端）执行完控制器后才能继续执行
			4. 当您完成一个SPDFParserResult对象后，使用recordParserResult函数将其记录下来，SPDF会稍后将其传递给抽象终端（前端）
			5. 您可以解析出不止一个控制器，只要您将其全部记录下来即可。
			6. 同理，您也可以不解析出任何控制器，但是您必须返回true，否则SPDF会认为您的解析失败，从而跳过此行
			7. 请您记住，您的控制器解析器实例只有一个，因此并不能（或很不方便）为每次解析单独缓存数据，但您可以通过
				setVariable和getVariable函数来设置和获取全局变量，这些全局变量在解释器处缓存，因此您可以在多次解析中使用它们
			8. 您可以使用getExecuteLineIndex和changeExecuteLine函数来获取当前行号和修改下一行号
			9. 您可以使用getSPOLWithIndex函数获取指定行号的SPOL原文（这肯定不会是移除过行首标识符的内容）
			10. 结合以上三条，您可以实现图灵完备。但是请注意，SPDF并不是一个编程语言，因此您不应该在此处实现过于复杂的逻辑。
				与此同时，这三条中提到的接口在VIECMA中暂时不可用。
			*/
			QStringList paras = scientificSplit(line, ','); //科学分割函数允许反斜杠后跟逗号，这样可以避免逗号被分割
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