#####################################
#   Adding source and include dir   #
#   Setting up source&header vars   #
#####################################
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/include)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/source)

SET(SOURCES
    ${SOURCES}
    PARENT_SCOPE
)

SET(HEADERS
    ${HEADERS}
    PARENT_SCOPE
)

