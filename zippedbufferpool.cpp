#include "zippedbufferpool.h"
#include <memory>
#include "zippedbuffer.h"
#include <QPair>
#include <QDebug>

using namespace std;


ZippedBufferPool::ZippedBufferPool()
{
    _allZippersHasDone=false;
}


void ZippedBufferPool::put(ZippedBuffer* buffer){
    QMutexLocker locker(&_mutex);
    _dataCompressed.push_back(buffer);
    _fileAdded.wakeOne();
}


vector<ZippedBuffer*> ZippedBufferPool::getDataCompressed(){
    return _dataCompressed;
}

unique_ptr<ZippedBuffer> ZippedBufferPool::tryGet(){


    unique_ptr<ZippedBuffer> pair=nullptr;

    QMutexLocker locker(&_mutex);

    if(_allZippersHasDone==false &&  _dataCompressed.size()==0){
            _fileAdded.wait(&_mutex);

    }
    if(_dataCompressed.size()!=0){

         ZippedBuffer* buffer = _dataCompressed.front();
         pair = unique_ptr<ZippedBuffer>(buffer);
         _dataCompressed.erase(_dataCompressed.begin(),_dataCompressed.begin()+1);
    }    

    return pair;
}

void ZippedBufferPool::done(){
    _allZippersHasDone = true;
    _fileAdded.wakeAll();

}

int ZippedBufferPool::size(){

    return _dataCompressed.size();
}
