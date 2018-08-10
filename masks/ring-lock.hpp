#ifndef RINGLOCK_HPP
#define RINGLOCK_HPP

#include <QWidget>

namespace Ui {
class RingLock;
}

class MaskRingLock : public QWidget
{
	Q_OBJECT

public:
	Ui::RingLock *ui;
	explicit MaskRingLock(QWidget *parent = 0);
	~MaskRingLock();
};

#endif // RINGLOCK_HPP
