#include "unzipwriter.h"
#include <QFile>
#include <QDir>
#include <QDebug>
UnzipWriter::UnzipWriter(ZippedBufferPool& bufferPool, QString& destinationFolder):
    _bufferPool(bufferPool),_destinationFolder(destinationFolder)
{

}


void UnzipWriter::run(){

    unique_ptr<ZippedBuffer> buffer = _bufferPool.tryGet();

    int nbFilesWritten=0;

    while(buffer!= nullptr){

        makeDirectory(buffer->getFileName());

        QFile outFile(_destinationFolder+buffer->getFileName());
#ifdef DEBUG
        qDebug()<< "Writing "<< buffer->getFileName()<< endl;
#endif
        outFile.open(QIODevice::WriteOnly);
        outFile.write(*buffer->getData());
        outFile.close();
        ++nbFilesWritten;
        emit filesWrittenChanged(nbFilesWritten);
        buffer = _bufferPool.tryGet();
    }


}


void UnzipWriter::makeDirectory(QString &directoryName){

    QDir dir;
    QString subfolder;

    for(int i=directoryName.length()-1;i>0;--i){
        if((QString(directoryName.at(i))== QString("\\")) || (QString(directoryName.at(i))==QString("/")))
        {
            subfolder=directoryName.left(i);
            dir.mkpath(_destinationFolder+subfolder);
            break;
        }
    }
}
