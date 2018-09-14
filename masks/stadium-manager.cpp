#include "stadium-manager.hpp"
#include "ui_stadium-form.h"
#include "ui_stadium-lock.h"

MaskStadiumManager::MaskStadiumManager(MainWindow *main_window):
   QObject (),
   TemplateManager ("stadium", main_window)
{
	QObject::connect (this->lock->ui->lockWidthCheckBox, SIGNAL (stateChanged (int)), this, SLOT (lockWidthCheckBox (int)));
	QObject::connect (this->lock->ui->lockLengthCheckBox, SIGNAL (stateChanged (int)), this, SLOT (lockLengthCheckBox (int)));
	QObject::connect (this->lock->ui->lockBorderCheckBox, SIGNAL (stateChanged (int)), this, SLOT (lockBorderCheckBox (int)));
}

void MaskStadiumManager::connect_components (MaskStadiumForm *form, MaskStadiumGraphics *graphics)
{
	QObject::connect (form->ui->centerXSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setCenterX (int)));
	QObject::connect (form->ui->centerYSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setCenterY (int)));
	QObject::connect (form->ui->angleSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setAngle (int)));
	QObject::connect (form->ui->widthSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setWidth (int)));
	QObject::connect (form->ui->lengthSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setLength (int)));
	QObject::connect (form->ui->borderSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setBorder (int)));
}

void MaskStadiumManager::lockWidthCheckBox (int state)
{
	LOCK_COMPONENTS(state, widthSpinBox, lock_width, MaskStadiumForm, MaskStadiumGraphics)
}

void MaskStadiumManager::lockLengthCheckBox (int _state)
{
	LOCK_COMPONENTS(_state, lengthSpinBox, lock_length, MaskStadiumForm, MaskStadiumGraphics)
}

void MaskStadiumManager::lockBorderCheckBox (int state)
{
	LOCK_COMPONENTS(state, borderSpinBox, lock_border, MaskStadiumForm, MaskStadiumGraphics)
}
