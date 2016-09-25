#include "poolconcurrent.h"
#include <QFile>
#include <QDir>
#include <QMessageBox>
#include "zippedbuffer.h"
#include <QDebug>
#include "unzipwriter.h"

PoolConcurrent::PoolConcurrent(const QString &zippedFilename,const QString &password,QString folder):_folder(folder)
{
    unzipFile(zippedFilename,password);

}



void PoolConcurrent::unzipFile(const QString &zippedFilename,const QString &password){

    QFile file(zippedFilename);

    QDataStream stream;
    stream.setDevice(&file);

    if(!file.open(QIODevice::ReadOnly)){
        QMessageBox msg;
        msg.setText("Ouverture du fichier zippé impossible !");
        msg.exec();
        return;
    }

    QString passwordFile;
    int nbFiles;
    stream >> passwordFile;
    stream >> nbFiles;

#ifdef DEBUG
    qDebug() << " Reading nb files : " << nbFiles << endl;
    qDebug() << " Reading password file  : " << passwordFile << endl;
#endif

    if(passwordFile != password){
        QMessageBox msg;
        msg.setText("Wrong password , sorry ! Try again");
        msg.exec();
        return;
    }

    while(!stream.atEnd()){

        ZippedBuffer* buffer = new ZippedBuffer();
        buffer->read(stream);
        QString subfolder;
        QDir dir;

        for(int i=buffer->getFileName().length()-1;i>0;--i){
            if((QString(buffer->getFileName().at(i))== QString("\\")) || (QString(buffer->getFileName().at(i))==QString("/")))
            {
                subfolder=buffer->getFileName().left(i);
                dir.mkpath(_folder+subfolder);
                break;
            }
        }


        push_back(buffer);
    }
    file.close();
}

ZippedBuffer* PoolConcurrent::tryGet(){


    ZippedBuffer* zippedbuffer = nullptr;
    if(!this->empty()){

        zippedbuffer = this->first();
        this->remove(0);
    }
    return zippedbuffer;
}
