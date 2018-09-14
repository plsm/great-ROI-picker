#ifndef STADIUMMANAGER_HPP
#define STADIUMMANAGER_HPP

#include <QObject>

#include "template-manager.hpp"
#include "stadium-graphics.hpp"
#include "stadium-form.hpp"
#include "stadium-lock.hpp"

class MaskStadiumManager: public QObject,
      public TemplateManager<MaskStadiumForm, MaskStadiumGraphics, MaskStadiumLock>
{
	Q_OBJECT
public:
	explicit MaskStadiumManager (MainWindow *main_window);
	virtual ~MaskStadiumManager () {}
	void virtual connect_components (MaskStadiumForm *form, MaskStadiumGraphics *graphics);
signals:

public slots:
	void lockWidthCheckBox (int state);
	void lockLengthCheckBox (int state);
	void lockBorderCheckBox (int state);
};

#endif // STADIUMMANAGER_HPP
