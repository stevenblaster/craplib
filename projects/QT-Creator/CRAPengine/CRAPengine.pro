TEMPLATE = lib
CONFIG += staticlib
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += opengl
CONFIG += x11

LIBS += -lpthread

DEFINES += AL_ALEXT_PROTOTYPES
//DEFINES += _GNU_SOURCE=1
DEFINES += AL_LIBTYPE_STATIC
DEFINES += _CRT_SECURE_NO_WARNINGS
LIBS += -ldl

INCLUDEPATH += ../../../../CRAP/source/craplib/include/
INCLUDEPATH += ../../../../CRAP/source/crapengine/include/
INCLUDEPATH += ../../../../CRAP/libraries/glfw/include/
INCLUDEPATH += ../../../../CRAP/libraries/openal/build/Linux/
INCLUDEPATH += ../../../../CRAP/libraries/openal/include/
INCLUDEPATH += ../../../../CRAP/libraries/openal/OpenAL32/Include/
INCLUDEPATH += ../../../../CRAP/libraries/openal/Alc/
INCLUDEPATH += ../../../../CRAP/libraries/glew/include/

SOURCES += \
    ../../../source/crapengine/source/files/wavefile.cpp \
    ../../../source/crapengine/source/files/imagefile.cpp \
    ../../../source/crapengine/source/files/geometryfile.cpp \
    ../../../source/crapengine/source/opengl/texture.cpp \
    ../../../source/crapengine/source/opengl/shader.cpp \
    ../../../source/crapengine/source/opengl/buffer.cpp

HEADERS += \
    ../../../source/crapengine/include/core/component.h \
    ../../../source/crapengine/include/files/wavefile.h \
    ../../../source/crapengine/include/files/imagefile.h \
    ../../../source/crapengine/include/files/geometryfile.h \
    ../../../source/crapengine/include/opengl/texture.h \
    ../../../source/crapengine/include/opengl/shader.h \
    ../../../source/crapengine/include/opengl/buffer.h


unix:!macx: LIBS += -L$$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/ -lCRAPlibrary

INCLUDEPATH += $$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/
DEPENDPATH += $$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../CRAP/build/qt-creator/craplibrary/debug/libCRAPlibrary.a

unix:!macx: LIBS += -ldl
