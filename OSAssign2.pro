#-------------------------------------------------
#
# Project created by QtCreator 2016-04-19T20:26:35
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OSAssign2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    memoryallocation.cpp \
    process.cpp \
    hole.cpp

HEADERS  += mainwindow.h \
    memoryallocation.h \
    process.h \
    hole.h

FORMS    += mainwindow.ui

RESOURCES += \
    qdarkstyle/style.qrc
