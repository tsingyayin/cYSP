#pragma once
#include <VICore>
#include <QtNetwork>


//远程资源
//远程资源获取不干涉原有的本地逻辑，即取得远程资源的方式是手动或半自动的，不会自动获取
class VIRemoteResource :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
};