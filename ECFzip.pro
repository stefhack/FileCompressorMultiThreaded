#-------------------------------------------------
#
# Project created by QtCreator 2015-05-15T10:44:58
#
#-------------------------------------------------

QT       += core gui
QT +=concurrent

QMAKE_CXXFLAGS +=-std=c++11
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ECFzip
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    directoryselector.cpp \
    filepool.cpp \
    zipper.cpp \
    zippedbuffer.cpp \
    zippedbufferpool.cpp \
    writer.cpp \
    epsifilecompressor.cpp \
    zippedpool.cpp \
    unzipper.cpp \
    unzipwriter.cpp \
    poolconcurrent.cpp

HEADERS  += mainwindow.h \
    directoryselector.h \
    filepool.h \
    zipper.h \
    zippedbuffer.h \
    zippedbufferpool.h \
    writer.h \
    epsifilecompressor.h \
    writefilesinfolders.h \
    zippedpool.h \
    unzipper.h \
    unzipwriter.h \
    poolconcurrent.h
