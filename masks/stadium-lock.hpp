#ifndef STADIUMLOCK_HPP
#define STADIUMLOCK_HPP

#include <QWidget>

namespace Ui {
class MaskStadiumLock;
}

class MaskStadiumLock : public QWidget
{
	Q_OBJECT

public:
	explicit MaskStadiumLock(QWidget *parent = 0);
	~MaskStadiumLock();

private:
	Ui::MaskStadiumLock *ui;
};

#endif // STADIUMLOCK_HPP
