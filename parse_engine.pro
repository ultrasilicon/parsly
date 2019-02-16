TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += "-Wno-old-style-cast"


INCLUDEPATH += ./include

SOURCES += \
    src/main.cpp \
    src/engine.cpp \
    packet.cpp


HEADERS += \
    include/json.hpp \
    include/engine.h \
    include/sized_mask.h \
    packet.h

mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

CONFIG += link_pkgconfig
PKGCONFIG += gtest
