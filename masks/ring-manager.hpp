#ifndef RINGMANAGER_HPP
#define RINGMANAGER_HPP

#include <QObject>

#include "template-manager.hpp"
#include "ring-graphics.hpp"
#include "ring-form.hpp"
#include "ring-lock.hpp"

class RingManager: public QObject,
      public TemplateManager<MaskRingForm, MaskRingGraphics, MaskRingLock>
{
	Q_OBJECT
public:
	explicit RingManager (MainWindow *main_window);
	virtual ~RingManager () {}
	void virtual connect_components (MaskRingForm *form, MaskRingGraphics *graphics);
signals:

public slots:
	void lockInnerRadiusCheckBox (int state);
	void lockOuterRadiusCheckBox (int state);
};

#endif // RINGMANAGER_HPP
