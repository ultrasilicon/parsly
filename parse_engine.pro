TEMPLATE = app
CONFIG += console c++1z
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += "-Wno-old-style-cast"


INCLUDEPATH += ./include

SOURCES += \
    src/main.cpp \
    packet.cpp \
    net_stack.cpp \
    src/parse_engine.cpp


HEADERS += \
    include/json.hpp \
    include/sized_mask.h \
    packet.h \
    net_stack.h \
    include/parse_engine.h

mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

CONFIG += link_pkgconfig
PKGCONFIG += gtest
