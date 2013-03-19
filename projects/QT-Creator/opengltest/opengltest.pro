TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += opengl
CONFIG += x11

INCLUDEPATH += ../../../../CRAP/source/craplib/include/
LIBS += -lpthread
LIBS += -ldl


SOURCES += \
    ../../../source/opengltest/main.cpp


unix:!macx: LIBS += -L$$PWD/../../../../CRAP/binary/ -lCRAPlibrary

INCLUDEPATH += $$PWD/../../../../CRAP/binary
DEPENDPATH += $$PWD/../../../../CRAP/binary

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../CRAP/binary/libCRAPlibrary.a

unix:!macx: LIBS += -ldl
unix:!macx: LIBS += -lpthread
unix:!macx: LIBS += -lGLU
