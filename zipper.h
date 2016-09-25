#ifndef ZIPPER_H
#define ZIPPER_H
#include "QThread"
#include <filepool.h>
#include <zippedbufferpool.h>

/**
 * @brief The Zipper class représente la
 */
class Zipper : public QThread
{
public:
    /**
     * @brief Zipper construit un nouveau zipper
     * @param pool le pool avec la liste des fichiers
     * @param bufferPool la liste des fichiers avec leur nom et données compressés
     * @param compressionLevel le niveau de compression
     */
    Zipper(FilePool &pool,ZippedBufferPool &bufferPool,const int compressionLevel);
    /**
     * @brief zip permet de compressé un fichier à partir de son nom
     * @param filename le nom du fichier à compresser
     */
    void zip(const QString &filename);
    /**
     * @brief run est appelée au démarrage du thread.Elle récupère
     * un nom de fichier du FilePool et le compresse tant qu'il  y a des éléments dans la liste
     */
    virtual void run();
private :
    /**
     * @brief _pool représente la liste des noms de fichiers
     */
    FilePool &_pool;
    /**
     * @brief _bufferPool représente la liste des fichiers (nom et données compressées)
     */
    ZippedBufferPool &_bufferPool;
    /**
     * @brief _mutex utilisé pour rendre thread safe l'accés à la liste des fichiers
     */
    QMutex _mutex;
    /**
     * @brief _zipLevel le niveau de compression
     */
    int  _zipLevel;

};

#endif // ZIPPER_H
