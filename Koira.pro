#-------------------------------------------------
#
# Project created by QtCreator 2016-05-20T16:36:56
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Koira
TEMPLATE = app
CONFIG += c++14


SOURCES += main.cc\
        mainwindow.cc \
    card.cc \
    deck.cc \
    player.cc \
    game.cc \
    cardproxy.cc

HEADERS  += mainwindow.hh \
    card.hh \
    deck.hh \
    player.hh \
    game.hh \
    cardproxy.hh

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

