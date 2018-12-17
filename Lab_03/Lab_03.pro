TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -fpermissive

SOURCES += main.cpp \
    matrix.cpp

HEADERS += \
    matrix.h
