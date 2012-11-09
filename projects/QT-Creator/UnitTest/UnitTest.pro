TEMPLATE = lib
CONFIG += staticlib
CONFIG -= qt

INCLUDEPATH += ../../../lib/unittest
LIBS += -lpthread

SOURCES += \
    ../../../lib/unittest/XmlTestReporter.cpp \
    ../../../lib/unittest/TimeConstraint.cpp \
    ../../../lib/unittest/TestRunner.cpp \
    ../../../lib/unittest/TestResults.cpp \
    ../../../lib/unittest/TestReporterStdout.cpp \
    ../../../lib/unittest/TestReporter.cpp \
    ../../../lib/unittest/TestList.cpp \
    ../../../lib/unittest/TestDetails.cpp \
    ../../../lib/unittest/Test.cpp \
    ../../../lib/unittest/ReportAssert.cpp \
    ../../../lib/unittest/MemoryOutStream.cpp \
    ../../../lib/unittest/DeferredTestResult.cpp \
    ../../../lib/unittest/DeferredTestReporter.cpp \
    ../../../lib/unittest/CurrentTest.cpp \
    ../../../lib/unittest/Checks.cpp \
    ../../../lib/unittest/AssertException.cpp \
    ../../../lib/unittest/Posix/TimeHelpers.cpp \
    ../../../lib/unittest/Posix/SignalTranslator.cpp

HEADERS += \
    ../../../lib/unittest/XmlTestReporter.h \
    ../../../lib/unittest/UnitTest++.h \
    ../../../lib/unittest/TimeHelpers.h \
    ../../../lib/unittest/TimeConstraint.h \
    ../../../lib/unittest/TestSuite.h \
    ../../../lib/unittest/TestRunner.h \
    ../../../lib/unittest/TestResults.h \
    ../../../lib/unittest/TestReporterStdout.h \
    ../../../lib/unittest/TestReporter.h \
    ../../../lib/unittest/TestMacros.h \
    ../../../lib/unittest/TestList.h \
    ../../../lib/unittest/TestDetails.h \
    ../../../lib/unittest/Test.h \
    ../../../lib/unittest/ReportAssert.h \
    ../../../lib/unittest/MemoryOutStream.h \
    ../../../lib/unittest/ExecuteTest.h \
    ../../../lib/unittest/DeferredTestResult.h \
    ../../../lib/unittest/DeferredTestReporter.h \
    ../../../lib/unittest/CurrentTest.h \
    ../../../lib/unittest/Config.h \
    ../../../lib/unittest/Checks.h \
    ../../../lib/unittest/CheckMacros.h \
    ../../../lib/unittest/AssertException.h \
    ../../../lib/unittest/Posix/TimeHelpers.h \
    ../../../lib/unittest/Posix/SignalTranslator.h

