#ifndef UNZIPWRITER_H
#define UNZIPWRITER_H
#include <QThread>
#include "zippedbufferpool.h"

/**
 * @brief The UnzipWriter class représente l'objet qui va écrire les fichiers décompressés
 */
class UnzipWriter : public QThread
{
    Q_OBJECT

public:
    /**
     * @brief UnzipWriter construit un nouveau writer
     * @param bufferPool un pool contenant les fichiers avec leurs noms et leurs données compressées
     * @param destinationFolder le dossier de destination
     */
    UnzipWriter(ZippedBufferPool& bufferPool,QString& destinationFolder);    
    /**
     * @brief run appelée au démarrage du thread.Tant qu'il y en a , elle récupère un ZippedBuffer du ZippedBufferPool,
     * crée les dossiers et écrit le fichier.
     *
     */
    virtual void run();
    /**
      * @brief makeDirectory permet de créer les dossiers
      * @param directoryName le nom du dossier récupéré du stream avec les délimitations \\ ou /
      */
     void makeDirectory(QString& directoryName);
signals:
     /**
     * @brief filesWrittenChanged permet de signaler que le nombre de fichiers écrits
     * a changé
     * @param nbFiles le nombre  de fichiers écrits
     */
    void filesWrittenChanged(int nbFiles);

private :
    /**
     * @brief _bufferPool le pool de fichiers compressés
     */
    ZippedBufferPool& _bufferPool;
    /**
     * @brief _destinationFolder le dossier de destination des fichiers décompressés
     */
    QString& _destinationFolder;

};

#endif // UNZIPWRITER_H
