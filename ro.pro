#-------------------------------------------------
#
# Project created by QtCreator 2015-06-06T13:04:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ro
TEMPLATE = app


SOURCES += main.cpp\
    graphics/piece.cpp \
    graphics/rowindow.cpp \
    game_logic/reversi.cpp \
    artificial_intelligence/artificial_intelligence.cpp

HEADERS  += graphics/piece.h \
    graphics/rowindow.h \
    game_logic/reversi.h \
    artificial_intelligence/artificial_intelligencei.h

FORMS    += graphics/rowindow.ui
