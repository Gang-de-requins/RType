cmake_minimum_required(VERSION 3.20)
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
set(ECS_LIBRARY _ecs)

set(SRC
    src/Main.cpp
    src/ErrorHandling.cpp
    src/Game.cpp
    src/Network.cpp
    src/Player.cpp
)

# add_compile_options(-Wall -Wextra -Werror -std=c++17)

message("Compiling ${PROJECT_NAME}...")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE include)
target_include_directories(${PROJECT_NAME} PUBLIC ../ecs/include)

target_link_libraries(${PROJECT_NAME} PUBLIC ${ECS_LIBRARY})
target_link_libraries(${PROJECT_NAME} PRIVATE Boost::boost Boost::system)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

message("Compiling ${PROJECT_NAME} done successfully!")
