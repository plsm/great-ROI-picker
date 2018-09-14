#ifndef STADIUMFORM_HPP
#define STADIUMFORM_HPP

#include <QWidget>

namespace Ui {
class MaskStadiumForm;
}

class MaskStadiumForm : public QWidget
{
	Q_OBJECT

public:
	explicit MaskStadiumForm(QWidget *parent = 0);
	~MaskStadiumForm();

private:
	Ui::MaskStadiumForm *ui;
};

#endif // STADIUMFORM_HPP
