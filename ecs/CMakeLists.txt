cmake_minimum_required(VERSION 3.8)
project(ecs)

message("Building ECS Library...")
message("Looking for raylib...")
find_package(raylib CONFIG REQUIRED)
message("Found raylib!")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    src/World.cpp
    src/SceneManager.cpp
    src/ParserJson.cpp
    src/Buffer.cpp
    src/systems/Movement.cpp
    src/systems/Controllable.cpp
    src/systems/Modifier.cpp
    src/systems/Music.cpp
    src/systems/Sound.cpp
    src/systems/Collision.cpp
    src/systems/Life.cpp
    src/systems/Parallax.cpp
    src/systems/Clickable.cpp
    src/systems/Destruction.cpp
    src/systems/KeyboardInput.cpp
    src/systems/Submit.cpp
    src/systems/rendering/Name.cpp
    src/systems/rendering/Sprite.cpp
    src/systems/rendering/Text.cpp
    src/systems/rendering/Animation.cpp
    src/systems/rendering/Rectangle.cpp
    src/systems/rendering/TextInput.cpp
    src/systems/rendering/Render.cpp
)

add_library(${PROJECT_NAME} STATIC ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

message("ECS Library built successfully!")

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32_WINNT=0x0601)
endif()
