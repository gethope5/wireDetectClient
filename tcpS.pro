#-------------------------------------------------
#
# Project created by QtCreator 2017-02-06T20:02:06
#
#-------------------------------------------------

QT       += core gui
QT       += network
QT       += sql
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

TARGET = tcpS-V1.3-0416
TEMPLATE = app
#CONFIG+=console

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += main.cpp\
    cdevicemanager.cpp \
    qcustomplot.cpp\
    subexcelsave.cpp \
    mysqlmodel.cpp \
    mainwindow.cpp \
#    raillinesqlmodel.cpp \
    logindlg.cpp \
    database.cpp \
    devicestatus.cpp \
    multtablefrm.cpp \
    hoverbitmapbtn.cpp

HEADERS  += \
    cdevicemanager.h \
    qcustomplot.h\
    subexcelsave.h \
    mysqlmodel.h \
    mainwindow.h \
#    raillinesqlmodel.h \
    logindlg.h \
    database.h \
    devicestatus.h \
    multtablefrm.h \
    hoverbitmapbtn.h

FORMS    += \
    cdevicemanager.ui \
    mainwindow.ui \
    logindlg.ui \
    multtablefrm.ui

RESOURCES += \
    resource.qrc

RC_FILE   += myico.rc

