cmake_minimum_required(VERSION 3.20)
project(ecs VERSION 0.1.0)

set(RAYLIB_VERSION 4.5.0)
message("Looking for raylib ${RAYLIB_VERSION}")

find_package(raylib ${RAYLIB_VERSION} REQUIRED)
if (NOT raylib_FOUND)
    message(FATAL_ERROR "raylib ${RAYLIB_VERSION} not found, installing it...")
    include(FetchContent)
    FetchContent_Declare(
        raylib
        GIT_REPOSITORY https://github.com/raysan5/raylib.git
        GIT_TAG master
    )
    FetchContent_GetProperties(raylib)
    message("raylib ${RAYLIB_VERSION} installed!")
endif()

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    src/World.cpp
    src/Archetype.cpp
    src/systems/Movement.cpp
    src/systems/rendering/Sprite.cpp
    src/systems/rendering/Text.cpp
)

message("Building ECS Library...")
add_library(_ecs SHARED ${SRC})

target_include_directories(_ecs PRIVATE include)

target_link_libraries(_ecs PRIVATE -lraylib -lGL -lm -lpthread -ldl -lrt -lX11)
message("ECS Library built successfully!")
