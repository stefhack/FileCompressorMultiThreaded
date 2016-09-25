#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFuture>
#include "epsifilecompressor.h"


class QTextEdit;
class QLineEdit;
class QDir;
class QProgressBar;
class DirectorySelector;
class QPushButton;
class QComboBox;

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    /**
     * @brief processZip permet de lancer le processus de compression
     * sur l'action du bouton _button_zip
     */
    void processZip();
    /**
     * @brief processUnzip permet de lancer le processus de décompression
     * sur l'action du bouton _button_unzip
     */
    void processUnzip();
    /**
     * @brief directoryChanged
     * @param dir
     */
    void directoryChanged(const QDir &dir);
    /**
     * @brief sliderChanged permet de changer _nbCores
     * @param nbCore le nombre de coeurs à utiliser pour les threads
     */
    void sliderChanged(int nbCore);   
    void validateExtensionFile();
private:
    /**
     * @brief directorySelector_
     */
    DirectorySelector *directorySelector_;
    /**
     * @brief result_ le champ texte pour afficher des informations
     */
    QTextEdit *result_;
    /**
     * @brief _fileName le champ texte contenant le nom
     * du fichier zippé
     */
    QLineEdit *_fileName;
    /**
     * @brief _nbCores le nombre de threads à utiliser pour la compression/décompression
     */
    int _nbCores;
    /**
     * @brief _comboCompression la combobox permettant de choisir le niveau
     * de compression
     */
    QComboBox* _comboCompression;
    /**
     * @brief _password le champ de texte permettant de remplir le mot de passe
     */
    QLineEdit* _password;
    /**
     * @brief _uncompressChoice la combobox permettant de choisir le niveau de compression
     */
    QComboBox* _uncompressChoice;
    /**
     * @brief _button_zip le bouton permettant de lancer la compression
     */
    QPushButton* _button_zip;
    /**
     * @brief _button_unzip le bouton permettant de lancer la décompression
     */
    QPushButton* _button_unzip;  

};

#endif // MAINWINDOW_H
