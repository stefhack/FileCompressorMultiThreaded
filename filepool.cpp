#include "filepool.h"
#include <QDir>
#include <QFileInfo>
#include <QDebug>
#include <QMutexLocker>

FilePool::FilePool(const QString &folder)
{
    _folder=folder;
    findFileInFolderAndSubFolder(folder,"");
}


void FilePool::findFileInFolderAndSubFolder(const QString &folder,QString relativePath){
    QDir dir(folder);
    dir.setFilter(QDir::NoDotAndDotDot);
    QList<QFileInfo> listInfos = dir.entryInfoList(QDir::AllEntries | QDir::NoDotAndDotDot);

    for(QFileInfo info : listInfos){

        if(info.isDir()){
            QString foldername =info.fileName();
            QString folderpath = dir.absolutePath()+"/"+foldername;
            QString newRelativePath = relativePath+"/"+foldername;
            findFileInFolderAndSubFolder(folderpath,newRelativePath);
        }
        else{
            append(relativePath+"/"+info.fileName());

#ifdef DEBUG
            qDebug() << "Adding to pool : " << relativePath+"/"+info.fileName() << endl;
#endif
        }

    }

}

QString FilePool::tryGet(){
    QString filename = "";

    QMutexLocker locker(&_mutex);

    if(!this->isEmpty()){
        filename = this->first();
        this->removeFirst();
    }
    return filename;
}

QString& FilePool::getFolder(){
    return _folder;
}
