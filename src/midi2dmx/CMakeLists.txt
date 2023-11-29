cmake_minimum_required(VERSION 3.14)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
enable_testing()

###########################################################
# Setup the project
###########################################################
set(VERSION_MAJOR   1   CACHE STRING "Project major version number.")
set(VERSION_MINOR   0   CACHE STRING "Project minor version number.")
set(VERSION_PATCH   0   CACHE STRING "Project patch version number.")
mark_as_advanced(VERSION_MAJOR VERSION_MINOR VERSION_PATCH)

project(midi2dmx VERSION ${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH} DESCRIPTION "midi2dmx library")

###########################################################
# Setup Google's gtest/gmock environment
###########################################################
include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

###########################################################
# Setup Doxygen documentation
###########################################################
find_package(Doxygen)
option(BUILD_DOC "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if (BUILD_DOC)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen need to be installed to generate the doxygen documentation.")
    endif()

    set(DOXYGEN_IN ${CMAKE_CURRENT_SOURCE_DIR}/doc/doxygen.in)
    set(DOXYGEN_OUT ${CMAKE_CURRENT_BINARY_DIR}/doxyfile)

    configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT} @ONLY)

    add_custom_target(doc_doxygen ALL
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_OUT}
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM)

    # install(DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/html DESTINATION share/doc)
endif (BUILD_DOC)

###########################################################
# Add the static library target midi2dmx
###########################################################
add_library(midi2dmx STATIC src/midi2dmx/ContinuousController.cpp)

set_target_properties(midi2dmx PROPERTIES
    VERSION ${PROJECT_VERSION}
    SOVERSION ${PROJECT_VERSION_MAJOR})

target_include_directories(midi2dmx PRIVATE src/midi2dmx
                                    INTERFACE src)

# install(TARGETS midi2dmx
#     LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
#     PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

###########################################################
# Add binary target for the unit test executble
###########################################################
add_executable(unittests tests/unittests.cpp tests/midi2dmx/ContinuousControllerTests.cpp)
target_link_libraries(unittests gtest gmock)
target_link_libraries(unittests midi2dmx)
add_test(NAME midi2dmx_unittest COMMAND unittests)
