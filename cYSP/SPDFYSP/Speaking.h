#pragma once
#include <SPDF>
namespace YSP_10X {
	class Speaking :public SPDFAbstractControllerParser
	{
		Q_OBJECT;
		VI_OBJECT;
		_Public def_init Speaking() :SPDFAbstractControllerParser() {
			setControllerFlag(">>>"); //此项设置您的控制器在SPOL中的行首标识符，必须设置且必须唯一
			setFunctionLike(false); //此项设置您的控制器看上去是否像是一个函数，如果是的话，那么您的控制器行首标识符后的正文内容必须在一对括号中
			setControllerColor(QColor(0, 0, 0)); //此项用于后期的语法高亮，您可以设置您的控制器的颜色
			setDefaultColor(true); //此项用于后期的语法高亮，设置为真时采用内部默认的颜色，否则采用您设置的颜色
		}
		_Public bool onParseLine(const QString& line, SPDFNamespace::SPOLExecutionMode mode) {
			/*此函数用于解析您的控制器，您可以在此函数中对您的控制器进行解析，请注意：
			1. 您拿到的line参数中已经剥离了行首标识符。如果您的控制器是函数形式的，那么您拿到的line参数相当于是括号中的内容
			2. mode参数代表当前的执行模式，目前分为预加载（Preload）和运行时（Runtime）模式，
					您可以根据不同的模式决定不同的解析行为（例如在预加载时进行语法检查或预载入数据），
					无论何种模式，您必须返回一个布尔量代表解析是否成功。当返回为false时，当前SPOL会跳过此行，继续解析下一行（此行为以后可能会改变）
			3. 当您解析到一定的控制器时，您应该创建一个SPDFParserResult对象，在此对象中：
					a.MethodName字段标明您解析出了哪一种控制器
					b.Parameters字段承载控制器的具体参数
					c.NoWait字段标明解释器（后端）是否需要等待抽象终端（前端）执行完控制器后才能继续执行
					d.ExecutionMode字段在内部被设置为mode参数的值，您不需要手动设置
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

			QStringList Speakers = line.split(">>>");
			for (auto speaker = Speakers.begin(); speaker != Speakers.end(); speaker++) {
				QStringList SpeakerInfo = speaker->split(":");
				if (SpeakerInfo.length() < 1 || SpeakerInfo.length() > 3) {
					consoleLog("讲述控制器：主参数个数少于1个或多于三个");
					return false;
				}
				QStringList SpeakerDisplayInfo = SpeakerInfo[0].split("/");
				if (SpeakerDisplayInfo.length() > 5) {
					consoleLog("讲述控制器：显示参数多于五个");
					return false;
				}
				QString DisplayName = SpeakerDisplayInfo[0];
				QString SpeakerText = "";
				if (SpeakerInfo.length() == 2) {
					SpeakerText = SpeakerInfo[1];
				}
				else {
					DisplayName = SpeakerInfo[1];
					SpeakerText = SpeakerInfo[2];
				}
				int length = SpeakerDisplayInfo.length();
				for (int i = 0; i < 6 - length; i++) { SpeakerDisplayInfo.append(""); }
				QString FileNameSuffix = (SpeakerDisplayInfo[1] != "" ? SpeakerDisplayInfo[1] : "");
				QString FilterSuffix = (SpeakerDisplayInfo[2] != "" ? SpeakerDisplayInfo[2] : "");
				QString FadeInSecond = (SpeakerDisplayInfo[3] != "" ? SpeakerDisplayInfo[3] : "0");
				QString FadeOutSecond = (SpeakerDisplayInfo[4] != "" ? SpeakerDisplayInfo[4] : "0");
				QString FileName = SpeakerDisplayInfo[0];
				if (FileNameSuffix != "") { FileName += "_" + FileNameSuffix; }
				if (FilterSuffix != "") { FileName += "_" + FilterSuffix; }
				if (FileName == "") { FileName = "__None__"; }
				else { FileName += ".png"; }
				int index = SpeakerText.lastIndexOf("(");
				QStringList SpeedSubController = { "0.04","1.75" };
				if (index != -1 && SpeakerText.endsWith(")")) {
					QString SpeedSubControllerText = SpeakerText.mid(index + 1, SpeakerText.length() - index - 2);
					SpeakerText = SpeakerText.mid(0, index);
					SpeedSubController = SpeedSubControllerText.split(",");
					if (SpeedSubController.length() > 2) {
						consoleLog("讲述控制器：速度控制器参数多于2");
						return false;
					}
					if (SpeedSubController.length() == 1) {
						SpeedSubController.append("1.75");
					}
				}
				/*
				实现有误：
				讲述控制器一行内有多个时，按SPOL规范要求应该只有一个人是可以说话的，但是这里实现的是多个人同时说话
				应该被拆分为多个CharaController和一个SpeakingController
				*/
				SPDFParserResult SpeakerController;
				SpeakerController.MethodName = "YSP_Speaking";
				SpeakerController.Parameters["SpeakerCount"] = Speakers.length();
				SpeakerController.Parameters["DisplayName"] = DisplayName;
				SpeakerController.Parameters["FileName"] = FileName;
				SpeakerController.Parameters["FadeInSecond"] = FadeInSecond;
				SpeakerController.Parameters["FadeOutSecond"] = FadeOutSecond;
				SpeakerController.Parameters["SecondPerChar"] = SpeedSubController[0];
				SpeakerController.Parameters["SecondLineEnd"] = SpeedSubController[1];
				SpeakerController.Parameters["Text"] = SpeakerText;
				Parameters.append(SpeakerController);
			}
			return true;
		}
	};
}