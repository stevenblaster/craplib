###
# UNIT TEST LIB FILES
###

INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/unittest/)
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/craplib/include)

SET( UNITTEST_SOURCEFILES
    ${CRAPLIB_PATH}/unittest/XmlTestReporter.cpp
    ${CRAPLIB_PATH}/unittest/TimeConstraint.cpp
    ${CRAPLIB_PATH}/unittest/TestRunner.cpp 
    ${CRAPLIB_PATH}/unittest/TestResults.cpp
    ${CRAPLIB_PATH}/unittest/TestReporterStdout.cpp
    ${CRAPLIB_PATH}/unittest/TestReporter.cpp
    ${CRAPLIB_PATH}/unittest/TestList.cpp
    ${CRAPLIB_PATH}/unittest/TestDetails.cpp
    ${CRAPLIB_PATH}/unittest/Test.cpp
    ${CRAPLIB_PATH}/unittest/ReportAssert.cpp
    ${CRAPLIB_PATH}/unittest/MemoryOutStream.cpp
    ${CRAPLIB_PATH}/unittest/DeferredTestResult.cpp
    ${CRAPLIB_PATH}/unittest/DeferredTestReporter.cpp
    ${CRAPLIB_PATH}/unittest/CurrentTest.cpp
    ${CRAPLIB_PATH}/unittest/Checks.cpp
    ${CRAPLIB_PATH}/unittest/AssertException.cpp
    ${CRAPLIB_PATH}/unittest/Posix/TimeHelpers.cpp
    ${CRAPLIB_PATH}/unittest/Posix/SignalTranslator.cpp
)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/source)

SET(SOURCES
    ${SOURCES}
    ${UNITTEST_SOURCEFILES}
)

ADD_EXECUTABLE(lib_unittest ${SOURCES})
TARGET_LINK_LIBRARIES(lib_unittest crap)
