cmake_minimum_required(VERSION 3.20)
project(documentation)

message("Downloading and installing Doxygen...")
include(FetchContent)

FetchContent_Declare(
    doxygen
    GIT_REPOSITORY https://github.com/doxygen/doxygen.git
    GIT_TAG Release_1_9_2
    QUIET
)

FetchContent_GetProperties(doxygen)
if(NOT doxygen_POPULATED)
    FetchContent_Populate(doxygen)
    add_subdirectory(${doxygen_SOURCE_DIR} ${doxygen_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()
message("Doxygen installed")

message("Looking for Doxygen...")
find_package(Doxygen REQUIRED)
if(DOXYGEN_FOUND)
    message("Doxygen found")
   
    set(DOXYGEN_CONFIG_FILE ${CMAKE_CURRENT_SOURCE_DIR}/docs/Doxyfile.in)

    # configure_file(${DOXYGEN_CONFIG_FILE} ${CMAKE_SOURCE_DIR}/docs/Doxyfile.in @ONLY)

    add_custom_target(
        docs
        COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE}
        WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
        COMMENT "Generating API documentation with Doxygen"
        VERBATIM
    )

    # execute_process(
    #     COMMAND ${CMAKE_COMMAND} -E chdir ${CMAKE_CURRENT_SOURCE_DIR}/docs ${DOXYGEN_EXECUTABLE} ${DOXYGEN_CONFIG_FILE}
    #     WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/docs
    # )

    message("Doxygen documentation generated")
else()
    message("Doxygen need to be installed to generate the doxygen documentation")
endif()