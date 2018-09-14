#ifndef ROIGOSTADIUMSTANDARD_H
#define ROIGOSTADIUMSTANDARD_H

#include <QGraphicsObject>
#include "abstract.hpp"

class MaskStadiumForm;

class MaskStadiumGraphics:
      public QGraphicsObject,
      public AbstractMask
{
	Q_OBJECT
public:
	int center_x;
	int center_y;
	double angle;
	int width;
	int length;
	int border;
	MaskStadiumGraphics *lock_width;
	MaskStadiumGraphics *lock_length;
	MaskStadiumGraphics *lock_border;
public:
	MaskStadiumGraphics (QGraphicsItem *parent, MaskStadiumForm *form, int image_width, int image_height);
	virtual ~MaskStadiumGraphics ();
	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	virtual QRectF boundingRect () const;
	virtual unsigned int save_masks (const std::string &folder, int image_width, int image_height, const std::vector<std::string> names, unsigned int image_index) const;
	virtual void save_properties (const std::string &folder, unsigned int index) const;
public slots:
	void setCenterX (int value);
	void setCenterY (int value);
	void setAngle (int value);
	void setWidth (int value);
	void setLength (int value);
	void setBorder (int value);
};

#endif // ROIGOSTADIUMSTANDARD_H
