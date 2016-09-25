#include "zipper.h"
#include <QFile>
#include <QDebug>

Zipper::Zipper(FilePool &pool,ZippedBufferPool &bufferPool,int compressionLevel)
    :_pool(pool),_bufferPool(bufferPool),_zipLevel(compressionLevel)
{

}



void Zipper::run(){

    QString filename = _pool.tryGet();

    while(filename != ""){
        zip(filename);

#ifdef DEBUG
        qDebug() << "Zipping : " << filename << endl;
#endif

        filename = _pool.tryGet();
    }

}

void Zipper::zip(const QString &filename){

    QString folderToZip = _pool.getFolder();
    QFile file(folderToZip+filename);
    file.open(QIODevice::ReadOnly);

    QByteArray bytesCompressed = qCompress(file.readAll(),_zipLevel);
    ZippedBuffer* bufferZipped = new ZippedBuffer(bytesCompressed,filename);
    _bufferPool.put(bufferZipped);

}
