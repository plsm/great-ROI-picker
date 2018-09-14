#include <QWidget>

#include "ring-manager.hpp"
#include "ui_main-window.h"
#include "ui_ring-form.h"
#include "ui_ring-lock.h"

RingManager::RingManager (MainWindow *main_window):
   QObject (),
   TemplateManager ("ring", main_window)
{
	QObject::connect (this->lock->ui->lockInnerRadiusCheckBox, SIGNAL (stateChanged (int)), this, SLOT (lockInnerRadiusCheckBox (int)));
	QObject::connect (this->lock->ui->lockOuterRadiusCheckBox, SIGNAL (stateChanged (int)), this, SLOT (lockOuterRadiusCheckBox (int)));
}

void RingManager::connect_components (MaskRingForm *form, MaskRingGraphics *graphics)
{
	QObject::connect (form->ui->centerXSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setCenterX (int)));
	QObject::connect (form->ui->centerYSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setCenterY (int)));
	QObject::connect (form->ui->innerRadiusSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setInnerRadius (int)));
	QObject::connect (form->ui->outerRadiusSpinBox, SIGNAL (valueChanged (int)), graphics, SLOT (setOuterRadius (int)));
	QObject::connect (form->ui->outerRadiusSpinBox, SIGNAL (valueChanged (int)), this->main_window->ui->graphicsView, SLOT (update ()));
}

void RingManager::lockInnerRadiusCheckBox (int state)
{
	LOCK_COMPONENTS(state, innerRadiusSpinBox, lock_inner_radius, MaskRingForm, MaskRingGraphics)
}

void RingManager::lockOuterRadiusCheckBox (int state)
{
	LOCK_COMPONENTS(state, outerRadiusSpinBox, lock_outer_radius, MaskRingForm, MaskRingGraphics)
}
