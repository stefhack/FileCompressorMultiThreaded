#ifndef ZIPPEDBUFFER_H
#define ZIPPEDBUFFER_H
#include <QString>

/**
 * @brief The ZippedBuffer class représente un fichier compressé avec son nom et ses données
 */
class ZippedBuffer
{
public:
    /**
     * @brief ZippedBuffer construit un nouveau fichier compressé
     * @param data les données binaires compressées du fichier
     * @param filename le nom du fichier d'origine
     */
    ZippedBuffer(QByteArray &data,const QString &filename);
    ZippedBuffer();
    /**
     * @brief write permet d'écrire dans un flux de données
     * le nom du fichier et les données binaires
     * @param stream le flux dans lequel on veut écrire le fichier
     */
    void write(QDataStream &stream);
    /**
     * @brief read permet de lire le nom du fichier et les données binaires
     * à partir d'un flux de données
     * @param stream le flux à partir duquel on veut les informations
     */
    void read(QDataStream &stream);
    /**
     * @brief getData permet de récupérer les données binaires
     * @return les données binaires compressées
     */
    QByteArray* getData();
    /**
     * @brief getFileName permet de récupérer le nom du fichier
     * @return le nom du fichier
     */
    QString& getFileName();
   private:
    /**
     * @brief _filename le nom du chemin relatif du fichier compressé
     */
    QString _filename;
    /**
     * @brief _dataFileCompressed les données binaires du fichier compressé
     */
    QByteArray _dataFileCompressed;
};

#endif // ZIPPEDBUFFER_H
