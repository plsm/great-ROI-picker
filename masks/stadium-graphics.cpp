#include <iostream>
#include <fstream>
#include <algorithm>
#include <QPainter>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include "stadium-graphics.h"
#include "trigonometry.h"

void ROIGOStadiumStandard::setCenter_x(int value)
{
	center_x = value;
	update ();
}

void ROIGOStadiumStandard::setCenter_y(int value)
{
	center_y = value;
	update ();
}

void ROIGOStadiumStandard::setAngle(int value)
{
	angle = value;
	update ();
}

void ROIGOStadiumStandard::setWidth(int value)
{
	if (value > 10) {
		width = value;
		update ();
	}
}

void ROIGOStadiumStandard::setLength(int value)
{
	if (value > 10 && value > border + 3) {
		length = value;
		update ();
	}
}

void ROIGOStadiumStandard::setBorder(int value)
{
	if (value > 3 && value < length - 3) {
		border = value;
		update ();
	}
}

ROIGOStadiumStandard::ROIGOStadiumStandard (QGraphicsItem *parent):
   QGraphicsObject (parent),
   center_x (100),
   center_y (100),
   angle (0),
   width (50),
   length (200),
   border (100)
{

}

ROIGOStadiumStandard::~ROIGOStadiumStandard ()
{

}


void ROIGOStadiumStandard::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	painter->save ();
	painter->setPen (Qt::black);
	painter->translate (this->center_x, this->center_y);
	painter->rotate (this->angle);
	painter->translate (-this->center_x, -this->center_y);
	painter->drawRoundedRect (
	         this->center_x - this->length / 2, this->center_y - this->width / 2,
	         this->length, this->width,
	         this->width / 2, this->width / 2
	         );
	painter->drawLine (
	         this->center_x - this->length / 2 + this->border, this->center_y - this->width / 2,
	         this->center_x - this->length / 2 + this->border, this->center_y + this->width / 2
	         );
	painter->restore ();
}

QRectF ROIGOStadiumStandard::boundingRect () const
{
	int extend = std::max (this->length, this->width);
	return QRectF (this->center_x - extend / 2, this->center_y - extend / 2,
	               extend , extend);
}

void ROIGOStadiumStandard::save_masks (const std::string &folder, int width, int height, const std::vector<std::string> names) const
{
	cv::Mat mask;
	std::string filename;
	std::cout << "Saving masks to folder [" << folder << "]\n";
	// first mask
	mask = cv::Mat::zeros (height, width, CV_8UC1);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x + (this->length / 2 - this->width / 2) * cosd (this->angle + 180),
	            this->center_y + (this->length / 2 - this->width / 2) * sind (this->angle + 180)
	            ),
	         cvSize (this->width / 2, this->width / 2),
	         0,
	         this->angle + 90,
	         this->angle + 270,
	         cv::Scalar (255, 0, 0, 0),
	         -1);
	const cv::Point points_1 [] = {
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 270),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 270)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->border) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->border) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->border) * cosd (this->angle + 180)
	      + this->width / 2 * cosd (this->angle + 270),
	      this->center_y
	      + (this->length / 2 - this->border) * sind (this->angle + 180)
	      + this->width / 2 * sind (this->angle + 270)
	      )
	};
	cv::fillConvexPoly (
	         mask,
	         points_1,
	         4,
	         cv::Scalar (255, 0, 0, 0),
	         0);
	filename = this->mask_filename (folder, "Mask-1.png", names, 0);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved first mask\n";
	}
	// second mask
	mask = cv::Mat::zeros (height, width, CV_8UC1);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x + (this->length / 2 - this->width / 2) * cosd (this->angle),
	            this->center_y + (this->length / 2 - this->width / 2) * sind (this->angle)
	            ),
	         cvSize (this->width / 2, this->width / 2),
	         0,
	         this->angle - 90,
	         this->angle + 90,
	         cv::Scalar (255, 0, 0, 0),
	         -1);
	const cv::Point points_3 [] = {
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border) * cosd (this->angle)
	      - this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border) * sind (this->angle)
	      - this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (-this->length / 2 + this->border) * cosd (this->angle)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-this->length / 2 + this->border) * sind (this->angle)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle)
	      + this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle)
	      + this->width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (this->length / 2 - this->width / 2) * cosd (this->angle)
	      - this->width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (this->length / 2 - this->width / 2) * sind (this->angle)
	      - this->width / 2 * sind (this->angle + 90)
	      )
	};
	cv::fillConvexPoly (
	         mask,
	         points_3,
	         4,
	         cv::Scalar (255, 0, 0, 0),
	         0);
	filename = this->mask_filename (folder, "Mask-2.png", names, 1);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved second mask\n";
	}
}

void ROIGOStadiumStandard::save_properties (const std::string &folder) const
{
	std::cout << "Saving properties to folder [" << folder << "]\n";
	std::string filename = folder + "/" + AbstractROI::ROI_PROPERTIES_FILENAME;
	std::ofstream ofs (filename);
	ofs << "center_x:" << this->center_x << '\n'
	    << "center_x:" << this->center_x << '\n'
	    << "angle:" << this->angle << '\n'
	    << "width:" << this->width << '\n'
	    << "length:" << this->length << '\n'
	    << "border:" << this->border << '\n';
	ofs.close ();
}
