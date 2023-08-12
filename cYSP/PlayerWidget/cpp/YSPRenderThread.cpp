#include "../YSPRenderThread.h"
#include "../YSPPlayerView.h"

QMutex YSPRenderThread::Mutex;
bool YSPRenderThread::renderFinished() {
	YSPRenderThread::Mutex.lock();
	bool result = RenderFinished;
	YSPRenderThread::Mutex.unlock();
	return result;
}

void YSPRenderThread::setRenderFinished() {
	YSPRenderThread::Mutex.lock();
	RenderFinished = true;
	YSPRenderThread::Mutex.unlock();
}

def_init YSPRenderThread::YSPRenderThread(YSPPlayerView* view, QString fileName) {
	PlayerView = view;
	RenderFinished = false;
	connect(this, &YSPRenderThread::onRender, 
		view, &YSPPlayerView::renderImage, 
		Qt::BlockingQueuedConnection);
	connect(this, &YSPRenderThread::manualTickNextFrame, 
		VICoreFrame->getBehaviorHostInstance(), &VIBehaviorHost::manualExecueQuantifyTickBehaviorHost, 
		Qt::BlockingQueuedConnection);
	this->Width = view->width();
	this->Height = view->height();
	this->FileName = fileName;
	writer = cv::VideoWriter((fileName+".mp4").toStdString(), cv::VideoWriter::fourcc('m', 'p', '4', 'v'),
		32, cv::Size(Width, Height), true);
}

def_del YSPRenderThread::~YSPRenderThread() {
	disconnect(this, &YSPRenderThread::onRender, PlayerView, &YSPPlayerView::renderImage);
}
void YSPRenderThread::run() {
	int frameCount = 0;
	while (!renderFinished()) {
		qDebug() << "Render Frame: " << frameCount++;
		emit manualTickNextFrame(Visindigo::QuantifyTickType::T0, -1);
		emit manualTickNextFrame(Visindigo::QuantifyTickType::T0, -1);
		emit manualTickNextFrame(Visindigo::QuantifyTickType::T0, -1);
		emit manualTickNextFrame(Visindigo::QuantifyTickType::T0, -1);
		emit onRender();
		//PlayerView->CurrentImage.save("./frames/"+QString::number(frameCount) + ".png");
		cv::Mat f = YSPOpenCVAPI::QImage2Mat(PlayerView->CurrentImage);
		//cv::imwrite(("./frames/"+QString::number(frameCount) + ".png").toStdString(), f);
		writer << f;
	}
	qDebug() << "Render Finished: ";
	qDebug() << "File Name: " << FileName + ".mp4";
	qDebug() << "With frame count: " << frameCount << ", fps: 32, "<<frameCount/32.0<<"s";
	writer.release();
	this->deleteLater();
}