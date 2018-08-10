#include <QFileDialog>
#include <QGraphicsScene>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <libgen.h>
#include <iostream>
#include <stdlib.h>

#include "main-window.hpp"
#include "ui_main-window.h"

#include "masks/ring-manager.hpp"
#include "util-opencv-qt.hpp"

static char TEMPORARY_FOLDER_TEMPLATE[] = "/tmp/mask-picker-XXXXXX";

MainWindow::MainWindow(QWidget *parent) :
   QMainWindow (parent),
   ui (new Ui::MainWindow),
   pixmap (new QGraphicsPixmapItem ()),
   previous_lock (NULL),
   working_folder ("./"),
   temporary_folder (mkdtemp (TEMPORARY_FOLDER_TEMPLATE)),
   first_image (true)
{
	this->ui->setupUi (this);
	QGraphicsScene *scene = new QGraphicsScene ();
	this->ui->graphicsView->setScene (scene);
	scene->addItem (this->pixmap);
	this->managers.push_back (new RingManager (this));
	for (AbstractManager *m : this->managers) {
		this->ui->maskTypeComboBox->addItem (m->label.c_str ());
	}
	std::cout << "Temporary files are written to folder " << this->temporary_folder << '\n';
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::set_image (const std::string &image_filename)
{
	this->image = cv::imread (image_filename, CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat displayed_image;
	if (this->ui->enhanceImageCheckBox->isChecked ())
		cv::equalizeHist (this->image, displayed_image);
	else
		displayed_image = this->image;
	this->pixmap->setPixmap (QPixmap::fromImage (Mat2QImage (displayed_image)));
	this->ui->graphicsView->update ();
	// enable widgets
	this->ui->maskTypeComboBox->setEnabled (true);
	this->ui->enhanceImageCheckBox->setEnabled (true);
	if (this->first_image && this->ui->maskTypeComboBox->count () == 1) {
		this->managers [0]->setup_components (this->image.size ().width, this->image.size ().height);
		// enable widgets
		this->ui->createROIMasksPushButton->setEnabled (true);
		this->ui->highlightROIsCheckBox->setEnabled (true);
		this->ui->numberMasksSpinBox->setEnabled (true);
	}
	this->first_image = false;
}

void MainWindow::on_loadImagePushButton_clicked()
{
	QFileDialog *file_dialog = new QFileDialog ();
	file_dialog->setDirectory (this->working_folder.c_str ());
	file_dialog->setViewMode (QFileDialog::List);
	file_dialog->setOption (QFileDialog::ShowDirsOnly, false);
	file_dialog->setFileMode (QFileDialog::ExistingFiles);
	int return_code = file_dialog->exec ();
	if (return_code == QDialog::Accepted) {
		QStringList strings = file_dialog->selectedFiles ();
		std::string filename = strings.at (0).toStdString ();
		this->set_image (filename);
		char *copy = new char [filename.size () + 1];
		strcpy (copy, filename.c_str ());
		this->working_folder = dirname (copy);
		delete copy;
	}
}

#pragma GCC diagnostic ignored "-Wunused-parameter"
void MainWindow::on_numberMasksSpinBox_valueChanged (int value)
{
	this->managers [this->ui->maskTypeComboBox->currentIndex ()]->update_number_components (this->image.size ().width, this->image.size ().height);
}

void MainWindow::on_createROIMasksPushButton_clicked()
{
	AbstractManager *manager = this->managers [this->ui->maskTypeComboBox->currentIndex ()];
	manager->create_mask_files (this->working_folder, this->image.size ().width, this->image.size ().height, this->ui->useDefaultMaskFileNameCheckBox->isChecked ());
	manager->create_property_files (this->working_folder);
}

void MainWindow::on_maskTypeComboBox_currentIndexChanged (int index)
{
	if (this->ui->maskTypeComboBox->isEnabled ()) {
		this->managers [index]->setup_components (this->image.size ().width, this->image.size ().height);
		// enable widgets
		this->ui->createROIMasksPushButton->setEnabled (true);
		this->ui->highlightROIsCheckBox->setEnabled (true);
		this->ui->numberMasksSpinBox->setEnabled (true);
	}
}

void MainWindow::on_enhanceImageCheckBox_toggled (bool checked)
{
	cv::Mat displayed_image;
	 if (checked) {
		 cv::equalizeHist (this->image, displayed_image);
	 }
	 else {
		 displayed_image = this->image;
	 }
	 this->pixmap->setPixmap (QPixmap::fromImage (Mat2QImage (displayed_image)));
	 this->ui->graphicsView->update ();
}

void MainWindow::on_highlightROIsCheckBox_toggled(bool checked)
{

}
