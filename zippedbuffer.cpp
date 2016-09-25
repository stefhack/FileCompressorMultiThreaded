#include "zippedbuffer.h"

ZippedBuffer::ZippedBuffer(QByteArray &data,const QString &filename):_dataFileCompressed(data),_filename(filename)
{

}

ZippedBuffer::ZippedBuffer(){

}


QByteArray* ZippedBuffer::getData(){
    return &_dataFileCompressed;
}

QString &ZippedBuffer::getFileName(){
    return _filename;
}

void ZippedBuffer::read(QDataStream &stream){    
    stream >> _filename >> _dataFileCompressed;
}


void ZippedBuffer::write(QDataStream &stream){

    stream << _filename;
    stream << _dataFileCompressed;
}
