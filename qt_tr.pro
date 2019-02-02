#-------------------------------------------------
#
# Project created by QtCreator 2018-02-07T13:35:03
#
#-------------------------------------------------

QT       += core gui printsupport


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = qt_tr
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


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    unit.cpp \
    add2.cpp \
    textbutor.cpp \
    seller.cpp \
    customers.cpp \
    human.cpp \
    humanloader.cpp \
    humanadd.cpp \
    humanedit.cpp \
    unit_loader.cpp \
    unit_edit.cpp \
    options.cpp \
    ini.cpp \
    recive.cpp

HEADERS += \
        mainwindow.h \
    unit.h \
    add2.h \
    textbutor.h \
    seller.h \
    customers.h \
    human.h \
    humanloader.h \
    humanadd.h \
    humanedit.h \
    unit_loader.h \
    unit_edit.h \
    options.h \
    ini.h \
    recive.h

FORMS += \
        mainwindow.ui
