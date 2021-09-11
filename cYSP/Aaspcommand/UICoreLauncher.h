#pragma once
#include "../core/core0_6_5_T.h"

#include <QtCore>
#include "../langcontrol.h"
#include <exception>

class SPAWN :public QThread
{
	public:
		QMutex* mutex;
		QWaitCondition* cond;
		QString gFilename;
		InterpreterSignals* signalName = new InterpreterSignals();
		SPAWN(QString Filename) {
			gFilename = Filename;
			mutex = new QMutex();
			mutex->lock();
			cond = new QWaitCondition();
		}

		void pause(void) {
			cond->wait(mutex);
		}
		void wake(void) {
			cond->wakeAll();
		}
		void run(void) {
			QList<QStringList> warnline;
			QList<QStringList> texterrorline;
			QList<QStringList> numseterrorline;
			QList<QStringList> formatwarnline;
			QList<QStringList> nameerrorline;
			QList<QStringList> playnext;
			QList<QList<QStringList>> interpreterinfo;
			
			QFile StoryFile;
			bool firstOpen=false;
			bool continueOpen = false;
			StoryFile.setFileName(gFilename);
			StoryFile.open(QIODevice::ReadOnly | QIODevice::Text);

			if (StoryFile.isOpen()) {
				qDebug().noquote() << "======Start early filtering process======";
				emit signalName->can_hide_hello(1);

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
					if (StoryFileTextSingleLine[-1] != "\n") {
						StoryFileTextSingleLine.append("\n");
						formatwarnline.append({ QString::number(Linecount),gFilename,StoryFileTextSingleLine });
					}
					int LineLength = StoryFileTextSingleLine.length();
					if (StoryFileTextSingleLine[0] == "/") {
						Version = StoryFileTextSingleLine.mid(1, LineLength - 2);
						VerList = Version.split("-");
						if (VerList.length() != 2) { VerList << "DONOTFOLLOW"; }
						ensureSPOLVer = TRUE;
						qDebug().noquote() << "-->"+msg("Spawn_Mode_Get_Version") + Version + "<--";
					}
					else if (StoryFileTextSingleLine[0] == ":" && ensureSPOLVer) {
						if (StoryFileTextSingleLine.count(":") != 4) {
							texterrorline.append({ QString::number(Linecount),gFilename,StoryFileTextSingleLine });
							break;
						}
						try {
							Titlesetlist = StoryFileTextSingleLine.mid(1, LineLength - 1).split(":");
							if (Titlesetlist.length() != 4) { throw 0; }
						}
						catch (...) {
							texterrorline.append({ QString::number(Linecount),gFilename,StoryFileTextSingleLine });
							break;
						}
						qDebug().noquote() << "-->Get Title Line<--";
						if (VerList[0] == "SPOL0.6.5" || VerList[1] == "FollowNew") {
							emit signalName->can_show_title(Titlesetlist);
							firstOpen = true;
							break;
						}
					}
					if (StoryFileText.atEnd()) { break; }
				}
				StoryFile.close();
				if (firstOpen) {
					Interpreter(gFilename, InterpreterMode::presource, signalName);
				}
				
			}
			if (!firstOpen) {
				qDebug().noquote() << "";
			}
			mutex->tryLock();
			mutex->unlock();
			this->exit();
		}
};
