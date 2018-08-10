#include <iostream>
#include <fstream>
#include <algorithm>
#include <QPainter>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>

#include "ring-graphics.hpp"
#include "ring-form.hpp"
#include "ui_ring-form.h"

using namespace std;

MaskRingGraphics::MaskRingGraphics (QGraphicsItem *parent, MaskRingForm *form, int image_width, int image_height):
   QGraphicsObject (parent),
   center_x (min (100, image_width)),
   center_y (min (100, image_height)),
   inner_radius (min (10, max (image_width, image_height))),
   outer_radius (min (50, max (image_width, image_height))),
   lock_inner_radius (NULL),
   lock_outer_radius (NULL)
{
	form->ui->centerXSpinBox->setValue (this->center_x);
	form->ui->centerYSpinBox->setValue (this->center_y);
	form->ui->innerRadiusSpinBox->setValue (this->inner_radius);
	form->ui->outerRadiusSpinBox->setValue (this->outer_radius);
}

MaskRingGraphics::~MaskRingGraphics ()
{

}

void MaskRingGraphics::setCenterX(int value)
{
	center_x = value;
	update ();
}

void MaskRingGraphics::setCenterY(int value)
{
	center_y = value;
	update ();
}

void MaskRingGraphics::setInnerRadius(int value)
{
	if (value > 0) {
		this->inner_radius = value;
		update ();
	}
}

void MaskRingGraphics::setOuterRadius (int value)
{
	if (value > this->inner_radius) {
		this->outer_radius = value;
		update ();
	}
}

void MaskRingGraphics::paint (QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
	int radius;
	painter->save ();
	painter->setPen (Qt::black);
	radius = LOCK_PROPERTY(lock_inner_radius, inner_radius);
	painter->drawEllipse (QPoint (this->center_x, this->center_y), radius, radius);
	radius = LOCK_PROPERTY(lock_outer_radius, outer_radius);
	painter->drawEllipse (QPoint (this->center_x, this->center_y), radius, radius);
}

QRectF MaskRingGraphics::boundingRect () const
{
	int extend = 2 * LOCK_PROPERTY(lock_outer_radius, outer_radius);
	return QRectF (this->center_x - extend / 2, this->center_y - extend / 2,
	               extend , extend);
}

unsigned int MaskRingGraphics::save_masks (const std::string &folder, int image_width, int image_height, const std::vector<std::string> names, unsigned int image_index) const
{
	int radius;
	cv::Mat mask;
	std::string filename;
	std::cout << "Saving masks to folder [" << folder << "]\n";
	// first mask
	mask = cv::Mat::zeros (image_height, image_width, CV_8UC1);
	radius = LOCK_PROPERTY(lock_outer_radius, outer_radius);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x,
	            this->center_y
	            ),
	         cvSize (radius, radius),
	         0,
	         0,
	         360,
	         cv::Scalar (255, 0, 0, 0),
	         -1);
	radius = LOCK_PROPERTY(lock_inner_radius, inner_radius);
	cv::ellipse (
	         mask,
	         cv::Point2i (
	            this->center_x,
	            this->center_y
	            ),
	         cvSize (radius, radius),
	         0,
	         0,
	         360,
	         cv::Scalar (0, 0, 0, 0),
	         -1);
	filename = this->mask_filename (folder, "Ring-Mask-%d.png", names, 0, image_index);
	if (!cv::imwrite (filename, mask)) {
		std::cerr << "Problems writing file\n" << filename << "\n";
	}
	else {
		std::cout << "  saved first mask\n";
	}
	return image_index + 1;
}

void MaskRingGraphics::save_properties (const std::string &folder, unsigned int index) const
{
	int radius;
	std::cout << "Saving properties to folder [" << folder << "]\n";
	std::string filename = folder + "/" + AbstractMask::roi_properties_filename (index);
	std::ofstream ofs (filename);
	ofs << "center_x:" << this->center_x << '\n'
	    << "center_x:" << this->center_x << '\n';
	radius = LOCK_PROPERTY(lock_inner_radius, inner_radius);
	ofs << "inner_radius:" << radius << '\n';
	radius = LOCK_PROPERTY(lock_outer_radius, outer_radius);
	ofs << "outer_radius:" << radius << '\n';
	ofs.close ();
}
