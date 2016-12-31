TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    minesweeper.c \
    menu.c \
    records.c

HEADERS += \
    minesweeper.h \
    menu.h \
    records.h
