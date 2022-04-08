#pragma once
#pragma once
#include <QtWidgets>
#include <QtGui>
#include <QtCore>
#include <QtNetwork>
#include "..\langcontrol.h"
#include "..\global_value.h"
#include <exception>

using namespace std;

namespace CE {
	class CEDownload :public QObject
	{
		Q_OBJECT
	public:
		QTimer* timer;
		QNetworkAccessManager* manager;
		QNetworkRequest request;
		QEventLoop* loop;
		bool getIt = FALSE;
		QString gURL;
		QString gLocal;
		CEDownload(QString url, QString local, int interval = 10000) {
			gLocal = local;
			timer = new QTimer();
			timer->setInterval(interval);
			timer->setSingleShot(TRUE);
			manager = new QNetworkAccessManager();;
			request.setUrl(QUrl(url));
			connect(manager, SIGNAL(finished(QNetworkReply*)), this, SLOT(save(QNetworkReply*)));
			loop = new QEventLoop();
			connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
		}
		bool download(void) {
			manager->get(request);
			timer->start();
			loop->exec();
			return getIt;
		}
	private slots:
		void save(QNetworkReply* reply) {
			QFile target;
			target.setFileName(gLocal);
			if (target.exists()) { target.remove(); }
			target.open(QIODevice::NewOnly);
			target.write(reply->readAll());
			target.close();
			getIt = TRUE;
			loop->quit();
		}
	};
}