#####################################
#   Adding source and include dir   #
#   Setting up source&header vars   #
#####################################
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/core)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/files)
ADD_SUBDIRECTORY(${CMAKE_CURRENT_SOURCE_DIR}/opengl)

SET(HEADERS
    ${HEADERS}
    PARENT_SCOPE
)

