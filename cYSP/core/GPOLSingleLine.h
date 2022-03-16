#pragma once
#include "GPOLPointer.h"
#include "../UIFolder/ArtificialUI.h"
#include "GPOLSignal.h"
#include "../global_value.h"

class GPOLSingleLine :public QObject
{
	Q_OBJECT
public:
	GPOLBaseSignal* BaseSignal;
	GPOLSingleLine() {
		BaseSignal = new GPOLBaseSignal(this);
	}
	bool SingleLine(QString LineString) {
		QStringList CommandRAW;

		QString CommandSplit;
		bool InText = FALSE;
		foreach(QChar SC, LineString) {
			if (SC == '"') {
				InText = !InText;
			}
			if ((SC == ' ' || SC == ';') && !InText) {
				CommandRAW.append(CommandSplit);
				CommandSplit.clear();
			}
			else {
				CommandSplit += SC;
			}
		}
		if (CommandRAW[0] == "USE") {
			GPOLNameBranch(CommandRAW[1].split("."), CommandRAW.mid(2, CommandRAW.length() - 2));
		}
	}
	bool GPOLNameBranch(QStringList Name, QStringList Arg) {
		if (Name[0] == "System") {
			if (Name[1] == "wait") {
				QTest::qSleep(Arg[0].toInt());
				return TRUE;
			}
			else if (Name[1] == "Player") {
				if (Name[2] == "PlayerPage") {
					if (Name[3] == "WordLabel") {
						if (Name[4] == "setText") {
							setTextOfWordLabel(Arg[0], Arg[1], Arg[2]);
							return TRUE;
						}
					}
					else if (Name[3] == "FreeLabel") {
						if (Name[4] == "setText") {
							setTextOfFreeLabel(Arg[0], Arg[1], Arg[2]);
							return TRUE;
						}
					}
				}
				BaseSignal->PlayerSignal(Name, Arg);
			}
		}
	}
	bool setTextOfWordLabel(QString Interval, QString Word, QString wait) {
		int AlphaCount = 0;
		QString WordsAll;
		for (int j = 0; j < Word.length(); j++) {
			ushort chara = Word[j].unicode();
			if (0x4E00 <= chara && chara <= 0x9FFF ||
				0x3040 <= chara && chara <= 0x309F ||
				0x30A0 <= chara && chara <= 0x30FF) {
				AlphaCount += 2;
			}
			else { AlphaCount += 1; }
			if (AlphaCount > 60) {
				WordsAll += "\n";
				AlphaCount = 1;
			}
			WordsAll += Word[j];
			if (Interval.toFloat() != 0) {
				QTest::qSleep(1000 * Interval.toFloat() * PlayerBaseInfo::SpeedFloat);
			}
		}
		BaseSignal->PlayerSignal({ "System","Player","PlayerPage","WordLabel","setText" }, { WordsAll });
		QTest::qSleep(1000 * wait.toFloat() * PlayerBaseInfo::SpeedFloat);
	}
	bool setTextOfFreeLabel(QString Interval, QString Word, QString wait) {
		int AlphaCount = 0;
		QString WordsAll;
		for (int j = 0; j < Word.length(); j++) {
			ushort chara = Word[j].unicode();
			if (0x4E00 <= chara && chara <= 0x9FFF ||
				0x3040 <= chara && chara <= 0x309F ||
				0x30A0 <= chara && chara <= 0x30FF) {
				AlphaCount += 2;
			}
			else { AlphaCount += 1; }
			if (AlphaCount > 60) {
				WordsAll += "\n";
				AlphaCount = 1;
			}
			WordsAll += Word[j];
			if (Interval.toFloat() != 0) {
				QTest::qSleep(1000 * Interval.toFloat() * PlayerBaseInfo::SpeedFloat);
			}
		}
		BaseSignal->PlayerSignal({ "System","Player","PlayerPage","FreeLabel","setText" }, { WordsAll });
		QTest::qSleep(1000 * wait.toFloat() * PlayerBaseInfo::SpeedFloat);
	}
};