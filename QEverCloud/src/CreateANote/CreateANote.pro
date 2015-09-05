load(mgs_project)

TARGET = CreateANote

QT -= gui
QT += network
CONFIG   += console

SOURCES += main.cpp

MGS_MIN_QT_VERSION = 5.0.2

MGS_VERSION = 1.0.0.1
QMAKE_TARGET_COMPANY = mgsxx Software
QMAKE_TARGET_PRODUCT = CreateANote
QMAKE_TARGET_DESCRIPTION =
QMAKE_TARGET_COPYRIGHT = (c) Sergey Skoblikov
RC_ICONS = mainicon.ico

path = $$absolute_path($$PWD/../QEverCloud/include)
path = $$clean_path($$path)
INCLUDEPATH += $$path

win32-msvc* {
  LIB_PREFIX =
  LIB_EXT = .lib
} else { #mingw
  LIB_PREFIX = lib
  LIB_EXT = .a
}

libpath = $${OUT_PWD}/../QEverCloud/bin/$${LIB_PREFIX}QEverCloud$${LIB_EXT}
libpath = $$clean_path($$libpath)


LIBS += $${libpath}
PRE_TARGETDEPS += $${libpath}

win32-msvc* {
    LIBS += kernel32.lib user32.lib gdi32.lib crypt32.lib
}

include($$mgs_ending)
