#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T19:43:21
#
#-------------------------------------------------

QT       -= core gui

TARGET = lemon
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

CONFIG += c++11
CONFIG += silent
CONFIG -= debug_and_release debug_and_release_target

DESTDIR = bin
MOC_DIR = moc
OBJECTS_DIR = obj
UI_DIR = ui
RCC_DIR = rcc

OTHER_FILES += lempar.c

# patched: extension of the result file is changed from .c to .cpp
SOURCES += main.c

# lempar.c has to exist beside lemon.exe
lempar = $$shadowed($$DESTDIR)/lempar.c
copylempar.target = $$lempar
copylempar.commands = $(COPY_FILE) $$shell_path($$PWD/lempar.c) $$shell_path($$lempar)
QMAKE_EXTRA_TARGETS += copylempar
PRE_TARGETDEPS += $$lempar

include(../common.pri)
