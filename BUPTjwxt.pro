#-------------------------------------------------
#
# Project created by QtCreator 2017-01-24T19:23:42
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BUPTjwxt
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    login.cpp \
    subject.cpp

HEADERS  += mainwindow.h \
    login.h \
    subject.h

FORMS    += mainwindow.ui \
    login.ui

DISTFILES += \
    getCapcha.py \
    login.py \
    getGrade.py \
    getGradeOnTerms.py

RESOURCES +=
