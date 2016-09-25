#ifndef UNZIPPER_H
#define UNZIPPER_H
#include <QThread>
#include "zippedpool.h"
#include "zippedbufferpool.h"
#include <QMutex>
#include "poolconcurrent.h"

/**
 * @brief The Unzipper class représente un décompresseur de fichiers
 */
class Unzipper : public QThread
{
public:
    /**
     * @brief Unzipper construit un nouveau décompresseur de fichiers
     * @param pool le pool de fichiers compressés
     * @param bufferPool le pool de fichier décompressés
     */
    Unzipper(ZippedPool &pool,ZippedBufferPool &bufferPool);
    /**
      * @brief run est appelée au démarrage du thread.
      * Elle récupère un fichier compressé du ZippedPool , compresse ses données
      *  et l'ajoute à la liste du ZippedBufferPool
      */

     virtual void run();
    /**
     * @brief unzip permet de décompresser un fichier et l'ajoute à liste du ZippedBufferPool
     * @param zippedbuffer
     */
    void unzip(ZippedBuffer* zippedbuffer);
private :
    /**
    * @brief _pool représente la liste des fichiers avec les données compressées
    */
   ZippedPool& _pool;
   /**
    * @brief _bufferPool représente la liste des fichiers avec les données décompressées
    */
   ZippedBufferPool& _bufferPool;

};

#endif // UNZIPPER_H
