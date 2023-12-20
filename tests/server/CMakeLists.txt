cmake_minimum_required(VERSION 3.14)
project(tests_ecs)

add_subdirectory(${CMAKE_SOURCE_DIR}/../../ecs ${CMAKE_BINARY_DIR}/ecs)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
    ${PROJECT_NAME}
    # complete with real files like the following exemple
    # src/CustomExceptionsTest.cpp
)

target_link_libraries(
    ${PROJECT_NAME}
    GTest::gtest_main
    _ecs
)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME})

include_directories(
    ${CMAKE_SOURCE_DIR}/../../ecs/include
    ${CMAKE_SOURCE_DIR}/include
)

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy
    ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}
)
