#-------------------------------------------------
#
# Project created by QtCreator 2016-05-18T11:08:44
#
#-------------------------------------------------

QT       += widgets testlib

QT       -= gui

TARGET = tst_unittesttest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_unittesttest.cpp \
    ../Szakdolgozat/Model/graph.cpp \
    ../Szakdolgozat/Model/layout.cpp \
    ../Szakdolgozat/Model/model.cpp \
    ../Szakdolgozat/Model/visualizationgraph.cpp \
    ../Szakdolgozat/Model/visualizationvertex.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../Szakdolgozat/Model/basevertex.h \
    ../Szakdolgozat/Model/cluster.h \
    ../Szakdolgozat/Model/graph.h \
    ../Szakdolgozat/Model/layout.h \
    ../Szakdolgozat/Model/model.h \
    ../Szakdolgozat/Model/myvalidator.h \
    ../Szakdolgozat/Model/visualizationgraph.h \
    ../Szakdolgozat/Model/visualizationvertex.h
