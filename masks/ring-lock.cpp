#include "ring-lock.hpp"
#include "ui_ring-lock.h"

MaskRingLock::MaskRingLock(QWidget *parent) :
   QWidget(parent),
   ui(new Ui::RingLock)
{
	ui->setupUi(this);
}

MaskRingLock::~MaskRingLock()
{
	delete ui;
}
