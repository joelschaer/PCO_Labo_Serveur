QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp \
    requesthandler.cpp \
    responsedispatcherthread.cpp \
    hoaremonitor.cpp \
    requestdispatcherthread.cpp \
    requestprocess.cpp \
    threadpool.cpp \
    thread.cpp \
    readerwritercache.cpp \
    readerwriterlock.cpp \

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    abstractbuffer.h \
    request.h \
    requesthandler.h \
    responsedispatcherthread.h \
    hoaremonitor.h \
    buffern.h \
    requestdispatcherthread.h \
    requestprocess.h \
    threadpool.h \
    runnable.h \
    readerwritercache.h \
    readerwriterlock.h

EXAMPLE_FILES += fileclient.html

