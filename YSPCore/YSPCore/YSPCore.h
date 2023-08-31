/*
此文件用于包含YSPCore目录下的所有头文件，以便在使用YSPCore时，只需要包含此文件即可

如果您使用Visindigo提供的PyTools中的Dll导出工具，此工具自动利用此文件生成可以用尖括号包含的头文件。
因此如果您的项目需要导出dll，务必认真维护此文件。如果不需要导出dll，您可以删除此文件。
*/
#include "YSPCorePackageMeta.h"
#include "YSPCorePackage.h"
#include "ImageFilter/YSPImageFilter.h"
#include "YSPImageResource.h"
#include "YSPProject.h"
#include "YSPResourceManager.h"

