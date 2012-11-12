TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../../../src/crap/
INCLUDEPATH += ../../../lib/unittest/
INCLUDEPATH += ../../../lib/
INCLUDEPATH += ../../../src/crapunittests/

QMAKE_CXXFLAGS += -include "unittest_precompiled.h"

PRECOMPILED_HEADER += ../../../src/crapunittests/unittest_precompiled.h

SOURCES += \
    ../../../src/crapunittests/main.cpp \
    ../../../src/crapunittests/config_compilers.cpp \
    ../../../src/crapunittests/config_endianess.cpp \
    ../../../src/crapunittests/config_math.cpp \
    ../../../src/crapunittests/config_memory.cpp \
    ../../../src/crapunittests/config_platforms.cpp \
    ../../../src/crapunittests/config_processors.cpp \
    ../../../src/crapunittests/config_simd.cpp \
    ../../../src/crapunittests/config_threading.cpp \
    ../../../src/crapunittests/config_types.cpp \
    ../../../src/crapunittests/container_binarytree.cpp \
    ../../../src/crapunittests/types_string.cpp \
    ../../../src/crapunittests/types_staticstring.cpp \
    ../../../src/crapunittests/threading_thread.cpp \
    ../../../src/crapunittests/threading_sleep.cpp \
    ../../../src/crapunittests/threading_semaphore.cpp \
    ../../../src/crapunittests/threading_scopelock.cpp \
    ../../../src/crapunittests/threading_runnable.cpp \
    ../../../src/crapunittests/threading_mutex.cpp \
    ../../../src/crapunittests/math_random.cpp \
    ../../../src/crapunittests/math_math.cpp \
    ../../../src/crapunittests/control_zero.cpp \
    ../../../src/crapunittests/control_time.cpp \
    ../../../src/crapunittests/control_limits.cpp \
    ../../../src/crapunittests/control_endian.cpp \
    ../../../src/crapunittests/control_cpuinfo.cpp \
    ../../../src/crapunittests/control_copyobject.cpp \
    ../../../src/crapunittests/control_converter.cpp \
    ../../../src/crapunittests/control_compare.cpp \
    ../../../src/crapunittests/control_checkvtable.cpp \
    ../../../src/crapunittests/control_breakpoints.cpp \
    ../../../src/crapunittests/control_asserts.cpp \
    ../../../src/crapunittests/container_vector.cpp \
    ../../../src/crapunittests/container_treenode.cpp \
    ../../../src/crapunittests/container_stack.cpp \
    ../../../src/crapunittests/container_queue.cpp \
    ../../../src/crapunittests/container_pair.cpp \
    ../../../src/crapunittests/container_map.cpp \
    ../../../src/crapunittests/container_list.cpp \
    ../../../src/crapunittests/container_bitset.cpp \
    ../../../src/crapunittests/container_bitmask.cpp \
    ../../../src/crapunittests/threading_functorthread.cpp \
    ../../../src/crapunittests/types_vector2.cpp \
    ../../../src/crapunittests/types_vector3.cpp \
    ../../../src/crapunittests/types_vector4.cpp \
    ../../../src/crapunittests/types_matrix3.cpp \
    ../../../src/crapunittests/types_matrix2.cpp \
    ../../../src/crapunittests/types_matrix4.cpp \
    ../../../src/crapunittests/network_addressip4.cpp


unix|win32: LIBS += -L$$PWD/../../../bin/crapbase -lCRAPbase

INCLUDEPATH += $$PWD/../../../bin/crapbase
DEPENDPATH += $$PWD/../../../bin/crapbase

win32: PRE_TARGETDEPS += $$PWD/../../../bin/crapbase/CRAPbase.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../bin/crapbase/libCRAPbase.a

unix|win32: LIBS += -L$$PWD/../../../bin/unittest -lUnitTest

INCLUDEPATH += $$PWD/../../../bin/unittest
DEPENDPATH += $$PWD/../../../bin/unittest

win32: PRE_TARGETDEPS += $$PWD/../../../bin/unittest/UnitTest.lib
else:unix: PRE_TARGETDEPS += $$PWD/../../../bin/unittest/libUnitTest.a

HEADERS += \
    ../../../src/crapunittests/unittest_precompiled.h
