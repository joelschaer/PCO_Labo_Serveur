QT       += core websockets
QT       -= gui

TARGET = fileserver
CONFIG   += console
CONFIG   -= app_bundle
OUTPUT += console

TEMPLATE = app

SOURCES += \
    main.cpp \
    fileserver.cpp \
    filereader.cpp

HEADERS += \
    fileserver.h \
    filereader.h \
    response.h \
    request.h

EXAMPLE_FILES += fileclient.html

