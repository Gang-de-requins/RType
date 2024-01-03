cmake_minimum_required(VERSION 3.20)
project(_ecs)

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
    src/systems/Movement.cpp
    src/systems/Controllable.cpp
    src/systems/Modifier.cpp
    src/systems/Music.cpp
    src/systems/Sound.cpp
    src/systems/Collision.cpp
    src/systems/Life.cpp
    src/systems/Parallax.cpp
    src/systems/Clickable.cpp
    src/systems/Spawner.cpp
    src/systems/Destruction.cpp
    src/systems/rendering/Name.cpp
    src/systems/rendering/Sprite.cpp
    src/systems/rendering/Text.cpp
    src/systems/rendering/Animation.cpp
    src/systems/rendering/Rectangle.cpp
    src/systems/rendering/TextInput.cpp
    src/systems/rendering/Render.cpp
)

add_library(${PROJECT_NAME} SHARED ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC raylib)

message("ECS Library built successfully!")
