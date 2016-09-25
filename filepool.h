#ifndef FILEPOOL_H
#define FILEPOOL_H
#include <QStringList>
#include <QMutex>
#include <QThread>

/**
 * @brief The FilePool class représente la liste des fichiers à traiter pour la compression
 */
class FilePool : public QStringList
{
public:
    /**
     * @brief FilePool construit un nouveau pool
     * initialise la liste des fichiers à partir du dossier donné en parcourant
     * les sous-dossiers.Il peut être utilisé dés qu'il est construit
     * @param folder le chemin absolu du dossier à compresser
     */
    FilePool(const QString &folder);
    /**
     * @brief tryGet permet de récupérer le nom d'un fichier dans la liste.
     * Retourne une chaine vide s'il n'y a plus d'éléments dans le pool.
     * Le nom retourné est ensuite supprimé de la liste.
     * @return Un nom de fichier ou une chaine vide
     * @note Cette méthode est thread-safe
     */
    QString tryGet();
    /**
     * @brief getFolder permet de récupérer le nom du dossier à compresser
     * @return une référence du nom de dossier
     */
    QString& getFolder();
private :
    /**
     * @brief _folder le nom du chemin absolu vers le dossier
     */
    QString _folder;
    /**
     * @brief findFileInFolderAndSubFolder permet de remplir le pool
     * en parcourant récursivement le dossier et les sous-dossiers
     * @param folder le dossier à parcourir
     * @param relativePath le chemin relatif des sous-dossiers
     * lors du parcours.
     */
    void findFileInFolderAndSubFolder(const QString &folder,QString relativePath);
    /**
     * @brief _mutex utilisé pour rendre thread safe l'accés à la liste des fichiers
     */
    QMutex _mutex;

};

#endif // FILEPOOL_H
