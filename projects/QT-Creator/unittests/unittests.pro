TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += opengl
CONFIG += x11
CONFIG += dl
CONFIG += glu

INCLUDEPATH += ../../../../CRAP/source/craplib/include/
INCLUDEPATH += ../../../../CRAP/libraries/glfw/include/
INCLUDEPATH += .../../../../CRAP/libraries/glfw/lib/x11/
INCLUDEPATH += ../../../../CRAP/libraries/glfw/lib/
INCLUDEPATH += ../../../../CRAP/libraries/unittest/
LIBS += -lpthread
LIBS += -ldl

SOURCES += \
    ../../../../CRAP/source/unittests/source/threading_thread.cpp \
    ../../../../CRAP/source/unittests/source/threading_sleep.cpp \
    ../../../../CRAP/source/unittests/source/threading_semaphore.cpp \
    ../../../../CRAP/source/unittests/source/threading_scopelock.cpp \
    ../../../../CRAP/source/unittests/source/threading_runnable.cpp \
    ../../../../CRAP/source/unittests/source/threading_mutex.cpp \
    ../../../../CRAP/source/unittests/source/threading_functorthread.cpp \
    ../../../../CRAP/source/unittests/source/network_sockets.cpp \
    ../../../../CRAP/source/unittests/source/network_packet.cpp \
    ../../../../CRAP/source/unittests/source/network_ipaddress6.cpp \
    ../../../../CRAP/source/unittests/source/network_headers.cpp \
    ../../../../CRAP/source/unittests/source/network_addressip4.cpp \
    ../../../../CRAP/source/unittests/source/memory_memorypool.cpp \
    ../../../../CRAP/source/unittests/source/memory_allocatorstatic.cpp \
    ../../../../CRAP/source/unittests/source/memory_allocatormalloc.cpp \
    ../../../../CRAP/source/unittests/source/memory_allocatordefault.cpp \
    ../../../../CRAP/source/unittests/source/math_random.cpp \
    ../../../../CRAP/source/unittests/source/math_math.cpp \
    ../../../../CRAP/source/unittests/source/main.cpp \
    ../../../../CRAP/source/unittests/source/geometry_vector4.cpp \
    ../../../../CRAP/source/unittests/source/geometry_vector3.cpp \
    ../../../../CRAP/source/unittests/source/geometry_vector2.cpp \
    ../../../../CRAP/source/unittests/source/geometry_matrix4.cpp \
    ../../../../CRAP/source/unittests/source/geometry_matrix3.cpp \
    ../../../../CRAP/source/unittests/source/geometry_matrix2.cpp \
    ../../../../CRAP/source/unittests/source/geometry_geometry.cpp \
    ../../../../CRAP/source/unittests/source/files_file.cpp \
    ../../../../CRAP/source/unittests/source/control_zero.cpp \
    ../../../../CRAP/source/unittests/source/control_time.cpp \
    ../../../../CRAP/source/unittests/source/control_limits.cpp \
    ../../../../CRAP/source/unittests/source/control_endian.cpp \
    ../../../../CRAP/source/unittests/source/control_cpuinfo.cpp \
    ../../../../CRAP/source/unittests/source/control_copyobject.cpp \
    ../../../../CRAP/source/unittests/source/control_copyarray.cpp \
    ../../../../CRAP/source/unittests/source/control_converter.cpp \
    ../../../../CRAP/source/unittests/source/control_compare.cpp \
    ../../../../CRAP/source/unittests/source/control_checkvtable.cpp \
    ../../../../CRAP/source/unittests/source/control_breakpoints.cpp \
    ../../../../CRAP/source/unittests/source/control_asserts.cpp \
    ../../../../CRAP/source/unittests/source/container_vector.cpp \
    ../../../../CRAP/source/unittests/source/container_treenode.cpp \
    ../../../../CRAP/source/unittests/source/container_treemap.cpp \
    ../../../../CRAP/source/unittests/source/container_string.cpp \
    ../../../../CRAP/source/unittests/source/container_staticstring.cpp \
    ../../../../CRAP/source/unittests/source/container_staticstack.cpp \
    ../../../../CRAP/source/unittests/source/container_staticqueue.cpp \
    ../../../../CRAP/source/unittests/source/container_stack.cpp \
    ../../../../CRAP/source/unittests/source/container_queue.cpp \
    ../../../../CRAP/source/unittests/source/container_pair.cpp \
    ../../../../CRAP/source/unittests/source/container_map.cpp \
    ../../../../CRAP/source/unittests/source/container_list.cpp \
    ../../../../CRAP/source/unittests/source/container_bitset.cpp \
    ../../../../CRAP/source/unittests/source/container_bitmask.cpp \
    ../../../../CRAP/source/unittests/source/container_binarytree.cpp \
    ../../../../CRAP/source/unittests/source/config_types.cpp \
    ../../../../CRAP/source/unittests/source/config_threading.cpp \
    ../../../../CRAP/source/unittests/source/config_simd.cpp \
    ../../../../CRAP/source/unittests/source/config_processors.cpp \
    ../../../../CRAP/source/unittests/source/config_platforms.cpp \
    ../../../../CRAP/source/unittests/source/config_memory.cpp \
    ../../../../CRAP/source/unittests/source/config_math.cpp \
    ../../../../CRAP/source/unittests/source/config_files.cpp \
    ../../../../CRAP/source/unittests/source/config_endianess.cpp \
    ../../../../CRAP/source/unittests/source/config_compilers.cpp \
    ../../../../CRAP/libraries/unittest/XmlTestReporter.cpp \
    ../../../../CRAP/libraries/unittest/TimeConstraint.cpp \
    ../../../../CRAP/libraries/unittest/TestRunner.cpp \
    ../../../../CRAP/libraries/unittest/TestResults.cpp \
    ../../../../CRAP/libraries/unittest/TestReporterStdout.cpp \
    ../../../../CRAP/libraries/unittest/TestReporter.cpp \
    ../../../../CRAP/libraries/unittest/TestList.cpp \
    ../../../../CRAP/libraries/unittest/TestDetails.cpp \
    ../../../../CRAP/libraries/unittest/Test.cpp \
    ../../../../CRAP/libraries/unittest/ReportAssert.cpp \
    ../../../../CRAP/libraries/unittest/MemoryOutStream.cpp \
    ../../../../CRAP/libraries/unittest/DeferredTestResult.cpp \
    ../../../../CRAP/libraries/unittest/DeferredTestReporter.cpp \
    ../../../../CRAP/libraries/unittest/CurrentTest.cpp \
    ../../../../CRAP/libraries/unittest/Checks.cpp \
    ../../../../CRAP/libraries/unittest/AssertException.cpp \
    ../../../../CRAP/libraries/unittest/Posix/TimeHelpers.cpp \
    ../../../../CRAP/libraries/unittest/Posix/SignalTranslator.cpp



unix:!macx: LIBS += -L$$PWD/../../../../CRAP/binary/ -lCRAPlibrary

INCLUDEPATH += $$PWD/../../../../CRAP/binary
DEPENDPATH += $$PWD/../../../../CRAP/binary

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../CRAP/binary/libCRAPlibrary.a

unix:!macx: LIBS += -ldl
