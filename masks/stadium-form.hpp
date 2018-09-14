#ifndef STADIUMFORM_HPP
#define STADIUMFORM_HPP

#include <QWidget>
#include <vector>
#include <string>

namespace Ui {
class MaskStadiumForm;
}

class MaskStadiumForm : public QWidget
{
	Q_OBJECT

public:
	explicit MaskStadiumForm(QWidget *parent, int image_width, int image_height);
	~MaskStadiumForm();
	std::vector<std::string> get_mask_names () const;

public:
	Ui::MaskStadiumForm *ui;
};

#endif // STADIUMFORM_HPP
