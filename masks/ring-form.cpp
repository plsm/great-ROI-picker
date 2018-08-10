#include <algorithm>
#include "ring-form.hpp"

using namespace std;

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

std::vector<std::string> MaskRingForm::get_mask_names () const
{
	vector<string> result;
	result.push_back (this->ui->nameLineEdit->text ().toStdString ());
	return result;
}
