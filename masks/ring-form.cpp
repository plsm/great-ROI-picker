#include <algorithm>
#include "ring-form.hpp"

MaskRingForm::MaskRingForm(QWidget *parent, int width, int height) :
   QWidget (parent),
   ui (new Ui::MaskRing)
{
	ui->setupUi(this);
	ui->centerXSpinBox->setMaximum (width);
	ui->centerYSpinBox->setMaximum (height);
	ui->innerRadiusSpinBox->setMaximum (std::max (width, height));
	ui->outerRadiusSpinBox->setMaximum (std::max (width, height));
}

MaskRingForm::~MaskRingForm()
{
	delete ui;
}
