#-------------------------------------------------
#
# Project created by QtCreator 2018-10-02T16:45:03
#
#-------------------------------------------------

QT       += core gui
QT += sql
RC_ICONS += Double.ico


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = calculator
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

RESOURCES += \
    picture.qrc
#RC_FILE += return.rc
