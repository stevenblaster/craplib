CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CRAP_PROJECT)
#########################################################################


################################################
# Add Option to enable Unit tests and examples #
################################################

OPTION(CRAP_BUILD_UNITTEST "Build unit tests" ON)

IF(CRAP_BUILD_UNITTEST)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/unittests)
ENDIF(CRAP_BUILD_UNITTEST)

OPTION(CRAP_BUILD_OPENGLTEST "Build unit tests" OFF)

IF(CRAP_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/opengltest)
    ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/performancetests)
ENDIF(CRAP_BUILD_EXAMPLES)

#########################################################################


# Library version information
SET(CRAPBASE_MAJOR_VERSION 0)
SET(CRAPBASE_MAJOR_VERSION 0)
SET(CRAPBASE_PATCH_VERSION 1)
SET(CRAPLIB_VERSION
    ${CRAPBASE_MAJOR_VERSION}.${CRAPBASE_MINOR_VERSION}.${CRAPBASE_PATCH_VERSION}
)

# Build static libraries by default
OPTION(BUILD_SHARED_LIBS "Build CRAPLIB with shared libraries." OFF)

#########################################################################

###################################
#   SET PREPROCESSOR DEFINES      #
#   USAGE: #define EXMAPLE=0      #
#   ADD_DEFINITION(-DEXAMPLE=0)   #
###################################
ADD_DEFINITIONS(-DAL_ALEXT_PROTOTYPES)
ADD_DEFINITIONS(-D_GNU_SOURCE=1)
ADD_DEFINITIONS(-DAL_LIBTYPE_STATIC)
ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)

#########################################################################

####
#   EXTERNAL DEPENDENCIES
#   FIXME: CHECK DIFFERENT PLATFORM DEPENDENCIES
###

SET(CRAP_LIB_PATH ${CMAKE_CURRENT_DIRECTORY}/../libraries)

#####################################
#         Adding include dirs       #
#####################################

### OPENAL
SET(CRAP_OPENAL_INCLUDE_PATH
    ${CRAP_LIB_PATH}/openal/include/
    ${CRAP_LIB_PATH}/openal/OpenAL32/Include/
    ${CRAP_LIB_PATH}/openal/Alc/
)

IF(WIN32)
    SET(CRAP_OPENAL_INCLUDE_PATH
        ${CRAP_OPENAL_INCLUDE_PATH}
        ${CRAP_LIB_PATH}/openal/build/Win32/
    )
ELSE(WIN32)
    SET(
        CRAP_OPENAL_INCLUDE_PATH
        ${CRAP_OPENAL_INCLUDE_PATH}
        ${CRAP_LIB_PATH}/openal/build/Linux/
    )
ENDIF(WIN32)

INCLUDE_DIRECTORIES(${CRAP_INCLUDE_DIRS} ${CRAP_OPENAL_INCLUDE_PATH})

### GLFW
INCLUDE_DIRECTORIES(${CRAP_LIB_PATH}/glfw/include/)

### GLEW
INCLUDE_DIRECTORIES(${CRAP_LIB_PATH}/glew/include/)


# Attention:
# Adding new source file to any lib in the libraries dir
# needs a new Configure and Generate step from CMake
# FIXME: add files manually

#####################################
#       Adding openAL sources       #
#####################################
file(GLOB_RECURSE OPENAL_SOURCES_ALC "../libraries/openal/Alc/*.c")
file(GLOB_RECURSE OPENAL_SOURCES_OpenAL "../libraries/openal/OpenAL32*.c")
SET(OPENAL_SOURCES
    ${OPENAL_SOURCES_AL}
    ${OpenAL_SOURCES_OpenAL}
    )

#####################################
#        Adding GLFW sources        #
#####################################
IF(WIN32)
    file(GLOB_RECURSE GLFW_SOURCES "../libraries/glfw/lib/win32/*.c")
ELSEIF(APPLE)
    file(GLOB_RECURSE GLFW_SOURCES "../libraries/glfw/lib/cocoa/*.c")
ELSE(WIN32) #Unix, linux, ...
    file(GLOB_RECURSE GLFW_SOURCES "../libraries/glfw/lib/x11/*.c")
ENDIF(WIN32)

#####################################
#        Adding GLEW sources        #
#####################################
file(GLOB_RECURSE GLEW_SOURCES "../libraries/glew/src/*.c")

########################################################################

#####################################
#       Other dependencies          #
#####################################
FIND_PACKAGE(OpenGL)
IF(NOT WIN32)
IF(NOT APPLE)
    FIND_PACKAGE(X11)
ENDIF(NOT APPLE)
ENDIF(NOT WIN32)

#########################################################################

#####################################
#       Building source tree        #
#   Setting up source&header vars   #
#####################################
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/craplib)
SET(SOURCES
    ${SOURCES}
    ${OPENAL_SOURCES}
    ${GLFW_SOURCES}
    ${GLEW_SOURCES}
)

SET(HEADERS
    ${HEADERS}
    ../libraries/glfw/lib/internal.h
    ../libraries/openal/Alc/mixer_defs.h
)

#########################################################################

#####################################
#           Creating Lib            #
#####################################
ADD_LIBRARY(CRAPLIB, ${SOURCES} ${HEADERS})
