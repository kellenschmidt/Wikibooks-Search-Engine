#-------------------------------------------------
#
# Project created by QtCreator 2016-04-29T02:58:31
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GUISearchEngine
TEMPLATE = app
CXXFLAGS += -std=c++0x
CXXFLAGS += -O3

SOURCES += main.cpp\
        guiuserinterface.cpp \
    avltree.cpp \
    documentparser.cpp \
    indexhandler.cpp \
    myhash.cpp \
    pagelocation.cpp \
    porter2_stemmer.cpp \
    queryprocessor.cpp \
    userinterface.cpp \
    wordref.cpp \
    xmlfile.cpp \
    documentdialog.cpp \
    statsdialog.cpp

HEADERS  += guiuserinterface.h \
    avltree.h \
    documentparser.h \
    indexhandler.h \
    indexinterface.h \
    myhash.h \
    pagelocation.h \
    porter2_stemmer.h \
    queryprocessor.h \
    rapidxml_print.hpp \
    rapidxml.hpp \
    userinterface.h \
    wordref.h \
    xmlfile.h \
    documentdialog.h \
    statsdialog.h

FORMS    += guiuserinterface.ui \
    documentdialog.ui \
    statsdialog.ui

RESOURCES += \
    guiresources.qrc
