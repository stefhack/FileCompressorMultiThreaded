#ifndef ZIPPEDBUFFERPOOL_H
#define ZIPPEDBUFFERPOOL_H
#include "zippedbuffer.h"
#include "QPair"
#include <QWidget>
#include "memory"
#include <QMutex>
#include <QWaitCondition>

using  std::vector;
using std::unique_ptr;

/**
 * @brief The ZippedBufferPool class représente le pool de fichiers compressés
 */
class ZippedBufferPool
{

public:
    /**
     * @brief ZippedBufferPool construit un nouveau pool de fichiers compressés
     * en initialisant le booléen _allZippersHasDone à false
     */
    ZippedBufferPool();
    /**
     * @brief put permet de rajouter un nouveau fichier compressé à la liste
     * @param buffer un pointer vers le ZippedBuffer représentant le fichier compressé
     */
    void put(ZippedBuffer* buffer);
    /**
     * @brief tryGet permet de récupérer un fichier dans le pool tant
     * qu 'il y en a
     * @return
     * @note méthode thread-safe
     */
    unique_ptr<ZippedBuffer> tryGet();
    /**
     * @brief getDataCompressed
     * @return
     */
    vector<ZippedBuffer*> getDataCompressed();
    /**
     * @brief size permet de connaitre la taille du pool
     * @return  la taille de la liste
     */
    int size();
    /**
     * @brief done permet de signaler au thread du Writer accédant à la méthode tryGet
     * que  tous les zippers ont fini leur éxécution
     */
    void done();
    /**
      * @brief _allZippersHasDone false tant que les zippers n'ont pas terminés, true sinon
      */
     bool _allZippersHasDone;
private :
     /**
     * @brief _dataCompressed la liste des fichiers compressés
     */
    vector<ZippedBuffer*> _dataCompressed;
    /**
     * @brief _mutex utilisé pour rendre thread safe l'accés à la liste des fichiers
     */
    QMutex _mutex;
    /**
      * @brief _fileAdded représente la condition d'attente d'un thread voulant accéder à un fichier
      * du buffer pool : lorsqu'il n'y a pas d'éléments dans la liste il attend et peut y accéder lorsqu'il est réveillé
      * par l'ajout d'un nouvel élément dans la liste ou à la fin quand tous les zippers ont terminé.
      *
      */
     QWaitCondition _fileAdded;

};

#endif // ZIPPEDBUFFERPOOL_H
