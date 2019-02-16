TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += "-Wno-old-style-cast"


INCLUDEPATH += ./include

SOURCES += \
    src/main.cpp \
    packet.cpp \
    net_stack.cpp \
    src/parse_engine.cpp \
    parse_engine_encode_pp.cpp \
    parse_engine_decode_pp.cpp


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
