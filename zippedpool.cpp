#include "zippedpool.h"
#include <QDir>
#include <QMessageBox>
#include "zippedbuffer.h"
#include <QDebug>


ZippedPool::ZippedPool(const QString &zippedFilename,const QString &password):
    _filename(zippedFilename),_password(password)
{
_done =false;
_wrongPasswordProvided = false;
_file.setFileName(zippedFilename);


  _stream.setDevice(&_file);

if(!_file.open(QIODevice::ReadOnly)){
    QMessageBox msg;
    msg.setText("Ouverture du fichier zippé impossible !");
    msg.exec();
    return;
}

QString passwordFile;

_stream >> passwordFile;
_stream >> _nbFiles;


#ifdef DEBUG
qDebug() << " Reading nb files : " << _nbFiles << endl;
qDebug() << " Reading password file  : " << passwordFile << endl;
#endif

if(passwordFile != password){
    _wrongPasswordProvided= true;
      QMessageBox msg;
      msg.setText("Wrong password , sorry ! Try again");
      msg.exec();
    return;
}

}



void ZippedPool::run(){
unzipFile();
QMutexLocker locker(&_mutex);
_done=true;
_fileAdded.wakeAll();
}

void ZippedPool::unzipFile(){


         while(!_stream.atEnd()){

             ZippedBuffer* buffer = new ZippedBuffer();
             buffer->read(_stream);

              push_back(buffer);
              _fileAdded.wakeOne();
         }
          _file.close();
}

ZippedBuffer* ZippedPool::tryGet(){

QMutexLocker locker(&_mutex);
ZippedBuffer* zippedbuffer = nullptr;

if(!this->empty()){

    zippedbuffer = this->first();
    this->remove(0);
}
else{
     if(_done == false){
    _fileAdded.wait(&_mutex);
    if(!this->empty()){

        zippedbuffer = this->first();
        this->remove(0);
    }
     }
}
return zippedbuffer;
}

int ZippedPool::getNbFiles(){
return _nbFiles;
}

bool ZippedPool::hasWrongPasswordProvided(){
return _wrongPasswordProvided;
}
