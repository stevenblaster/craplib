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


unix:!macx: LIBS += -L$$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/ -lCRAPlibrary

INCLUDEPATH += $$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/
DEPENDPATH += $$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/libCRAPlibrary.a

unix:!macx: LIBS += -ldl
unix:!macx: LIBS += -lpthread
unix:!macx: LIBS += -lGLU
