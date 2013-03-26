CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(CRAP_LIBRARY)

#########################################################################

################################################
# Add Option to enable Unit tests and examples #
################################################

OPTION(CRAP_BUILD_UNITTEST "Build unit tests" OFF)

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

SET(CRAPLIB_PATH ${CMAKE_SOURCE_DIR}/../libraries)

#####################################
#         Adding include dirs       #
#####################################

### OPENAL
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/openal/include)
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/openal/OpenAL32/Include)
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/openal/Alc)

IF(WIN32)
    INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/openal/build/Win32/)
ELSE(WIN32)
    INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/openal/build/Linux)
ENDIF(WIN32)

### GLFW
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glfw/include)

### GLEW
INCLUDE_DIRECTORIES(${CRAPLIB_PATH}/glew/include)


#################################################
#                 External sources              #
#################################################

#####################################
#       Adding openAL sources       #
#####################################

# FIXME: switch backends for different platforms
# FIXME: check which backends are available before compiling

SET(OPENAL_SOURCES
    "../libraries/openal/OpenAL32/alThunk.c"
    "../libraries/openal/OpenAL32/alState.c"
    "../libraries/openal/OpenAL32/alSource.c"
    "../libraries/openal/OpenAL32/alListener.c"
    "../libraries/openal/OpenAL32/alFilter.c"
    "../libraries/openal/OpenAL32/alExtension.c"
    "../libraries/openal/OpenAL32/alError.c"
    "../libraries/openal/OpenAL32/alEffect.c"
    "../libraries/openal/OpenAL32/alBuffer.c"
    "../libraries/openal/OpenAL32/alAuxEffectSlot.c"
    "../libraries/openal/Alc/panning.c"
    "../libraries/openal/Alc/mixer_sse.c"
    "../libraries/openal/Alc/mixer_c.c"
    "../libraries/openal/Alc/mixer.c"
    "../libraries/openal/Alc/hrtf.c"
    "../libraries/openal/Alc/helpers.c"
    "../libraries/openal/Alc/bs2b.c"
    "../libraries/openal/Alc/ALu.c"
    "../libraries/openal/Alc/alcThread.c"
    "../libraries/openal/Alc/alcRing.c"
    "../libraries/openal/Alc/alcReverb.c"
    "../libraries/openal/Alc/alcModulator.c"
    "../libraries/openal/Alc/alcFlanger.c"
    "../libraries/openal/Alc/alcEcho.c"
    "../libraries/openal/Alc/alcDedicated.c"
    "../libraries/openal/Alc/alcConfig.c"
    "../libraries/openal/Alc/alcChorus.c"
    "../libraries/openal/Alc/ALc.c"
    "../libraries/openal/Alc/backends/wave.c"
    "../libraries/openal/Alc/backends/oss.c"
    "../libraries/openal/Alc/backends/null.c"
    "../libraries/openal/Alc/backends/alsa.c"
    "../libraries/openal/Alc/backends/pulseaudio.c"
    "../libraries/openal/Alc/backends/loopback.c"
    "../libraries/openal/Alc/hrtf_tables.inc"
)

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
    ${OPENAL_SOURCES}
    ${GLFW_SOURCES}
    ${GLEW_SOURCES}
)

SET(HEADERS
    ${HEADERS}
    ${CRAPLIB_PATH}/glfw/lib/internal.h
    ${CRAPLIB_PATH}/openal/Alc/mixer_defs.h
)

#########################################################################

#####################################
#           Creating Lib            #
#####################################
ADD_LIBRARY(CRAPLIB, ${SOURCES} ${HEADERS})
