#ifndef ZIPPEDPOOL_H
#define ZIPPEDPOOL_H
#include <QMutex>
#include <QString>
#include <QVector>
#include "zippedbuffer.h"
#include <QThread>
#include <QWaitCondition>
#include <QFile>
#include <QDataStream>

/**
 * @brief The ZippedPool class représente la liste des fichiers compressés
 * récupérés du fichier archive
 */
class ZippedPool : public QVector<ZippedBuffer*>,public QThread
{



public:
    /**
     * @brief ZippedPool construit une nouvelle liste des fichiers compressés à
     * partir du fichier archive
     * @param zippedFilename le nom du fichier archivé
     * @param password le mot de passe du fichier archivé
     */
    ZippedPool(const QString &zippedFilename,const QString &password);
    /**
     * @brief run est appelé au démarrage du thread.Appelle la méthode unzipFile()
     * et une fois terminée signale aux threads accédant à la méthode tryGet()
     * que le parcours du fichier zippé est terminé
     */

    virtual void run();
    /**
     * @brief tryGet permet de récupérer  un ZippedBuffer de la liste
     * @return un pointer vers un ZippedBuffer
     */
    ZippedBuffer* tryGet();
    /**
     * @brief getNbFiles permet de récupérer le nombre de fichiers contenus
     * dans l'archive
     * @return le nombre de fichiers
     * @note méthode thread-safe
     */
    int getNbFiles();
    /**
     * @brief hasWrongPasswordProvided
     * @return true si le mot de passe fourni
     * correspond à celui de l'archive , false sinon
     */

    bool hasWrongPasswordProvided();
private:
    /**
     * @brief unzipFile parcours le flux de données , récupère le nombre
     * de fichiers contenus ainsi que le mot de passe. Les noms de fichiers et leurs données
     * sont ajoutés à la liste
     * @param zippedFilename le nom du fichier compressé
     * @param password le mot de passe du fichier
     */
    void unzipFile();
    /**
    * @brief _mutex utilisé pour rendre thread safe l'accés à la liste des fichiers
    */
   QMutex _mutex;  
   /**
    * @brief _filename le nom fichier archivé
    */
   QString _filename;
   /**
    * @brief _password le mot de passe de l'archive
    */
   QString _password;
   /**
     * @brief _fileAdded représente la condition d'attente d'un thread voulant accéder à un fichier
     * du pool : lorsqu'il n'y a pas d'éléments dans la liste il attend et peut y accéder lorsqu'il est réveillé
     * par l'ajout d'un nouvel élément dans la liste ou à la fin quand tous les éléments ont pu être rajoutés.
     *
     */
    QWaitCondition _fileAdded;
    /**
     * @brief _done false tant que tous les fichiers du stream n'ont pas été récupérés
     * @note Passé à true dans la méthode run une fois la méthode unzipFile() terminée.
     */
    bool _done;
    /**
     * @brief _nbFiles le nombre de fichier de l'archive traité
     */
    int _nbFiles;
    /**
     * @brief _stream le flux de données du fichier compressé
     */
    QDataStream _stream;
    /**
     * @brief _file le fichier compressé
     */
    QFile _file;
    /**
     * @brief _wrongPasswordProvided true si le mot de passe fourni
     * correspond à celui de l'archive , false sinon
     */
    bool _wrongPasswordProvided;
};

#endif // ZIPPEDPOOL_H
