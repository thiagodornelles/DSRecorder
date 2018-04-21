#-------------------------------------------------
#
# Project created by QtCreator 2018-03-05T21:28:46
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = RecorderDS
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += link_pkgconfig
PKGCONFIG += eigen3

INCLUDEPATH += /opt/softkinetic/DepthSenseSDK/include
INCLUDEPATH += /home/thiago/Libraries/rgbd-grabber/include
INCLUDEPATH += /usr/include/pcl-1.8

LIBS += -L/usr/lib
LIBS += -L/home/thiago/Libraries/rgbd-grabber/lib -lrgbd-grabber-ds
LIBS += -L/opt/softkinetic/DepthSenseSDK/lib -lDepthSense
LIBS += -L/opt/softkinetic/DepthSenseSDK/lib -lDepthSensePlugins
LIBS += -L/opt/softkinetic/DepthSenseSDK/lib -lturbojpeg
LIBS += -lboost_system
LIBS += -lopencv_core \
        -lopencv_imgproc \
        -lopencv_highgui

SOURCES += \
        main.cpp \
        mainwindow.cpp

HEADERS += \
        mainwindow.h

FORMS += \
        mainwindow.ui
