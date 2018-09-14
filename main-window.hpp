#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>
#include <QGraphicsPixmapItem>
#include <opencv2/core/core.hpp>
#include <string>
#include <vector>

#include "masks/abstract-manager.hpp"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	Ui::MainWindow *ui;
	QGraphicsPixmapItem *pixmap;
	QWidget *previous_lock;
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void add_manager (AbstractManager *);

private slots:
	void on_loadImagePushButton_clicked();

	void on_numberMasksSpinBox_valueChanged(int arg1);

	void on_createROIMasksPushButton_clicked();

	void on_maskTypeComboBox_currentIndexChanged(int index);

	void on_enhanceImageCheckBox_toggled(bool checked);

	void on_highlightROIsCheckBox_toggled(bool checked);

private:
	/**
	 * @brief folder Folder where the image and masks are stored.
	 *
	 * Folder where the shown image is stored. Image masks and mask properties are
	 * saved in this folder.
	 */
	std::string working_folder;
	/**
	 * @brief temporary_folder Folder where temporary masks are saved.
	 */
	std::string temporary_folder;
	cv::Mat image;
	std::vector<AbstractManager *> managers;
	bool first_image;
	void set_image (const std::string &image_filename);
};

#endif // MAINWINDOW_HPP
