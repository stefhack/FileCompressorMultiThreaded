#ifndef EPSIFILECOMPRESSOR_H
#define EPSIFILECOMPRESSOR_H
#include <QString>
#include <QByteArray>
#include "epsifilecompressor.h"
#include <QThread>
#include <vector>
#include "zippedbuffer.h"
#include <QFile>
using std::vector;
/**
 * @brief La classe EpsiFileCompressor représente le compresseur /décompresseur
 *
 */
class EpsiFileCompressor :public QObject
{
    Q_OBJECT
public:


    /**
     * @brief EpsiFileCompressor construit un nouveau compresseur/décompresseur
     * @param nbThreads le nombre de threads que l'on veut éxécuter
     * @param compressionLevel le niveau de compression
     */
    EpsiFileCompressor(int nbThreads,int compressionLevel);
    /**
     * @brief compress permet de compresser un dossier en un fichier
     *
     * @param folder le chemin absolu du dossier à compresser
     * @param zippedFileName le nom du fichier compressé avec pour extension : ecf
     * @param password le mot de passe du fichier compressé que l'on veut protéger
     */
    void compress(const QString &folder,const QString &zippedFileName,QString password);
    /**
     * @brief uncompressConcurrent permet de décompresser le fichier zippé
     * en multi-thread avec QtConcurrent
     * @param zippedFileName le nom du fichier zippé
     * @param destinationFolder le chemin absolu du dossier où décompresser le fichier
     * @param password le mot de passe du fichier à dézipper
     */
    void uncompressConcurrent(const QString &zippedFileName,QString &destinationFolder,QString password);
    /**
     * @brief uncompressMultiThread permet de décompresser le fichier zippé
     * en multi-thread (avec QMutex)
     * @param zippedFileName le nom du fichier zippé
     * @param destinationFolder le chemin absolu du dossier où décompresser le fichier
     * @param password le mot de passe du fichier à dézipper
     */
    void uncompressMultiThread(const QString &zippedFileName,QString &destinationFolder,QString password);    

private :
    /**
     * @brief _nbThreadsToRun le nombre de threads
     * @note pour la compression
     * et la décompression (uncompressMultiThread seulement)
     */
    int _nbThreadsToRun;
    /**
     * @brief _compressionLevel le niveau de compression du fichier à zipper
     * @note Ne sert que pour la compression
     */
    int _compressionLevel;


};

#endif // EPSIFILECOMPRESSOR_H
