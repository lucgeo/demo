#-------------------------------------------------
#
# Project created by QtCreator 2014-02-27T22:20:49
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tutorial3
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

INCLUDEPATH += /usr/local/include/opencv
LIBS += -L/usr/local/lib
LIBS += -lopencv_core
LIBS += -lopencv_imgproc
LIBS += -lopencv_highgui
LIBS += -lopencv_video
LIBS += -lopencv_features2d
LIBS += -lopencv_objdetect
LIBS += -lopencv_contrib

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
