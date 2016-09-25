#ifndef WRITER_H
#define WRITER_H
#include "zippedbufferpool.h"
#include <QThread>

/**
 * @brief The Writer class représente le thread qui va permettre d'écrire le
 * fichier compressé
 */
class Writer : public QThread
{
     Q_OBJECT
public:
    /**
     * @brief Writer construit un nouveau Writer
     * @param bufferPool le pool de fichier zippé
     * @param zippedFileName le nom du fichier zippé
     * @param password le mot de passe de l'archive
     */
    Writer(ZippedBufferPool &bufferPool,const QString &zippedFileName,const QString password);
    /**
     * @brief run est appelée au démarrage du thread.Elle commence à écrire le fichier archive
     * avec le mot de passe et le nombre total de fichiers à l'origine.
     * Elle récupère  du bufferPool les ZippedBuffer tant qu'il y en a.
     */
    virtual void run();
    /**
     * @brief setNbFiles permet de changer l'information du nombre de fichiers écrits
     * @param nbFilesToZip le nombre total de fichiers dans le dossier d'origine
     */
    void setNbFiles(int nbFilesToZip);

signals:
    /**
     * @brief filesWrittenChanged permet de signaler un nouveau fichier écrit
     * @param nbFiles le nombre de fichiers écrits jusqu'à présent
     */
    void filesWrittenChanged(int nbFiles);

private :
    /**
     * @brief _bufferPool le buffer contenant les ZippedBuffer
     *
     */
    ZippedBufferPool& _bufferPool;
    /**
     * @brief _stream le flux de données permettant d'écrire le fichier compressé
     */
    QDataStream _stream;
    /**
     * @brief _zippedFileName le nom du fichier zippé
     */
    QString _zippedFileName;
    /**
     * @brief _password le mot de passe à enregistrer dans le flux de données du fichier
     * @note permet sécuriser l'archive en vérifiant cett information à l'ouverture
     */

    QString _password;
    /**
     * @brief _nbFilesToZip le nombre fichiers(dans le dossier d'origine)
     * à écrire dans le flux de données du fichier
     * @note permet de retrouver cette information à l'ouverture du fichier
     */
    int _nbFilesToZip;
};

#endif // WRITER_H
