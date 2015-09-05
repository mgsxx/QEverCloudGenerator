#-------------------------------------------------
#
# Project created by QtCreator 2013-10-09T13:30:07
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = ThriftParser
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



SOURCES += \
    main.cpp \
    Lexer.cpp \
    Parser.cpp \
    thrift_lemon.cpp \
    Generator.cpp

HEADERS += \
    Lexer.h \
    thrift_lemon.h \
    Parser.h \
    ParserHelper.h \
    Generator.h

OTHER_FILES += thrift_lemon.y
lemon = $${OUT_PWD}/../Lemon/bin/lemon
lemon = $$shell_path($$clean_path($$lemon))
lempar = $${OUT_PWD}/../Lemon/bin/lempar.c
lempar = $$shell_path($$clean_path($$lempar))

parser_cpp.target = $$shell_path($$PWD/Parser.cpp)
parser_cpp.depends = $$shell_path($$PWD/thrift_lemon.cpp) $$shell_path($$PWD/thrift_lemon.h)

thrift_lemon_h.target = $$shell_path($$PWD/thrift_lemon.h)
thrift_lemon_h.depends = $$shell_path($$PWD/thrift_lemon.cpp)

thrift_lemon_cpp.target = $$shell_path($$PWD/thrift_lemon.cpp)
thrift_lemon_cpp.depends = $$shell_path($$PWD/thrift_lemon.y) $$files($$shell_path($${lemon}.*)) $$lempar
thrift_lemon_cpp.commands = $$lemon $$shell_path($$PWD/thrift_lemon.y) $$escape_expand(\n\t)echo LEMON have been executed $$escape_expand(\n\t) $(DEL_FILE) $$shell_path($$PWD/thrift_lemon.out)

object_target.target = $(OBJECTS)
object_target.depends = $${parser_cpp.target}

QMAKE_EXTRA_TARGETS += thrift_lemon_h thrift_lemon_cpp parser_cpp object_target
PRE_TARGETDEPS += $${parser_cpp.target}

include(../common.pri)


