#pragma once
//This file contains CESettings class that belongs to CommonEdit Library
//File version 20220124-01
//NEED QT 5\6
//ALSO SUPPORT OPENCV
#include <QtCore>
#include <QtGui>
#include <QtWidgets>

namespace CE {
	enum class TILayout {
		unknown = 0,
		HIT = 1,
		HTI = 2,
		VIT = 3,
		VTI = 4,
	};

	class FormatConversion
	{
	public:
#ifdef USE_OPENCV
		static QImage CVMat_QImage(cv::Mat OpenCVImage) {
			return QImage((uchar*)OpenCVImage.data, OpenCVImage.cols, OpenCVImage.rows, OpenCVImage.step, QImage::Format_RGB888);
		}
#endif
	};

	class CEMultiButton :public QFrame
	{
		Q_OBJECT
	signals:
		void selected(QString);
		void clicked();
		void pressed();
	private:
		TILayout gTIGeo;
		QLabel* InsiderImage;
		QLabel* InsiderLabel;
		QString LabelStyleSheet = "";
		QString CurrentFontSize = "";
		QString StyleNormal = "";
		QString StylePress = "";
		QString StyleHover = "";
		bool gRadioMode;
		double FontP = 0.95;
		friend class CEButtonGroup;
	public:
		QString InsiderValue = "";
		CEMultiButton(TILayout TIGeo = TILayout::VIT, QWidget* parent = Q_NULLPTR, bool RadioMode = FALSE) {
			this->setParent(parent);
			gTIGeo = TIGeo;
			gRadioMode = RadioMode;

			InsiderImage = new QLabel(this);
			InsiderImage->setObjectName("INSIDERIMAGE");

			InsiderLabel = new QLabel(this);
			InsiderLabel->setObjectName("INSIDERLABEL");
			switch (TIGeo) {
			case TILayout::VIT:
				InsiderLabel->setAlignment(Qt::AlignCenter);
				break;
			case TILayout::VTI:
				InsiderLabel->setAlignment(Qt::AlignCenter);
				break;
			case TILayout::HIT:
				InsiderLabel->setAlignment(Qt::AlignLeft);
				break;
			case TILayout::HTI:
				InsiderLabel->setAlignment(Qt::AlignLeft);
				break;
			}
			this->setAttribute(Qt::WA_Hover, true);
			this->installEventFilter(this);
			resizeEvent();
		}
		void setText(QString text) {
			InsiderLabel->setText(text);
		}
		//use"font-size:__AUTO__;"to use automatic font size controll.
		void setTextStyleSheet(QString text) {
			LabelStyleSheet = text;
			text = text.replace("__AUTO__", CurrentFontSize);
			InsiderLabel->setStyleSheet(text);
		}
		void setFontPercentage(double Percentage) {
			FontP = Percentage;
		}
		void setNormalStyleSheet(QString text) {
			StyleNormal = text;
			this->setStyleSheet(text);
		}
		void setHoverStyleSheet(QString text) {
			StyleHover = text;
		}
		void setPressStyleSheet(QString text) {
			StylePress = text;
		}
		void setTextAlignment(Qt::AlignmentFlag Alignment) {
			InsiderLabel->setAlignment(Alignment);
		}
		void setCentralImage(QString image) {
			InsiderImage->setStyleSheet("QLabel{background-color:rgba(0,0,0,0);border-image:url('" + image + "');}");
			//InsiderImage->setStyleSheet("QLabel{background-color:rgba(0,0,0,0);border-image:url('./Icon/¿ÕÏîÄ¿.png');}");
		}
		void setPixmapStyleSheet(QString text) {
			InsiderImage->setStyleSheet(text);
		}
		void click(void) {
			emit pressed();
			this->setStyleSheet(StylePress);
			emit clicked();
			if (!gRadioMode) {
				this->setStyleSheet(StyleNormal);
			}
		}
	private:
		void resizeEvent(QResizeEvent* event = Q_NULLPTR) {
			switch (gTIGeo) {
			case TILayout::VIT:
				InsiderImage->setGeometry(QRect((width() - height() * 0.74 / 9 * 16) / 2, height() * 0.01, height() * 0.74 / 9 * 16, height() * 0.74));
				InsiderLabel->setGeometry(QRect(width() * 0.01, height() * 0.75, width() * 0.98, height() * 0.15));
				break;
			case TILayout::VTI:
				InsiderImage->setGeometry(QRect((width() - height() * 0.74) / 2, height() * 0.25, height() * 0.74, height() * 0.74));
				InsiderLabel->setGeometry(QRect(width() * 0.01, height() * 0.10, width() * 0.98, height() * 0.15));
				break;
			case TILayout::HIT:
				InsiderImage->setGeometry(QRect(width() * 0.02, height() * 0.05, height() * 0.9 / 0.5625, height() * 0.9));
				InsiderLabel->setGeometry(QRect(width() * 0.04 + height() * 0.9 / 0.5625, height() * 0.05, width() * 0.96 - height() * 0.9 / 0.5625, height() * 0.9));
				break;
			case TILayout::HTI:
				InsiderImage->setGeometry(QRect(width() * 0.04, height() * 0.15, height() * 0.7 / 0.5625, height() * 0.7));
				InsiderLabel->setGeometry(QRect(height() * 0.7 / 0.5625, height() * 0.05, width() * 0.68, height() * 0.9));
				break;
			}
			CurrentFontSize = QString::number((int)(InsiderLabel->height() * FontP)) + "px";
			QString CurrentStyleSheet = LabelStyleSheet;
			InsiderLabel->setStyleSheet(CurrentStyleSheet.replace("__AUTO__", CurrentFontSize));
		}
		void mouseReleaseEvent(QMouseEvent* event = Q_NULLPTR) {
			if (event->button() == Qt::LeftButton) {
				emit clicked();
				if (!gRadioMode) {
					this->setStyleSheet(StyleNormal);
				}
			}
		}

