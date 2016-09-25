#ifndef WRITEFILESINFOLDERS_H
#define WRITEFILESINFOLDERS_H
#include "zippedbuffer.h"
#include <QFile>

/**
 * @brief The WriteFilesInFolders class la classe fonction appelée
 * par QT_CONCURRENT
 */
class WriteFilesInFolders
{

public:
    /**
      * @brief WriteFilesInFolders construit
      * @param destinationFolder le dossier  de destination où vont être
      * écrits les sous-dossiers et fichiers décompressés
      */
     WriteFilesInFolders(QString destinationFolder){
         _folder=destinationFolder;
     }
     /**
     * @brief operator () est appelée pour chaque élément de la liste passée en paramètre
     * de QT_CONCURRENT::map
     * Elle permet d'écrire un fichier de la liste et libère la mémoire qui lui est allouée
     * @param buffer un pointer de ZippedBuffer de la liste
     */
    void operator()(ZippedBuffer*& buffer) {
        QFile outFile(_folder+buffer->getFileName());
        outFile.open(QIODevice::WriteOnly);
        outFile.write(qUncompress(*buffer->getData()));
        outFile.close();
        delete buffer;
        buffer = nullptr;
    }
private :
    /**
     * @brief _folder le dossier de destination
     */
    QString _folder;
};

#endif // WRITEFILESINFOLDERS_H
