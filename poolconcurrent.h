#ifndef POOLTEST_H
#define POOLTEST_H
#include <QString>
#include <QVector>
#include "zippedbuffer.h"
#include"zippedpool.h"

/**
 * @brief The PoolConcurrent class représente la liste des fichiers compressés
 * récupérés du fichier archive pour la version QtConcurrent
 */
class PoolConcurrent : public QVector<ZippedBuffer*>
{
public:
    /**
     * @brief PoolConcurrent construit un nouveau pool
     * @param zippedFilename le nom du fichier compressé
     * @param password le mot de passe fourni par l'utilisateur
     * @param folder le dossier de destination pour créer les répertoires
     */
    PoolConcurrent(const QString &zippedFilename,const QString &password,QString folder);
    /**
     * @brief tryGet permet de récupérer un fichier de la liste
     * @return un pointer vers un ZippedBuffer si la liste n'est pas vide,
     * un pointer null sinon
     */
    ZippedBuffer* tryGet();
private:
    /**
     * @brief _folder
     */
    QString _folder;
    /**
     * @brief unzipFile permet de parcourir un flux de données
     * corerspondant au fichier zippé
     * @param zippedFilename le nom du fichier zippé
     * @param password le mot de passe fourni par l'utilisateur
     */
    void unzipFile(const QString &zippedFilename,const QString &password);
};

#endif // POOLTEST_H
