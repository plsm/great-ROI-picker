#include <iostream>
#include <fstream>
#include <algorithm>
#include <QPainter>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include "stadium-graphics.hpp"
#include "stadium-form.hpp"
#include "ui_stadium-form.h"
#include "../trigonometry.hpp"

MaskStadiumGraphics::MaskStadiumGraphics (QGraphicsItem *parent, MaskStadiumForm *form, int image_width, int image_height):
   QGraphicsObject (parent),
   center_x (std::min (100, image_width)),
   center_y (std::min (100, image_height)),
   angle (0),
   width (std::min (50, std::max (image_width, image_height))),
   length (std::min (200, std::max (image_width, image_height))),
   border (std::min (100, std::max (image_width, image_height))),
   lock_width (NULL),
   lock_length (NULL),
   lock_border (NULL)
{
	form->ui->centerXSpinBox->setValue (this->center_x);
	form->ui->centerYSpinBox->setValue (this->center_y);
	form->ui->widthSpinBox->setValue (this->width);
	form->ui->lengthSpinBox->setValue (this->length);
	form->ui->borderSpinBox->setValue (this->border);
}

MaskStadiumGraphics::~MaskStadiumGraphics ()
{

}

void MaskStadiumGraphics::setCenterX(int value)
{
	this->center_x = value;
	update ();
}

void MaskStadiumGraphics::setCenterY(int value)
{
	this->center_y = value;
	update ();
}

void MaskStadiumGraphics::setAngle(int value)
{
	this->angle = value;
	update ();
}

void MaskStadiumGraphics::setWidth(int value)
{
	if (value > 10) {
		this->width = value;
		update ();
	}
}

void MaskStadiumGraphics::setLength(int value)
{
	if (value > 10 && value > border + 3) {
		this->length = value;
		update ();
	}
}

void MaskStadiumGraphics::setBorder(int value)
{
	if (value > 3 && value < length - 3) {
		this->border = value;
		update ();
	}
}

void MaskStadiumGraphics::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int _length = LOCK_PROPERTY(lock_length, length);
	int _width = LOCK_PROPERTY(lock_width, width);
	int _border = LOCK_PROPERTY(lock_border, border);
	painter->save ();
	painter->setPen (Qt::black);
	painter->translate (this->center_x, this->center_y);
	painter->rotate (this->angle);
	painter->translate (-this->center_x, -this->center_y);
	painter->drawRoundedRect (
	         this->center_x - _length / 2, this->center_y - _width / 2,
	         _length, _width,
	         _width / 2, _width / 2
	         );
	painter->drawLine (
	         this->center_x - _length / 2 + _border, this->center_y - _width / 2,
	         this->center_x - _length / 2 + _border, this->center_y + _width / 2
	         );
	painter->restore ();
}

QRectF MaskStadiumGraphics::boundingRect () const
{
	int _length = LOCK_PROPERTY(lock_length, length);
	int _width = LOCK_PROPERTY(lock_width, width);
	int extend = std::max (_length, _width);
	return QRectF (this->center_x - extend / 2, this->center_y - extend / 2,
	               extend , extend);
}

unsigned int MaskStadiumGraphics::save_masks (const std::string &folder, int image_width, int image_height, const std::vector<std::string> names, unsigned int image_index) const
{
	int _length = LOCK_PROPERTY(lock_length, length);
	int _width = LOCK_PROPERTY(lock_width, width);
	int _border = LOCK_PROPERTY(lock_border, border);
	cv::Mat mask;
	std::string filename;
	std::cout << "Saving masks to folder [" << folder << "]\n";
	// first mask
	mask = cv::Mat::zeros (image_height, image_width, CV_8UC1);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x + (_length / 2 - _width / 2) * cosd (this->angle + 180),
	            this->center_y + (_length / 2 - _width / 2) * sind (this->angle + 180)
	            ),
	         cvSize (_width / 2, _width / 2),
	         0,
	         this->angle + 90,
	         this->angle + 270,
	         cv::Scalar (255, 0, 0, 0),
	         -1);
	const cv::Point points_1 [] = {
	   cv::Point2i (
	      this->center_x
	      + (_length / 2 - _width / 2) * cosd (this->angle + 180)
	      + _width / 2 * cosd (this->angle + 270),
	      this->center_y
	      + (_length / 2 - _width / 2) * sind (this->angle + 180)
	      + _width / 2 * sind (this->angle + 270)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (_length / 2 - _width / 2) * cosd (this->angle + 180)
	      + _width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (_length / 2 - _width / 2) * sind (this->angle + 180)
	      + _width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (_length / 2 - _border) * cosd (this->angle + 180)
	      + _width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (_length / 2 - _border) * sind (this->angle + 180)
	      + _width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (_length / 2 - _border) * cosd (this->angle + 180)
	      + _width / 2 * cosd (this->angle + 270),
	      this->center_y
	      + (_length / 2 - _border) * sind (this->angle + 180)
	      + _width / 2 * sind (this->angle + 270)
	      )
	};
	cv::fillConvexPoly (
	         mask,
	         points_1,
	         4,
	         cv::Scalar (255, 0, 0, 0),
	         0);
	filename = this->mask_filename (folder, "Stadium-Mask-%d.png", names, 0, image_index);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved first mask\n";
	}
	// second mask
	mask = cv::Mat::zeros (image_height, image_width, CV_8UC1);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x + (_length / 2 - _width / 2) * cosd (this->angle),
	            this->center_y + (_length / 2 - _width / 2) * sind (this->angle)
	            ),
	         cvSize (_width / 2, _width / 2),
	         0,
	         this->angle - 90,
	         this->angle + 90,
	         cv::Scalar (255, 0, 0, 0),
	         -1);
	const cv::Point points_3 [] = {
	   cv::Point2i (
	      this->center_x
	      + (-_length / 2 + _border) * cosd (this->angle)
	      - _width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-_length / 2 + _border) * sind (this->angle)
	      - _width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (-_length / 2 + _border) * cosd (this->angle)
	      + _width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (-_length / 2 + _border) * sind (this->angle)
	      + _width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (_length / 2 - _width / 2) * cosd (this->angle)
	      + _width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (_length / 2 - _width / 2) * sind (this->angle)
	      + _width / 2 * sind (this->angle + 90)
	      ),
	   cv::Point2i (
	      this->center_x
	      + (_length / 2 - _width / 2) * cosd (this->angle)
	      - _width / 2 * cosd (this->angle + 90),
	      this->center_y
	      + (_length / 2 - _width / 2) * sind (this->angle)
	      - _width / 2 * sind (this->angle + 90)
	      )
	};
	cv::fillConvexPoly (
	         mask,
	         points_3,
	         4,
	         cv::Scalar (255, 0, 0, 0),
	         0);
	filename = this->mask_filename (folder, "Stadium-Mask-%d.png", names, 1, image_index + 1);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved second mask\n";
	}
	return image_index + 2;
}

void MaskStadiumGraphics::save_properties (const std::string &folder, unsigned int index) const
{
	std::cout << "Saving properties to folder [" << folder << "]\n";
	std::string filename = folder + "/" + AbstractMask::roi_properties_filename (index);
	std::ofstream ofs (filename);
	ofs << "center_x:" << this->center_x << '\n'
	    << "center_x:" << this->center_x << '\n'
	    << "angle:" << this->angle << '\n'
	    << "width:" << LOCK_PROPERTY(lock_width, width) << '\n'
	    << "length:" << LOCK_PROPERTY(lock_length, length) << '\n'
	    << "border:" << LOCK_PROPERTY(lock_border, border) << '\n';
	ofs.close ();
}
