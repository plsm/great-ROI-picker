#-------------------------------------------------
#
# Project created by QtCreator 2018-08-07T17:08:19
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = mask-picker
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += link_pkgconfig
PKGCONFIG = opencv

SOURCES += main.cpp\
        main-window.cpp \
    masks/ring-form.cpp \
    masks/ring-graphics.cpp \
    masks/abstract.cpp \
    masks/ring-manager.cpp \
    masks/ring-lock.cpp \
    util-opencv-qt.cpp \
    masks/stadium-form.cpp \
    masks/stadium-graphics.cpp \
    masks/stadium-lock.cpp \
    masks/stadium-manager.cpp

HEADERS  += main-window.hpp \
    masks/ring-form.hpp \
    masks/ring-graphics.hpp \
    masks/abstract.hpp \
    trigonometry.hpp \
    masks/ring-manager.hpp \
    masks/abstract-manager.hpp \
    masks/template-manager.hpp \
    masks/ring-lock.hpp \
    util-opencv-qt.hpp \
    masks/stadium-form.hpp \
    masks/stadium-graphics.hpp \
    masks/stadium-lock.hpp \
    masks/stadium-manager.hpp

FORMS    += main-window.ui \
    masks/ring-form.ui \
    masks/ring-lock.ui \
    masks/stadium-form.ui \
    masks/stadium-lock.ui
