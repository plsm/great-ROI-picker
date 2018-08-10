#include "util-opencv-qt.hpp"

QImage Mat2QImage (const cv::Mat &image)
{
	QImage dest (image.cols, image.rows, QImage::Format_ARGB32);
	for (int y = 0; y < image.rows; ++y) {
		for (int x = 0; x < image.cols; ++x) {
			unsigned int color = image.at<unsigned char> (y, x);
			dest.setPixel (x, y, qRgba (color, color, color, 255));
		}
	}
	return dest;
}
