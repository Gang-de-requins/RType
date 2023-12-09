cmake_minimum_required(VERSION 3.20)
project(r-type_client)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# add_subdirectory(ecs)

set(SRC
    src/Main.cpp
)

add_compile_options(-Wall -Wextra -Werror -std=c++17)

message("Compiling ${PROJECT_NAME}...")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PRIVATE ../ecs/include)
target_link_libraries(${PROJECT_NAME} PRIVATE _ecs)

find_package(raylib 4.5.0 REQUIRED)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

message("Compiling ${PROJECT_NAME} done successfully!")
