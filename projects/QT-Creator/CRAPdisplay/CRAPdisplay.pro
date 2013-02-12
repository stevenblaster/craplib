TEMPLATE = lib
CONFIG += staticlib
CONFIG -= qt

INCLUDEPATH += ../../../src/crap/
INCLUDEPATH += ../../../lib/
INCLUDEPATH += ../../../lib/glfw/include
INCLUDEPATH += ../../../lib/glfw/lib
INCLUDEPATH += ../../../lib/glfw/lib/x11
LIBS += -lpthread

QMAKE_CXXFLAGS += -include "precompiled.h"

PRECOMPILED_HEADER += ../../../src/crap/precompiled.h

SOURCES += \
    ../../../lib/glfw/lib/joystick.c \
    ../../../lib/glfw/lib/thread.c \
    ../../../lib/glfw/lib/init.c \
    ../../../lib/glfw/lib/time.c \
    ../../../lib/glfw/lib/image.c \
    ../../../lib/glfw/lib/tga.c \
    ../../../lib/glfw/lib/input.c \
    ../../../lib/glfw/lib/stream.c \
    ../../../lib/glfw/lib/window.c \
    ../../../lib/glfw/lib/fullscreen.c \
    ../../../lib/glfw/lib/glext.c \
    ../../../lib/glfw/lib/enable.c \
    ../../../lib/glfw/lib/x11/x11_enable.c \
    ../../../lib/glfw/lib/x11/x11_joystick.c \
    ../../../lib/glfw/lib/x11/x11_keysym2unicode.c \
    ../../../lib/glfw/lib/x11/x11_thread.c \
    ../../../lib/glfw/lib/x11/x11_fullscreen.c \
    ../../../lib/glfw/lib/x11/x11_glext.c \
    ../../../lib/glfw/lib/x11/x11_init.c \
    ../../../lib/glfw/lib/x11/x11_time.c \
    ../../../lib/glfw/lib/x11/x11_window.c \
    ../../../src/crapdisplay/renderwindow.cpp

HEADERS += \
    ../../../lib/glfw/lib/internal.h \
    ../../../lib/glfw/lib/x11/platform.h \
    ../../../src/crapdisplay/renderwindow.h

OTHER_FILES += \
    ../../../lib/glfw/lib/x11/Makefile.x11.in \
    CRAPdisplay.pro.user

