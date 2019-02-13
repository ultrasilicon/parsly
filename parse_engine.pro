TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../include

SOURCES += main.cpp \
    engine.cpp


HEADERS += \
    engine.h \
    sized_mask.h

mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

CONFIG += link_pkgconfig
#PKGCONFIG += libuv
