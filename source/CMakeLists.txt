CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CRAP_LIBRARY)

SET(CRAPLIB_PATH ${CMAKE_SOURCE_DIR}/../libraries)

#########################################################################

### BUILD OPENAL

include(ExternalProject)

set(OpenAL_args
	-DALSOFT_EXAMPLES=OFF -DALSOFT_UTILS=OFF -DLIBTYPE=STATIC
)

if(WIN32)
set(OpenAL_args
	${OpenAL_args}
	)
elseif(LINUX)
set(OpenAL_args
	${OpenAL_args}
	-DAL_ALEXT_PROTOTYPES=1
	)
endif()

ExternalProject_Add(openal
  PREFIX ${CMAKE_BINARY_DIR}/openal
  SOURCE_DIR ${CRAPLIB_PATH}/openal
  CMAKE_ARGS ${OpenAL_args}
  BINARY_DIR ${CMAKE_BINARY_DIR}/openal
  INSTALL_COMMAND ""
)

#########################################################################

################################################
# Add Option to enable Unit tests and examples #
################################################

OPTION(CRAP_BUILD_UNITTEST "Build unit tests" OFF)
OPTION(CRAP_BUILD_EXAMPLES "Build unit tests" OFF)


IF(CRAP_BUILD_EXAMPLES)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/opengltest)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/performancetests)
	ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/SPG)
ENDIF(CRAP_BUILD_EXAMPLES)

IF(CRAP_BUILD_UNITTEST)
    ADD_SUBDIRECTORY(${CMAKE_SOURCE_DIR}/unittests)
ENDIF(CRAP_BUILD_UNITTEST)


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
IF(WIN32)
	ADD_DEFINITIONS(-DGLEW_STATIC)
	ADD_DEFINITIONS(-Dstrcasecmp=_stricmp)
	ADD_DEFINITIONS(-Dstrncasecmp=_strnicmp)
	ADD_DEFINITIONS(-Dsnprintf=_snprintf)
	ADD_DEFINITIONS(-Disfinite=_finite)
	ADD_DEFINITIONS(-Disnan=_isnan)
	ADD_DEFINITIONS(-D_WIN32_WINNT=0x0501)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
	ADD_DEFINITIONS(-D_CRT_NONSTDC_NO_DEPRECATE)
	ADD_DEFINITIONS(-D_DEBUG)
ENDIF(WIN32)

IF(LINUX)
	ADD_DEFINITIONS(-DAL_ALEXT_PROTOTYPES)
	ADD_DEFINITIONS(-D_GNU_SOURCE=1)
	ADD_DEFINITIONS(-DAL_LIBTYPE_STATIC)
	ADD_DEFINITIONS(-D_CRT_SECURE_NO_WARNINGS)
ENDIF(LINUX)

#########################################################################

####
#   EXTERNAL DEPENDENCIES
####

#####################################
#         Adding include dirs       #
#####################################

### AL
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/openal/include/)
LINK_DIRECTORIES(${CMAKE_BINARY_DIR}/openal/)

### GLFW
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glfw/lib/)
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glfw/include/)

IF(WIN32)
	INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glfw/lib/win32/)
ELSEIF(APPLE)
	INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glfw/lib/cocoa/)
ELSE(WIN32)
	INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glfw/lib/x11/)
ENDIF(WIN32)

### GLEW
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glew/include/)

#################################################
#                 External sources              #
#################################################

#####################################
#        Adding GLFW sources        #
#####################################

SET(GLFW_SOURCES
    "../libraries/glfw/lib/window.c"
    "../libraries/glfw/lib/time.c"
    "../libraries/glfw/lib/thread.c"
    "../libraries/glfw/lib/tga.c"
    "../libraries/glfw/lib/stream.c"
    "../libraries/glfw/lib/joystick.c"
    "../libraries/glfw/lib/input.c"
    "../libraries/glfw/lib/init.c"
    "../libraries/glfw/lib/image.c"
    "../libraries/glfw/lib/glext.c"
    "../libraries/glfw/lib/fullscreen.c"
    "../libraries/glfw/lib/enable.c"
)
IF(WIN32)
    SET(GLFW_SOURCES
        ${GLFW_SOURCES}
        "../libraries/glfw/lib/win32/win32_window.c"
        "../libraries/glfw/lib/win32/win32_time.c"
        "../libraries/glfw/lib/win32/win32_thread.c"
        "../libraries/glfw/lib/win32/win32_joystick.c"
        "../libraries/glfw/lib/win32/win32_init.c"
        "../libraries/glfw/lib/win32/win32_glext.c"
        "../libraries/glfw/lib/win32/win32_fullscreen.c"
        "../libraries/glfw/lib/win32/win32_enable.c"
        "../libraries/glfw/lib/win32/win32_dllmain.c"
    )
