#pragma once
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <QtNetwork>
#include "..\langcontrol.h"
#include "..\global_value.h"
#include "checkupdate.h"
#include <exception>

using namespace std;

class uCheckUpdate :public QObject
{
	Q_OBJECT
public:
	QTimer* timer;
	QNetworkAccessManager* manager;
	QNetworkRequest request;
	QEventLoop* loop;
	bool checkend = FALSE;
	QList<QStringList> editionlist;
	uCheckUpdate(void) {
		timer = new QTimer();
		timer->setInterval(5000);
		timer->setSingleShot(TRUE);
		manager = new QNetworkAccessManager();;
		request.setUrl(QUrl("https://qingyayin.lofter.com"));
		connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(saveText(QNetworkReply*)));
		loop = new QEventLoop();
		connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
	}
	QList<QStringList> getUpdate(int a = 0) {
		manager->get(request);
		timer->start();
		loop->exec();
		if (editionlist.isEmpty()) {
			editionlist.append({ "UNKNOWNNETERROR","UNKNOWNNETERROR","UNKNOWNNETERROR","UNKNOWNNETERROR","NONELINK" });
		}
		return editionlist;		
	}
public slots:
	void saveText(QNetworkReply* reply) {
		QTextStream LatestText(reply->readAll());
		LatestText.setCodec("UTF-8"); 
		
		int dayindex;
		QString dayinfo;
		int verindex_s;
		int verindex_e;
		QString verinfo;
		QString Subver;
		QString BuildVer;
		try {
			for (;;) {
				QString SingleLine = LatestText.readLine();
				if (SingleLine.contains("��������YSP����") && !SingleLine.contains("Ver")) {
					dayindex = SingleLine.indexOf("��������YSP����");
					dayinfo = SingleLine.mid(dayindex - 8, 8);
				}
				else if (SingleLine.contains("��������YSP�����ڲ��汾��Ver") || SingleLine.contains("��������YSP���򹫿��汾��Ver")) {
					if (dayinfo.toInt() > Program_Info("Day").toInt()) {
						verindex_s = SingleLine.indexOf("Ver");
						verindex_e = SingleLine.indexOf("��");
						verinfo = SingleLine.mid(verindex_s, verindex_e - verindex_s);
						if (verinfo.contains("Pre")) { Subver = "Pre"; }
						else if (verinfo.contains("Pub")) { Subver = "Pub"; }
						else { Subver = "Branch"; }
						BuildVer=verinfo.mid(verinfo.indexOf("(Build") + 6, verinfo.indexOf(")") - verinfo.indexOf("(Build") - 6);
						editionlist.append({ dayinfo,verinfo,Subver,BuildVer,"NONELINK"});
					}
				}
				else if (SingleLine.contains("��������") || SingleLine.contains("�Ի�ȡ������־")) {
					QString link = SingleLine.mid(SingleLine.indexOf("��������") + 4, SingleLine.indexOf("�Ի�ȡ������־") - SingleLine.indexOf("��������") - 4);
					editionlist[editionlist.length()-1][4] = link;	
				}
				if (LatestText.atEnd()) { break; }
			}
		}catch (...) {
			editionlist.append({"UNKNOWNBLOG","UNKNOWNBLOG","UNKNOWNBLOG","UNKNOWNBLOG","NONELINK" });
		}
		checkend = TRUE;
		loop->quit();
	}
		
};

