#-------------------------------------------------
#
# Project created by QtCreator 2016-06-30T13:48:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++11

TARGET = SudokuCSP
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    sudoku.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui
