TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += \
        main.cpp

mac {
    PKG_CONFIG = /usr/local/bin/pkg-config
}

INCLUDEPATH += /usr/local/include

CONFIG += link_pkgconfig
PKGCONFIG += \
    libparsley \
    parsly

