TEMPLATE = lib
CONFIG += staticlib
CONFIG -= qt
CONFIG -= app_bundle
CONFIG += opengl
CONFIG += x11

INCLUDEPATH += ../../../../CRAP/source/craplib/include/
INCLUDEPATH += ../../../../CRAP/libraries/glfw/include/
INCLUDEPATH += ../../../../CRAP/libraries/openal/build/Linux/
INCLUDEPATH += ../../../../CRAP/libraries/openal/include/
INCLUDEPATH += ../../../../CRAP/libraries/openal/OpenAL32/Include/
INCLUDEPATH += ../../../../CRAP/libraries/openal/Alc/
INCLUDEPATH += ../../../../CRAP/libraries/glew/include/
LIBS += -lpthread

DEFINES += AL_ALEXT_PROTOTYPES
//DEFINES += _GNU_SOURCE=1
DEFINES += AL_LIBTYPE_STATIC
DEFINES += _CRT_SECURE_NO_WARNINGS

SOURCES += \
    ../../../source/craplib/source/audio/wavefile.cpp \
    ../../../source/craplib/source/container/bitmask.cpp \
    ../../../source/craplib/source/control/zero.cpp \
    ../../../source/craplib/source/control/limits.cpp \
    ../../../source/craplib/source/control/craptime.cpp \
    ../../../source/craplib/source/control/cpuinfo.cpp \
    ../../../source/craplib/source/files/file.cpp \
    ../../../source/craplib/source/network/networkheaders.cpp \
    ../../../source/craplib/source/network/addressip6.cpp \
    ../../../source/craplib/source/network/addressip4.cpp \
    ../../../source/craplib/source/opengl/openglwindow.cpp \
    ../../../source/craplib/source/opengl/openglkeyboard.cpp \
    ../../../source/craplib/source/threading/sleep.cpp \
    ../../../source/craplib/source/threading/semaphore.cpp \
    ../../../source/craplib/source/threading/scopelock.cpp \
    ../../../source/craplib/source/threading/runthread.cpp \
    ../../../source/craplib/source/threading/runnable.cpp \
    ../../../source/craplib/source/threading/mutex.cpp \
    ../../../libraries/glfw/lib/window.c \
    ../../../libraries/glfw/lib/time.c \
    ../../../libraries/glfw/lib/thread.c \
    ../../../libraries/glfw/lib/tga.c \
    ../../../libraries/glfw/lib/stream.c \
    ../../../libraries/glfw/lib/joystick.c \
    ../../../libraries/glfw/lib/input.c \
    ../../../libraries/glfw/lib/init.c \
    ../../../libraries/glfw/lib/image.c \
    ../../../libraries/glfw/lib/glext.c \
    ../../../libraries/glfw/lib/fullscreen.c \
    ../../../libraries/glfw/lib/enable.c \
    ../../../libraries/glfw/lib/x11/x11_window.c \
    ../../../libraries/glfw/lib/x11/x11_time.c \
    ../../../libraries/glfw/lib/x11/x11_thread.c \
    ../../../libraries/glfw/lib/x11/x11_keysym2unicode.c \
    ../../../libraries/glfw/lib/x11/x11_joystick.c \
    ../../../libraries/glfw/lib/x11/x11_init.c \
    ../../../libraries/glfw/lib/x11/x11_glext.c \
    ../../../libraries/glfw/lib/x11/x11_fullscreen.c \
    ../../../libraries/glfw/lib/x11/x11_enable.c \
    ../../../source/craplib/source/audio/audiodevice.cpp \
    ../../../libraries/openal/OpenAL32/alThunk.c \
    ../../../libraries/openal/OpenAL32/alState.c \
    ../../../libraries/openal/OpenAL32/alSource.c \
    ../../../libraries/openal/OpenAL32/alListener.c \
    ../../../libraries/openal/OpenAL32/alFilter.c \
    ../../../libraries/openal/OpenAL32/alExtension.c \
    ../../../libraries/openal/OpenAL32/alError.c \
    ../../../libraries/openal/OpenAL32/alEffect.c \
    ../../../libraries/openal/OpenAL32/alBuffer.c \
    ../../../libraries/openal/OpenAL32/alAuxEffectSlot.c \
    ../../../libraries/openal/Alc/panning.c \
    ../../../libraries/openal/Alc/mixer_sse.c \
    ../../../libraries/openal/Alc/mixer_c.c \
    ../../../libraries/openal/Alc/mixer.c \
    ../../../libraries/openal/Alc/hrtf.c \
    ../../../libraries/openal/Alc/helpers.c \
    ../../../libraries/openal/Alc/bs2b.c \
    ../../../libraries/openal/Alc/ALu.c \
    ../../../libraries/openal/Alc/alcThread.c \
    ../../../libraries/openal/Alc/alcRing.c \
    ../../../libraries/openal/Alc/alcReverb.c \
    ../../../libraries/openal/Alc/alcModulator.c \
    ../../../libraries/openal/Alc/alcFlanger.c \
    ../../../libraries/openal/Alc/alcEcho.c \
    ../../../libraries/openal/Alc/alcDedicated.c \
    ../../../libraries/openal/Alc/alcConfig.c \
    ../../../libraries/openal/Alc/alcChorus.c \
    ../../../libraries/openal/Alc/ALc.c \
    ../../../libraries/openal/Alc/backends/wave.c \
    ../../../libraries/openal/Alc/backends/oss.c \
    ../../../libraries/openal/Alc/backends/null.c \
    ../../../libraries/openal/Alc/backends/alsa.c \
    ../../../libraries/openal/Alc/backends/pulseaudio.c \
    ../../../libraries/openal/Alc/backends/loopback.c \
    ../../../source/craplib/source/opengl/openglmouse.cpp \
    ../../../source/craplib/source/opengl/opengljoystick.cpp \
    ../../../source/craplib/source/opengl/openglshader.cpp \
    ../../../libraries/glew/src/glew.c \
    ../../../source/craplib/source/opengl/wavefrontfile.cpp \
    ../../../source/craplib/source/opengl/openglvertex.cpp \
    ../../../source/craplib/source/opengl/openglvbo.cpp \
    ../../../source/craplib/source/opengl/opengltexture.cpp \
    ../../../source/craplib/source/opengl/opengldata.cpp

