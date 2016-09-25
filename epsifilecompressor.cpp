#include "epsifilecompressor.h"
#include <vector>
#include <QFile>
#include "filepool.h"
#include "zippedbufferpool.h"
#include "writer.h"
#include <iostream>
#include <memory>
#include "zipper.h"
#include <QElapsedTimer>
#include <QDebug>
#include <QDir>
#include <QtConcurrent>
#include <QMessageBox>
#include <QProgressDialog>
#include <writefilesinfolders.h>
#include "zippedpool.h"
#include "unzipwriter.h"
#include "unzipper.h"
#include "poolconcurrent.h"

using  std::unique_ptr;
using  std::vector;



EpsiFileCompressor::EpsiFileCompressor(int nbThreads,int compressionLevel)
    :_nbThreadsToRun(nbThreads),_compressionLevel(compressionLevel)
{

}



void EpsiFileCompressor::compress(const QString &folder, const QString &zippedFileName,QString password){

    QProgressDialog dialog;
    dialog.setLabelText(QString("Zipping..."));

    QElapsedTimer timer;
    timer.start();

    FilePool pool(folder);
    ZippedBufferPool bufferPool;

    Writer writer(bufferPool,zippedFileName,password);
    writer.setNbFiles(pool.size());
    writer.start();

#ifdef DEBUG
    qDebug()<< "Building pool"<< endl;
#endif

    vector<unique_ptr<Zipper>> listZippers;

    dialog.setRange(0,pool.size());
    QObject::connect(&writer, SIGNAL(filesWrittenChanged(int)), &dialog, SLOT(setValue(int)));

    for(int i=1;i<=_nbThreadsToRun;++i){
        auto zipper = new Zipper(pool,bufferPool,_compressionLevel);
        listZippers.push_back(unique_ptr<Zipper>(zipper));
        listZippers.back()->start();
    }

    dialog.exec();

    while(listZippers.empty() == false) {
        listZippers.front()->wait();
        listZippers.erase(listZippers.begin(),listZippers.begin()+1);
    }
#ifdef DEBUG
    qDebug()<< " ZIPPERS DONE !"<<endl;
#endif

    bufferPool.done();
    writer.wait();

#ifdef DEBUG
    qDebug()<< "Done zipping in " << timer.elapsed()<< "ms";
#endif DEBUG
}

void EpsiFileCompressor::uncompressMultiThread(const QString &zippedFileName,QString &destinationFolder, QString password){

#ifdef DEBUG
    qDebug()<< "Uncompress multi thread..."<< endl;
#endif

    QProgressDialog dialog;
    dialog.setLabelText(QString("Unzipping..."));


    QElapsedTimer timer;
    timer.start();

    ZippedBufferPool bufferPool;
    ZippedPool pool(zippedFileName,password);
    UnzipWriter writer(bufferPool,destinationFolder);

    if(pool.hasWrongPasswordProvided()) return;
    dialog.setRange(0,pool.getNbFiles());
    pool.start();
    writer.start();

    QObject::connect(&writer, SIGNAL(filesWrittenChanged(int)), &dialog, SLOT(setValue(int)));

    vector<unique_ptr<Unzipper>> unzippers;

    for(int i=1;i<=_nbThreadsToRun;++i){
        auto unzipper = new Unzipper(pool,bufferPool);
        unzippers.push_back(unique_ptr<Unzipper>(unzipper));
        unzippers.back()->start();
    }

    dialog.exec();

    pool.wait();
    while(unzippers.empty() == false) {
        unzippers.front()->wait();
        unzippers.erase(unzippers.begin(),unzippers.begin()+1);
    }
#ifdef DEBUG
    qDebug()<< " UNZIPPERS DONE !"<<endl;
#endif

    bufferPool.done();

    writer.wait();

#ifdef DEBUG
    qDebug()<< "Done unzipping  in " << timer.elapsed()<< "ms";
#endif

}




void EpsiFileCompressor::uncompressConcurrent(const QString &zippedFileName, QString &destinationFolder,QString password){

#ifdef DEBUG
    qDebug()<< "Starting unzipping with QtConcurrent"<< endl;
#endif

    QFutureWatcher<void> futureWatcher;
    PoolConcurrent pool(zippedFileName,password,destinationFolder);
    if(pool.isEmpty()) return;

    QProgressDialog dialog;
    dialog.setLabelText(QString("Unzipping..."));
    dialog.setRange(0,pool.size());

    QObject::connect(&dialog, SIGNAL(canceled()), &futureWatcher, SLOT(cancel()));
    QObject::connect(&futureWatcher, SIGNAL(progressRangeChanged(int,int)), &dialog, SLOT(setRange(int,int)));
    QObject::connect(&futureWatcher, SIGNAL(progressValueChanged(int)), &dialog, SLOT(setValue(int)));

    QElapsedTimer timer;
    timer.start();

    futureWatcher.setFuture(QtConcurrent::map(pool,WriteFilesInFolders(destinationFolder)));
    dialog.exec();
    futureWatcher.waitForFinished();

#ifdef DEBUG
    qDebug()<< "Done unzipping with QtConcurrent in " << timer.elapsed()<< "ms";
#endif
}