		void mousePressEvent(QMouseEvent* event = Q_NULLPTR) {
			if (event->button() == Qt::LeftButton) {
				emit pressed();
				this->setStyleSheet(StylePress);
			}
		}

		void mouseDoubleClickEvent(QMouseEvent* event = Q_NULLPTR) {
			emit selected(InsiderLabel->text());
		}
		bool eventFilter(QObject* obj, QEvent* event) {
			return FALSE;
		}
		QString buttonGroupGetText() {
			return InsiderLabel->text();
		}
		void radioModeReleaseButton() {
			this->setStyleSheet(StyleNormal);
		}
	};

	class CEButtonGroup :public QObject
	{
		Q_OBJECT
	signals:
		void refreshed();
		void selected(QString);
	private:
		QList<CEMultiButton*> ButtonList;
		unsigned int CurrentIndex = 0;
		QString CurrentText = "";
		QString CurrentValue = "";
	public:
		CEButtonGroup(QObject* parent = Q_NULLPTR) {
		}
		void addCEMultiButton(CEMultiButton* Button) {
			connect(Button, SIGNAL(clicked()), this, SLOT(refreshCache()));
			connect(Button, SIGNAL(selected(QString)), this, SIGNAL(selected(QString)));
			ButtonList.append(Button);
		}
		CEMultiButton* button(unsigned int i) {
			if (0 <= i && i < ButtonList.length()) {
				if (!ButtonList.isEmpty()) {
					return ButtonList[i];
				}
			}
			else {
				throw "List index out of range";
			}
		}
		void setCurrentIndex(unsigned int i) {
			if (0 <= i && i < ButtonList.length()) {
				if (!ButtonList.isEmpty()) {
					ButtonList[i]->click();
				}
			}
			else {
				throw "List index out of range";
			}
		}
		unsigned int currentIndex(void) {
			return CurrentIndex;
		}
		QString currentString(void) {
			return CurrentText;
		}
		QString currentValue(void) {
			return CurrentValue;
		}
		unsigned int length(void) {
			return ButtonList.length();
		}
		bool isEmpty() {
			return ButtonList.isEmpty();
		}
		void clear() {
			ButtonList.clear();
		}
	private slots:
		void refreshCache() {
			CEMultiButton* sender = static_cast<CEMultiButton*>(this->sender());
			CurrentText = sender->buttonGroupGetText();
			CurrentValue = sender->InsiderValue;
			for (int i = 0; i < ButtonList.length(); i++) {
				if (sender == ButtonList[i]) {
					CurrentIndex = i;
				}
				else {
					ButtonList[i]->radioModeReleaseButton();
				}
			}

			emit refreshed();
		}
	};

