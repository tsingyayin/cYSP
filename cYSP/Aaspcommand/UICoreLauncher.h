#pragma once
#include "../core/core0_6_5_T.h"

#include <QtCore>
#include "../langcontrol.h"
#include <exception>

class SPAWN :public mQThread
{
	public:
		QString gFilename;
		InterpreterSignals* signalName = new InterpreterSignals();
		SPAWN(QString Filename) {
			gFilename = Filename;
			mutex = new QMutex();
			mutex->lock();
			cond = new QWaitCondition();
		}
		void run(void) {
			
			QFile StoryFile;
			bool firstOpen=false;
			bool continueOpen = false;
			StoryFile.setFileName(gFilename);
			StoryFile.open(QIODevice::ReadOnly | QIODevice::Text);
			emit signalName->can_hide_hello(1);

			if (StoryFile.isOpen()) {
				qDebug().noquote() << "======正在进行版本筛选======";
				
				QString Version;
				int Linecount = 0;
				QStringList VerList;
				bool ensureSPOLVer = FALSE;
				QStringList Titlesetlist;

				QTextStream StoryFileText(&StoryFile);
				StoryFileText.setCodec("UTF-8");
				QString StoryFileTextSingleLine;
				for (;;) {
					Linecount += 1;
					StoryFileTextSingleLine = StoryFileText.readLine();
					int LineLength = StoryFileTextSingleLine.length();
					if (StoryFileTextSingleLine[0] == "/") {
						Version = StoryFileTextSingleLine.mid(1, LineLength - 1);
						VerList = Version.split("-");
						if (VerList.length() != 2) { VerList << "DONOTFOLLOW"; }
						ensureSPOLVer = TRUE;
						qDebug().noquote() << "-->文档声明版本" + Version + "<--";
						qDebug().noquote() << "-->程序SPOL版本：SPOL" + Program_Info("SPOL") + "<--";
					}
					else if (StoryFileTextSingleLine[0] == ":" && ensureSPOLVer) {
						if (StoryFileTextSingleLine.count(":") != 4) {
							break;
						}
						try {
							Titlesetlist = StoryFileTextSingleLine.mid(1, LineLength - 1).split(":");
							if (Titlesetlist.length() != 4) { throw 0; }
						}
						catch (...) {
							break;
						}
						qDebug().noquote() << "-->获得标题<--";
						if (VerList[0] == "SPOL"+Program_Info("SPOL") || VerList[1] == "FollowNew") {
							emit signalName->can_show_title(Titlesetlist);
							firstOpen = true;
							break;
						}
					}
					if (StoryFileText.atEnd()) { break; }
				}
				StoryFile.close();
				if (firstOpen) {
					qDebug().noquote() << "======启动解释器核心======";
					Interpreter(gFilename, signalName, this);
				}
				
			}
			if (!firstOpen) {
				qDebug().noquote() << "";
			}
			mutex->tryLock();
			mutex->unlock();
			emit signalName->can_reprint_hello(1);
			this->deleteLater();
			this->exit();
		}
};
