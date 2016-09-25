#include "writer.h"
#include <QFile>
#include <QDebug>

Writer::Writer(ZippedBufferPool& bufferPool,const QString &zippedFileName,const QString password)
    :_bufferPool(bufferPool),_zippedFileName(zippedFileName),_password(password)
{

}


void Writer::run(){

    QFile fileCompressed(_zippedFileName);
    fileCompressed.open(QIODevice::WriteOnly);
    QDataStream stream(&fileCompressed);
    stream << _password;
    stream << _nbFilesToZip;


#ifdef DEBUG
    qDebug()<< " writer NB FILES : "<< _nbFilesToZip<<endl;
    qDebug()<< "Writing password : "<< _password <<" into file : "<<_zippedFileName << endl;
#endif

    unique_ptr<ZippedBuffer> zipBuffer = _bufferPool.tryGet();
    int nbFilesWritten = 0;

    while(zipBuffer != nullptr){
        zipBuffer->write(stream);

#ifdef DEBUG
        qDebug() << "Writing : " << zipBuffer->getFileName();
#endif

        ++nbFilesWritten;
        emit filesWrittenChanged(nbFilesWritten);
        zipBuffer =_bufferPool.tryGet();
    }

    fileCompressed.close();
}

void Writer::setNbFiles(int nbFilesToZip){
    _nbFilesToZip=nbFilesToZip;
}


