#ifndef ROIGOSTADIUMSTANDARD_H
#define ROIGOSTADIUMSTANDARD_H

#include <QGraphicsObject>
#include "abstract-roi.hpp"

class ROIGOStadiumStandard:
      public QGraphicsObject,
      public AbstractROI
{
	Q_OBJECT
public:
	int center_x;
	int center_y;
	double angle;
	int width;
	int length;
	int border;
	ROIGOStadiumStandard (QGraphicsItem *parent = 0);
	virtual ~ROIGOStadiumStandard ();
	void paint (QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0) override;
	virtual QRectF boundingRect () const;
	virtual void save_masks (const std::string &folder, int width, int height, const std::vector<std::string> names) const;
	virtual void save_properties (const std::string &folder) const;
public slots:
	void setCenter_x (int value);
	void setCenter_y (int value);
	void setAngle (int value);
	void setWidth (int value);
	void setLength (int value);
	void setBorder (int value);
};

#endif // ROIGOSTADIUMSTANDARD_H
