#include "stadium-form.hpp"
#include "ui_stadium-form.h"

using namespace std;

MaskStadiumForm::MaskStadiumForm(QWidget *parent, int image_width, int image_height) :
   QWidget(parent),
   ui(new Ui::MaskStadiumForm)
{
	ui->setupUi(this);
	this->ui->centerXSpinBox->setMaximum (image_width);
	this->ui->centerYSpinBox->setMaximum (image_height);
	this->ui->lengthSpinBox->setMaximum (std::max (image_width, image_height));
	this->ui->widthSpinBox->setMaximum (std::max (image_width, image_height));
	this->ui->borderSpinBox->setMaximum (std::max (image_width, image_height));
}

MaskStadiumForm::~MaskStadiumForm()
{
	delete ui;
}

std::vector<std::string> MaskStadiumForm::get_mask_names () const
{
	vector<string> result;
	result.push_back (this->ui->roi1NameLineEdit->text ().toStdString ());
	result.push_back (this->ui->roi2NameLineEdit->text ().toStdString ());
	return result;
}
