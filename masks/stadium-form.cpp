#include "stadium-form.hpp"
#include "ui_maskstadiumform.h"

MaskStadiumForm::MaskStadiumForm(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::MaskStadiumForm)
{
	ui->setupUi(this);
}

MaskStadiumForm::~MaskStadiumForm()
{
	delete ui;
}