HEADERS += \
    ../../../source/craplib/include/audio/wavefile.h \
    ../../../source/craplib/include/config/config_types.h \
    ../../../source/craplib/include/config/config_threading.h \
    ../../../source/craplib/include/config/config_simd.h \
    ../../../source/craplib/include/config/config_processors.h \
    ../../../source/craplib/include/config/config_platforms.h \
    ../../../source/craplib/include/config/config_network.h \
    ../../../source/craplib/include/config/config_memory.h \
    ../../../source/craplib/include/config/config_math.h \
    ../../../source/craplib/include/config/config_files.h \
    ../../../source/craplib/include/config/config_endianness.h \
    ../../../source/craplib/include/config/config_compilers.h \
    ../../../source/craplib/include/container/vector.h \
    ../../../source/craplib/include/container/treenode.h \
    ../../../source/craplib/include/container/treemap.h \
    ../../../source/craplib/include/container/string.h \
    ../../../source/craplib/include/container/staticstring.h \
    ../../../source/craplib/include/container/stack.h \
    ../../../source/craplib/include/container/queue.h \
    ../../../source/craplib/include/container/pair.h \
    ../../../source/craplib/include/container/map.h \
    ../../../source/craplib/include/container/list.h \
    ../../../source/craplib/include/container/bitset.h \
    ../../../source/craplib/include/container/bitmask.h \
    ../../../source/craplib/include/container/binarytree.h \
    ../../../source/craplib/include/control/zero.h \
    ../../../source/craplib/include/control/limits.h \
    ../../../source/craplib/include/control/endian.h \
    ../../../source/craplib/include/control/craptime.h \
    ../../../source/craplib/include/control/cpuinfo.h \
    ../../../source/craplib/include/control/copyobject.h \
    ../../../source/craplib/include/control/converter.h \
    ../../../source/craplib/include/control/compare.h \
    ../../../source/craplib/include/control/checkvtable.h \
    ../../../source/craplib/include/control/breakpoints.h \
    ../../../source/craplib/include/control/asserts.h \
    ../../../source/craplib/include/files/fileheaders.h \
    ../../../source/craplib/include/files/file.h \
    ../../../source/craplib/include/math/vector4.h \
    ../../../source/craplib/include/math/vector3.h \
    ../../../source/craplib/include/math/vector2.h \
    ../../../source/craplib/include/math/matrix4.h \
    ../../../source/craplib/include/math/matrix3.h \
    ../../../source/craplib/include/math/matrix2.h \
    ../../../source/craplib/include/math/geometry.h \
    ../../../source/craplib/include/math/random.h \
    ../../../source/craplib/include/math/basemath.h \
    ../../../source/craplib/include/memory/memorypool.h \
    ../../../source/craplib/include/memory/allocatorstatic.h \
    ../../../source/craplib/include/memory/allocatormalloc.h \
    ../../../source/craplib/include/memory/allocatordefault.h \
    ../../../source/craplib/include/network/sockets.h \
    ../../../source/craplib/include/network/packet.h \
    ../../../source/craplib/include/network/networkheaders.h \
    ../../../source/craplib/include/network/addressip6.h \
    ../../../source/craplib/include/network/addressip4.h \
    ../../../source/craplib/include/opengl/openglwindow.h \
    ../../../source/craplib/include/opengl/openglkeyboard.h \
    ../../../source/craplib/include/threading/sleep.h \
    ../../../source/craplib/include/threading/semaphore.h \
    ../../../source/craplib/include/threading/scopelock.h \
    ../../../source/craplib/include/threading/runthread.h \
    ../../../source/craplib/include/threading/runnable.h \
    ../../../source/craplib/include/threading/mutex.h \
    ../../../source/craplib/include/threading/functorthread.h \
    ../../../source/craplib/include/crap.h \
    ../../../libraries/glfw/lib/internal.h \
    ../../../source/craplib/include/audio/audiodevice.h \
    ../../../source/craplib/include/opengl/openglmouse.h \
    ../../../libraries/openal/Alc/mixer_defs.h \
    ../../../source/craplib/include/opengl/opengljoystick.h \
    ../../../source/craplib/include/opengl/openglshader.h \
    ../../../source/craplib/include/opengl/wavefrontfile.h \
    ../../../source/craplib/include/opengl/openglvertex.h \
    ../../../source/craplib/include/opengl/openglvbo.h \
    ../../../source/craplib/include/opengl/opengltexture.h \
    ../../../source/craplib/include/opengl/opengldata.h

OTHER_FILES += \
    ../../../libraries/openal/Alc/hrtf_tables.inc
