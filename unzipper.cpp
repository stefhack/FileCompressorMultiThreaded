#include "unzipper.h"

Unzipper::Unzipper(ZippedPool &pool,ZippedBufferPool &bufferPool):
    _pool(pool),_bufferPool(bufferPool)
{

}

void Unzipper::run(){

    ZippedBuffer* buffer=_pool.tryGet();

    while(buffer != nullptr){
        unzip(buffer);
        buffer =_pool.tryGet();
    }

}


void Unzipper::unzip(ZippedBuffer* zippedbuffer){
    QByteArray bytesUnCompressed = qUncompress(*zippedbuffer->getData());
    ZippedBuffer* buffer = new ZippedBuffer(bytesUnCompressed,zippedbuffer->getFileName());
    delete zippedbuffer;
    zippedbuffer =nullptr;
    _bufferPool.put(buffer);

}
