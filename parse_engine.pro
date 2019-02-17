TEMPLATE = app
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt
QMAKE_CXXFLAGS += "-Wno-old-style-cast"


INCLUDEPATH += ./include

SOURCES += \
    src/main.cpp \
    src/packet.cpp \
    src/net_stack.cpp \
    src/parse_engine.cpp \
    src/parse_engine_decode_pop.cpp \
    src/parse_engine_encode_pop.cpp


HEADERS += \
    include/json.hpp \
    include/sized_mask.h \
    include/packet.h \
    include/net_stack.h \
    include/parse_engine.h

mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

CONFIG += link_pkgconfig
PKGCONFIG += gtest
