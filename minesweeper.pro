TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    minesweeper.c \
    menu.c \
    records.c \
    tempo.c

HEADERS += \
    minesweeper.h \
    tempo.h \
    menu.h \
    records.h

