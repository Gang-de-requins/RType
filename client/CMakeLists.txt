cmake_minimum_required(VERSION 3.8)
project(r-type_client)

message("Configuring ${PROJECT_NAME}...")
message("Looking for raylib...")
find_package(raylib CONFIG REQUIRED)
message("Found raylib")
message("Looking for Boost...")
find_package(Boost COMPONENTS system REQUIRED)
message("Found Boost")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC_ECS
    ../ecs/src/World.cpp
    ../ecs/src/SceneManager.cpp
    ../ecs/src/ParserJson.cpp
    ../ecs/src/Buffer.cpp
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

set(SRC_CLIENT
    src/Main.cpp
    src/ErrorHandling.cpp
    src/Game.cpp
    src/Network.cpp
    src/Player.cpp
)

set(SRC
    ${SRC_ECS}
    ${SRC_CLIENT}
)

if (WIN32)
	add_compile_options(/W4 /WX /std:c++17)
else()
    add_compile_options(-Wall -Wextra -Werror -std=c++17)
endif()

message("Compiling ${PROJECT_NAME}...")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PUBLIC ../ecs/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::system)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

message("Compiling ${PROJECT_NAME} done successfully!")

if (WIN32)
    target_compile_definitions(${PROJECT_NAME} PRIVATE _WIN32_WINNT=0x0601)
endif()

if (WIN32)
    set(PLATFORM_NAME "windows")
elseif (APPLE)
    set(PLATFORM_NAME "macos")
elseif (UNIX)
    set(PLATFORM_NAME "linux")
endif()

install(TARGETS ${PROJECT_NAME} DESTINATION bin)

set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PLATFORM_NAME}")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PLATFORM_NAME}")

include(CPack)
