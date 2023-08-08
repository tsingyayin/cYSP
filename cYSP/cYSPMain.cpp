/*
Visindigo项目结构：
如果您的项目需要导出dll，则您务必遵守：
您的程序的所有功能或每个功能部分都应该设在一个与此文件同级的文件夹中，例如为您自动创建的
cYSP文件夹。与此同时，此文件夹内应该含有和其同名的头文件，例如cYSP.h。
此头文件应该包含此文件夹内的所有头文件，以便在使用cYSP时，只需要包含此文件即可。
例如下文中的#include "cYSP/cYSP.h"。
遵循此规则时，您可以使用Visindigo提供的开发工具快速导出dll和所有相关文件并生成发行文件包。
*/
#pragma execution_character_set("utf-8") //所有含有const char的cpp文件都需要这一句（大概）
#include <VICore>
#include <VIWidgets>
#include <SPDF>
#include "cYSP/cYSP.h"
#include "PlayerWidget/YSPPlayerWidget.h"
#ifndef cYSP_DEVELOPER //用于dll导出时不编译主函数，如果你不知道这是什么，请不要修改
visindigo Program {
	VIFramework Frame(sysArgv);
	// 此处放置框架的初始化参数
	// VVVVVVVVVVVVVVVVVVVV
	Frame.useDebugModeRuntime();


	// AAAAAAAAAAAAAAAAAAA
	Frame.init(); // 初始化框架
	// 此处放置您的项目的初始化代码
	// VVVVVVVVVVVVVVVVVVVV
	VIConsole::printLine(VIConsole::inSuccessStyle("Hello world!"));
	LOAD_PACKAGE(SPDF::Package);
	LOAD_PACKAGE(cYSP::Package);
	
	YSPPlayerWidget* w = new YSPPlayerWidget;
	w->show();
	// AAAAAAAAAAAAAAAAAAA
	Frame.start(); // 启动框架，此行之后的代码将不会被执行
} ProgramEnd;
#endif