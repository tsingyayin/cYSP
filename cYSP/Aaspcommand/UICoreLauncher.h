#pragma once
#include "../core/core_T.h"

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
			Sleep(2000);
			if (StoryFile.isOpen()) {
				//qDebug().noquote() << "======���ڽ��а汾ɸѡ======";
				emit signalName->send_kernal_info("======���ڽ��а汾ɸѡ======");
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
						//qDebug().noquote() << "-->�ĵ������汾" + Version + "<--";
						//qDebug().noquote() << "-->����SPOL�汾��SPOL" + Program_Info("SPOL") + "<--";
						//qDebug().noquote() << "������SPOL.9X�ڲ��ڼ䣬ʵ��ʶ��汾Ϊ0.8.0������0.9.0������";
						emit signalName->send_kernal_info("-->�ĵ������汾" + Version + "<--");
						emit signalName->send_kernal_info("-->����SPOL�汾��SPOL" + Program_Info("SPOL") + "<--");
						emit signalName->send_kernal_info("������SPOL.9X�ڲ��ڼ䣬ʵ��ʶ��汾Ϊ0.8.0������0.9.0������");
					}
					else if (StoryFileTextSingleLine.mid(0,6) == "title("  && StoryFileTextSingleLine[StoryFileTextSingleLine.length()-1]==")" && ensureSPOLVer) {
						if (StoryFileTextSingleLine.count(",") != 3) {
							break;
						}
						try {
							Titlesetlist = StoryFileTextSingleLine.mid(6, LineLength - 2).split(",");
							if (Titlesetlist.length() != 4) { throw 0; }
						}
						catch (...) {
							break;
						}
						//qDebug().noquote() << "-->��ñ���<--";
						emit signalName->send_kernal_info("-->��ñ���<---");
						//if (VerList[0] == "SPOL"+Program_Info("SPOL") || VerList[1] == "FollowNew") {
						if (VerList[0] == "SPOL0.8.0" || VerList[0]== "SPOL0.9.0" || VerList[1] == "FollowNew") {
							emit signalName->can_set_title(Titlesetlist);
							firstOpen = true;
							break;
						}
						else {
							emit signalName->send_EIFL_info("SPOL�﷨�쳣��", "δ��ʶ���ĵ�������SPOL�汾��������SPOL�汾����֧��", "��ǰ�汾�������֧��0.9.0�汾", EIFL::SSE);
						}
					}
					if (StoryFileText.atEnd()) { break; }
				}
				StoryFile.close();
				if (firstOpen) {
					//qDebug().noquote() << "======��������������======";
					emit signalName->send_kernal_info("======��������������======");
					Interpreter(gFilename, signalName, this);
				}
				else {
					emit signalName->send_EIFL_info("SPOL�﷨�쳣��", "δ��ʶ���﷨��ȷ�ı����������", "������Ƿ���ȷʹ���˱��������", EIFL::SSE);
				}
				if (!ensureSPOLVer) {
					emit signalName->send_EIFL_info("SPOL�﷨�쳣��", "δ��ʶ���ĵ�������SPOL�汾��������SPOL�汾����֧��", "��ǰ�汾�������֧��0.9.0�汾", EIFL::SSE);
				}
			}
			mutex->tryLock();
			mutex->unlock();
			emit signalName->can_reprint_hello(1);
			this->deleteLater();
			this->exit();
		}
};
