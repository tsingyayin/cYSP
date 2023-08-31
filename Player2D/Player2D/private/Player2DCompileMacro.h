/*
* 本文件用于定义编译宏，以便在不同的编译选项下，正确地导出或导入类、函数、变量等
* 如果你不知道如何使用此文件，请不要修改此文件
*/
#pragma once
#include <VICore>
#if VI_VERSION_MAJOR != 0 || VI_VERSION_MINOR != 11 || VI_VERSION_PATCH != 1
 #error "This template is only for Visindigo 0.11.1, please use the correct version of Visindigo!"
#endif

// 请在此处定义您的项目的版本号，这样定义的版本号符合Visindigo项目规范，可以快速和Visindigo开发工具对接
#define Player2D_VERSION_MAJOR 0
#define Player2D_VERSION_MINOR 1
#define Player2D_VERSION_PATCH 0

#define Player2D_USER
#ifdef Player2D_EVERYWHERE // 此宏在非Dll编译选项中项目内部定义，参见项目调试属性->C/C++ ->预定义宏
	#undef Player2D_USER
#endif
#ifdef Player2D_DEVELOPER // 此宏在Dll编译选项中内部定义，参见项目调试属性->C/C++ ->预定义宏
	#undef Player2D_USER
#endif

//Visindigo提供的权限标识宏_Public、_Private、_Protected、_Slot、_Signal也在内部定义，防止QT在MOC时出现错误

#ifdef _MSC_VER
	#if defined Player2D_EVERYWHERE
		#define Player2DPublicAPI 
	#elif defined Player2D_DEVELOPER
		#define Player2DPublicAPI __declspec(dllexport)
	#elif defined Player2D_USER
		#define Player2DPublicAPI __declspec(dllimport)
	#else
		#define Player2DPublicAPI
	#endif
#endif

#define Player2DPrivateAPI