	//This class is only used to implement a "Video summary scroll bar"
	class CEMultiHorizontalScrollBar :public QFrame
	{
		Q_OBJECT
	signals:
		void countChanged(int);
		void valueChanged(qint64);
	private:
		unsigned int LabelCount = 0;
		int Value = 0;
		qint64 Minimum = 0;
		qint64 Maximum = 10;
		QQueue<QLabel*> LabelList;
		QLabel* ScaleMark;
		QLabel* ASmallCover;
	public:
		CEMultiHorizontalScrollBar(QWidget* parent = Q_NULLPTR) {
			this->setParent(parent);
			ASmallCover = new QLabel(this);
			ASmallCover->setObjectName("INSIDERCOVER");
			ScaleMark = new QLabel(this);
			ScaleMark->setObjectName("INSIDERSCALE");
		}
		void loadImage(int Index, QString ImageDir) {
			if (0 <= Index && Index < LabelCount) {
				LabelList[Index]->setStyleSheet("QLabel{border-image:url('" + ImageDir + "')}");
				//qDebug() << "set" << Index;
			}
		}
	public slots:
		void setScaleStyleSheet(QString QSS) {
			ScaleMark->setStyleSheet(QSS);
		}
		void setMinimum(qint64 Min) {
			Minimum = Min;
		}
		void setMaximum(qint64 Max) {
			Maximum = Max;
		}
		void setValue(qint64 value) {
			//qDebug() << value;
			if (value < Minimum) { Value = Minimum; }
			else if (value > Maximum) { Value = Maximum; }
			else { Value = value; }
			ScaleMark->move((Value - Minimum) / (float)(Maximum - Minimum) * width() * 0.98 + width() * 0.01 - 5, height() * 0.01);
			//qDebug() << Value;
		}
		void setValueWithSignal(qint64 value) {
			setValue(value);
			emit valueChanged(value);
		}
		qint64 value() {
			return Value;
		}
		unsigned int count() {
			return LabelCount;
		}
	private:

		void mousePressEvent(QMouseEvent* event) {
			setValue((event->pos().x() - width() * 0.01) / (width() * 0.98) * (Maximum - Minimum) + Minimum);
			emit valueChanged(Value);
		}
		void mouseMoveEvent(QMouseEvent* event) {
			setValue((event->pos().x() - width() * 0.01) / (width() * 0.98) * (Maximum - Minimum) + Minimum);
			emit valueChanged(Value);
		}
		void resizeEvent(QResizeEvent* event) {
			int LabelHeight = height() * 0.98;
			int LabelWidth = width() * 0.98;
			LabelCount = LabelWidth / (LabelHeight / 9.0 * 16.0) + 1;
			while (!LabelList.isEmpty()) {
				LabelList[0]->hide();
				LabelList[0]->deleteLater();
				LabelList.removeFirst();
			}
			//qDebug() << "LabelListLength1" << LabelList.length();
			for (int i = 0; i < LabelCount; i++) {
				QLabel* newLabel = new QLabel(this);
				newLabel->setGeometry(QRect(width() * 0.01 + (LabelHeight / 9.0 * 16.0) * i, height() * 0.1, LabelHeight / 9.0 * 16.0 + 1, height() * 0.8));
				newLabel->show();
				LabelList.append(newLabel);
			}
			//qDebug() << "LabelListLength2" << LabelList.length();
			QColor BGColor = this->palette().background().color();

			ASmallCover->setStyleSheet("QLabel#INSIDERCOVER{background-color:#" + QString::number(BGColor.rgba(), 16) + ";}");
			ASmallCover->setGeometry(QRect(width() * 0.99, height() * 0.1, width() * 0.01 + 1, height() * 0.8));
			ASmallCover->raise();
			ScaleMark->move((Value - Minimum) / (float)(Maximum - Minimum) * width() * 0.98 + width() * 0.01 - 5, height() * 0.01);
			emit countChanged(LabelCount);
#ifdef FIREWORK_PROJECT_ONLY
			GlobalValue::CurrentPixmapNum = LabelCount;
#endif
			ScaleMark->setFixedSize(10, height());
			ScaleMark->raise();
		}
	};
}