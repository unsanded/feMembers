#-------------------------------------------------
#
# Project created by QtCreator 2014-05-16T16:15:44
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = femembers
TEMPLATE = app

CONFIG += c++11

SOURCES += main.cpp\
        memberlist.cpp \
    databaseconnection.cpp \
    memberlistmodel.cpp \
    qmemberlistview.cpp \
    memberdelegate.cpp \
    exportcsvform.cpp \
    addmemberdialog.cpp \
    member.cpp

HEADERS  += memberlist.h \
    databaseconnection.h \
    memberlistmodel.h \
    qmemberlistview.h \
    memberdelegate.h \
    exportcsvform.h \
    addmemberdialog.h \
    member.h

FORMS    += memberlist.ui \
    exportcsvform.ui \
    addmemberdialog.ui

RESOURCES +=
