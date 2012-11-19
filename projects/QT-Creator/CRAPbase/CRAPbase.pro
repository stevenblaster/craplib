TEMPLATE = lib
CONFIG += staticlib
CONFIG -= qt

INCLUDEPATH += ../../../src/crap/
INCLUDEPATH += ../../../lib/
LIBS += -lpthread

QMAKE_CXXFLAGS += -include "precompiled.h"

PRECOMPILED_HEADER += ../../../src/crap/precompiled.h

HEADERS += \
    ../../../src/crap/precompiled.h \
    ../../../src/crap/config.h \
    ../../../src/crap/config/types.h \
    ../../../src/crap/config/threading.h \
    ../../../src/crap/config/simd.h \
    ../../../src/crap/config/processors.h \
    ../../../src/crap/config/platforms.h \
    ../../../src/crap/config/memory.h \
    ../../../src/crap/config/math.h \
    ../../../src/crap/config/endianness.h \
    ../../../src/crap/config/compilers.h \
    ../../../src/crap/container/vector.h \
    ../../../src/crap/container/treenode.h \
    ../../../src/crap/container/stack.h \
    ../../../src/crap/container/queue.h \
    ../../../src/crap/container/pair.h \
    ../../../src/crap/container/map.h \
    ../../../src/crap/container/list.h \
    ../../../src/crap/container/bitset.h \
    ../../../src/crap/container/bitmask.h \
    ../../../src/crap/container/binarytree.h \
    ../../../src/crap/control/zero.h \
    ../../../src/crap/control/time.h \
    ../../../src/crap/control/limits.h \
    ../../../src/crap/control/endian.h \
    ../../../src/crap/control/cpuinfo.h \
    ../../../src/crap/control/copyobject.h \
    ../../../src/crap/control/converter.h \
    ../../../src/crap/control/compare.h \
    ../../../src/crap/control/checkvtable.h \
    ../../../src/crap/control/breakpoints.h \
    ../../../src/crap/control/asserts.h \
    ../../../src/crap/math/random.h \
    ../../../src/crap/math/math.h \
    ../../../src/crap/memory/memorytracker.h \
    ../../../src/crap/memory/memorypool.h \
    ../../../src/crap/memory/allocatormalloc.h \
    ../../../src/crap/memory/allocatordefault.h \
    ../../../src/crap/threading/thread.h \
    ../../../src/crap/threading/sleep.h \
    ../../../src/crap/threading/semaphore.h \
    ../../../src/crap/threading/scopelock.h \
    ../../../src/crap/threading/runnable.h \
    ../../../src/crap/threading/mutex.h \
    ../../../src/crap/types/string.h \
    ../../../src/crap/types/staticstring.h \
    ../../../src/crap/threading/functorthread.h \
    ../../../src/crap/types/vector2.h \
    ../../../src/crap/types/vector3.h \
    ../../../src/crap/types/vector4.h \
    ../../../src/crap/types/matrix3.h \
    ../../../src/crap/types/matrix2.h \
    ../../../src/crap/types/matrix4.h \
    ../../../src/crap/network/addressip4.h \
    ../../../src/crap/network/addressip6.h \
    ../../../src/crap/config/network.h \
    ../../../src/crap/network/headers.h \
    ../../../src/crap/network/sockets.h \
    ../../../src/crap/network/packet.h

SOURCES += \
    ../../../src/crap/control/time.cpp \
    ../../../src/crap/control/cpuinfo.cpp \
    ../../../src/crap/memory/memorytracker.cpp \
    ../../../src/crap/threading/thread.cpp \
    ../../../src/crap/threading/sleep.cpp \
    ../../../src/crap/threading/semaphore.cpp \
    ../../../src/crap/threading/scopelock.cpp \
    ../../../src/crap/threading/runnable.cpp \
    ../../../src/crap/threading/mutex.cpp \
    ../../../src/crap/control/limits.cpp \
    ../../../src/crap/control/zero.cpp \
    ../../../src/crap/container/bitmask.cpp \
    ../../../src/crap/network/addressip4.cpp \
    ../../../src/crap/network/addressip6.cpp \
    ../../../src/crap/network/headers.cpp \
    ../../../src/crap/network/sockets.cpp
