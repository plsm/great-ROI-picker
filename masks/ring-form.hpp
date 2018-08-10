#ifndef RING_HPP
#define RING_HPP

#include <QWidget>
#include <vector>
#include <string>

#include "ui_ring-form.h"

class RingManager;
class MaskRingGraphics;

namespace Ui {
class MaskRing;
}

class MaskRingForm : public QWidget
{
	Q_OBJECT
	friend class RingManager;
	friend class MaskRingGraphics;

public:
	explicit MaskRingForm (QWidget *parent, int width, int height);
	~MaskRingForm();
	std::vector<std::string> get_mask_names () const;
private:
	Ui::MaskRing *ui;
};

#endif // RING_HPP
