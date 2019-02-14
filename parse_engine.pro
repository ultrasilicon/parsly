TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ./include

SOURCES += \
    src/main.cpp \
    src/engine.cpp


HEADERS += \
    include/json.hpp \
    include/engine.h \
    include/sized_mask.h

mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

CONFIG += link_pkgconfig
#PKGCONFIG += libuv
