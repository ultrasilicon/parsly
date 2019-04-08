TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp \
    ../common/my_net_stack.cpp

HEADERS += \
    my_net_stack.h \
    ../common/my_net_stack.h

INCLUDEPATH += /usr/local/include

mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

CONFIG += link_pkgconfig
PKGCONFIG += \
    libparsley \
    parsly

