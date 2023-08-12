#pragma once
#include <VICore>
#include <opencv2/core.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
class YSPOpenCVAPI :public VIObject
{
	Q_OBJECT;
	VI_OBJECT;
	_Public static cv::Mat QImage2Mat(const QImage& image)
    {
        switch (image.format())
        {
        case QImage::Format_RGB888:
        {
            cv::Mat mat(image.height(), image.width(),
				CV_8UC3,
				(void*)image.constBits(),
				image.bytesPerLine());
            cv::Mat mat2;
            cv::cvtColor(mat, mat2, cv::COLOR_RGB2BGR);
			return mat2;
        }
        case QImage::Format_Indexed8:
        {
            cv::Mat mat(image.height(), image.width(),
                CV_8UC1,
                (void*)image.constBits(),
                image.bytesPerLine());
            return mat.clone();
        }
        // wrong
        default:
            qDebug() << "ERROR: QImage could not be converted to Mat.";
            break;
        }
        return cv::Mat();
    }
};
