#include "stadium-lock.hpp"
#include "ui_stadium-lock.h"

MaskStadiumLock::MaskStadiumLock(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::MaskStadiumLock)
{
	ui->setupUi(this);
}

MaskStadiumLock::~MaskStadiumLock()
{
	delete ui;
}
