#-------------------------------------------------
#
# Project created by QtCreator 2016-03-02T20:58:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = prog4
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++14

SOURCES += main.cpp\
        mainwindow.cpp \
    world.cpp \
    worldcommand.cpp \
    worldobj.cpp

HEADERS  += mainwindow.h \
    world.h \
    worldcommand.h \
    worldobj.h \
    moveable.h

FORMS    += mainwindow.ui

RESOURCES += \
    Resources.qrc

OTHER_FILES += \
    images/arrow.png \
    images/x.png
