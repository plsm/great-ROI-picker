#ifndef ROIGOSTADIUMLONG_H
#define ROIGOSTADIUMLONG_H

#include <QGraphicsObject>
#include "abstract.hpp"

class RingManager;
class MaskRingForm;

class MaskRingGraphics:
      public QGraphicsObject,
      public AbstractMask
{
	Q_OBJECT
	friend class RingManager;

private:
	int center_x;
	int center_y;
	int inner_radius;
	int outer_radius;
	MaskRingGraphics *lock_inner_radius;
	MaskRingGraphics *lock_outer_radius;
public:
	MaskRingGraphics (QGraphicsItem *parent, MaskRingForm *form, int image_width, int image_height);
	virtual ~MaskRingGraphics ();
	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	virtual QRectF boundingRect () const;
	virtual unsigned int save_masks (const std::string &folder, int image_width, int image_height, const std::vector<std::string> names, unsigned int image_index) const;
	virtual void save_properties (const std::string &folder, unsigned int index) const;
public slots:
	void setCenterX (int value);
	void setCenterY (int value);
	void setInnerRadius (int value);
	void setOuterRadius (int value);
};

#endif // ROIGOSTADIUMLONG_H