ELSEIF(APPLE)
    SET(GLFW_SOURCES
        ${GLFW_SOURCES}
        "../libraries/glfw/lib/cocoa/cocoa_window.c"
        "../libraries/glfw/lib/cocoa/cocoa_time.c"
        "../libraries/glfw/lib/cocoa/cocoa_thread.c"
        "../libraries/glfw/lib/cocoa/cocoa_joystick.c"
        "../libraries/glfw/lib/cocoa/cocoa_init.c"
        "../libraries/glfw/lib/cocoa/cocoa_glext.c"
        "../libraries/glfw/lib/cocoa/cocoa_fullscreen.c"
        "../libraries/glfw/lib/cocoa/cocoa_enable.c"
    )
ELSE(WIN32) #X11 (linux, unix, ...)
    SET(GLFW_SOURCES
        ${GLFW_SOURCES}
        "../libraries/glfw/lib/x11/x11_window.c"
        "../libraries/glfw/lib/x11/x11_time.c"
        "../libraries/glfw/lib/x11/x11_thread.c"
        "../libraries/glfw/lib/x11/x11_keysym2unicode.c"
        "../libraries/glfw/lib/x11/x11_joystick.c"
        "../libraries/glfw/lib/x11/x11_init.c"
        "../libraries/glfw/lib/x11/x11_glext.c"
        "../libraries/glfw/lib/x11/x11_fullscreen.c"
        "../libraries/glfw/lib/x11/x11_enable.c"
    )
ENDIF(WIN32)

#####################################
#        Adding GLEW sources        #
#####################################
SET(GLEW_SOURCES
    "../libraries/glew/src/glew.c"
)

########################################################################

#####################################
#       Other dependencies          #
#####################################

FIND_PACKAGE(OpenGL)

IF(NOT WIN32)
IF(NOT APPLE)
    FIND_PACKAGE(X11)
    FIND_PACKAGE(Threads)
ENDIF(NOT APPLE)
ENDIF(NOT WIN32)

#########################################################################

#####################################
#       Building source tree        #
#   Setting up source&header vars   #
#####################################

### CRAPLIB
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/craplib/include)

ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/craplib)
SET(SOURCES
    ${SOURCES}
    ${GLFW_SOURCES}
    ${GLEW_SOURCES}
)

SET(HEADERS
    ${HEADERS}
)

#####################################
#           Creating Lib            #
#####################################
ADD_LIBRARY(crap ${SOURCES} ${HEADERS})
TARGET_LINK_LIBRARIES(crap OpenAL32)

IF(MSVC)
### SET VISUAL STUDIO FILTERS
SOURCE_GROUP("source" FILES ${SOURCES})
SOURCE_GROUP("source\\audio" REGULAR_EXPRESSION ".*/source/audio/.*[;]*" FILES ${SOURCES})
SOURCE_GROUP("source\\container" REGULAR_EXPRESSION ".*/source/container/.*" FILES ${SOURCES})
SOURCE_GROUP("source\\control" REGULAR_EXPRESSION ".*/source/control/.*" FILES ${SOURCES})
SOURCE_GROUP("source\\files" REGULAR_EXPRESSION ".*/source/files/.*" FILES ${SOURCES})
SOURCE_GROUP("source\\network" REGULAR_EXPRESSION ".*/source/network/.*" FILES ${SOURCES})
SOURCE_GROUP("source\\opengl" REGULAR_EXPRESSION ".*/source/opengl/.*" FILES ${SOURCES})
SOURCE_GROUP("source\\threading" REGULAR_EXPRESSION ".*/source/threading/.*" FILES ${SOURCES})

SOURCE_GROUP("include" FILES ${HEADERS})
SOURCE_GROUP("include\\audio" REGULAR_EXPRESSION ".*/audio/.*" FILES ${HEADERS})
SOURCE_GROUP("include\\container" REGULAR_EXPRESSION ".*/container/.*" FILES ${HEADERS})
SOURCE_GROUP("include\\control" REGULAR_EXPRESSION ".*/control/.*" FILES ${HEADERS})
SOURCE_GROUP("include\\files" REGULAR_EXPRESSION ".*/files/.*" FILES ${HEADERS})
SOURCE_GROUP("include\\network" REGULAR_EXPRESSION ".*/network/.*" FILES ${HEADERS})
SOURCE_GROUP("include\\opengl" REGULAR_EXPRESSION ".*/opengl/.*" FILES ${HEADERS})
SOURCE_GROUP("include\\threading" REGULAR_EXPRESSION ".*/threading/.*" FILES ${HEADERS})
ENDIF(MSVC)