cmake_minimum_required(VERSION 3.20)
project(r-type_server)

message("Configuring ${PROJECT_NAME}...")
message("Looking for raylib...")
find_package(raylib CONFIG REQUIRED)
message("Found raylib")
message("Looking for boost...")
find_package(Boost REQUIRED COMPONENTS system)
message("Boost found!")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_ECS
    ../ecs/src/World.cpp
    ../ecs/src/SceneManager.cpp
    ../ecs/src/ParserJson.cpp
    ../ecs/src/systems/Movement.cpp
    ../ecs/src/systems/Controllable.cpp
    ../ecs/src/systems/Music.cpp
    ../ecs/src/systems/Sound.cpp
    ../ecs/src/systems/Collision.cpp
    ../ecs/src/systems/Life.cpp
    ../ecs/src/systems/Parallax.cpp
    ../ecs/src/systems/Clickable.cpp
    ../ecs/src/systems/Modifier.cpp
    ../ecs/src/systems/Spawner.cpp
    ../ecs/src/systems/Destruction.cpp
    ../ecs/src/systems/rendering/Name.cpp
    ../ecs/src/systems/rendering/Sprite.cpp
    ../ecs/src/systems/rendering/Text.cpp
    ../ecs/src/systems/rendering/Animation.cpp
    ../ecs/src/systems/rendering/Rectangle.cpp
    ../ecs/src/systems/rendering/TextInput.cpp
    ../ecs/src/systems/rendering/Render.cpp
)

set(SRC_SERVER
    src/Main.cpp
    src/Player.cpp
    src/Rtype.cpp
    src/Entity.cpp
    src/Server.cpp
    src/Message.cpp
)

set(SRC
    ${SRC_ECS}
    ${SRC_SERVER}
)

# add_compile_options(-Wall -Wextra -std=c++17)

message("Compiling ${PROJECT_NAME}...")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../ecs/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

message("Compiling ${PROJECT_NAME} done successfully!")
