#include "mainwindow.h"
#include "directoryselector.h"


#include <QVBoxLayout>
#include <QPushButton>

#include <QFutureWatcher>
#include <QFile>
#include <QTextStream>
#include <QLineEdit>
#include <QLabel>
#include <QTextEdit>
#include <QProgressDialog>
#include <QDebug>
#include <QElapsedTimer>
#include <QSlider>
#include <thread>
#include <QComboBox>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{

    auto window = new QWidget(this);
    window->setMinimumSize(QSize(400,400));
    directorySelector_ = new DirectorySelector(window);
    _button_zip = new QPushButton("Zip folder", window);
    _button_unzip = new QPushButton("Unzip file",window);
    _password = new QLineEdit("",window);
    _uncompressChoice = new QComboBox(window);

    _uncompressChoice->addItem("DECOMPRESSION  MUTEX");
    _uncompressChoice->addItem("DECOMPRESSION QT CONCURRENT");


    _comboCompression = new QComboBox(window);
    QStringList compressionLevel(QStringList()<< "1" << "2" << "3" << "4" << "5" << "6" << "7" << "8" << "9");
    _comboCompression->addItems(compressionLevel);

    _nbCores = std::thread::hardware_concurrency();
    auto slider = new QSlider(Qt::Horizontal,window);
    slider->setTickInterval(1);
    slider->setTickPosition(QSlider::TicksRight);
    slider->setRange(1,_nbCores);
    slider->setSliderPosition(1);

    _fileName = new QLineEdit("C:/Users/Stef/Desktop/test.ecf", window);
    result_ = new QTextEdit(window);

    auto layout = new QVBoxLayout;
    layout->addWidget(_button_zip);
    layout->addWidget(_button_unzip);
    layout->addWidget(_uncompressChoice);
    layout->addWidget(new QLabel("Nombre de coeurs",window));
    layout->addWidget(slider);
    layout->addWidget(new QLabel("Niveau de compression",window));
    layout->addWidget(_comboCompression);

    layout->addWidget(new QLabel("Dossier  :", window));
    layout->addWidget(directorySelector_);
    layout->addWidget(new QLabel("Nom du fichier compressé :", window));
    layout->addWidget( _fileName );
    layout->addWidget(new QLabel("Mot de passe : ",window));
    layout->addWidget(_password);
    layout->addWidget(result_);

    connect(slider,SIGNAL(valueChanged(int)),this,SLOT(sliderChanged(int)));
    connect(_button_zip,SIGNAL(clicked()),this, SLOT(processZip()));
    connect(_button_unzip,SIGNAL(clicked()),this, SLOT(processUnzip()));
    connect(directorySelector_,SIGNAL(directoryChanged(QDir)),this,SLOT(directoryChanged(QDir)));


    window->setLayout(layout);
    setCentralWidget(window);
    show();

}

MainWindow::~MainWindow()
{
}

void MainWindow::sliderChanged(int nbCore){
    _nbCores=nbCore;
#ifdef DEBUG
    qDebug()<< "nb cores : "<< nbCore;
#endif
}

void MainWindow::processZip() {

#ifdef DEBUG
    qDebug()<< "zipping"<<endl;
    qDebug()<< "Compression level : "<<_comboCompression->currentIndex()<<endl;
#endif

    int zipLevel(_comboCompression->currentIndex()+1);

    QString text("Starting zipping...\n");
    result_->clear();
    result_->setText(text);

    QElapsedTimer timer;
    timer.start();
    QString folder(directorySelector_->currentFolder().absolutePath());

    EpsiFileCompressor compressor(_nbCores,zipLevel);
    compressor.compress(folder,_fileName->text(),QString(_password->text()));

    text+="Zipping done in : "+QString::number(timer.elapsed())+" ms";
    result_->setText(text);

}

void MainWindow::processUnzip(){

    int indexMethod = _uncompressChoice->currentIndex();

    QString text("Starting unzipping...\n");
    QElapsedTimer timer;
    timer.start();
    result_->setText(QString("Starting unzipping..."));

    QString folder(directorySelector_->currentFolder().absolutePath());
    EpsiFileCompressor compressor(_nbCores,_comboCompression->currentIndex()+1);

    switch(indexMethod){
    case 0:
        compressor.uncompressMultiThread(_fileName->text(),folder,_password->text());
        break;
    case 1:
        compressor.uncompressConcurrent(_fileName->text(),folder,QString(_password->text()));
        break;

    }
    text+="Zipping done in : "+QString::number(timer.elapsed())+" ms";
     result_->setText(text);

}

void MainWindow::directoryChanged(const QDir &/*dir*/) {

}

void MainWindow::validateExtensionFile(){

    QFileInfo zippedFile(_fileName->text());
    if(zippedFile.suffix() != "ecf") {
        QMessageBox msg;
        msg.setText("Wrong extension file !");
        msg.exec();
        return;
    }

}


