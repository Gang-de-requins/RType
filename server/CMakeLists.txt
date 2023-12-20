cmake_minimum_required(VERSION 3.20)
project(r-type_server)

message("Configuring ${PROJECT_NAME}...")
message("Looking for boost...")
find_package(Boost REQUIRED COMPONENTS system)
message("Boost found!")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ECS_LIBRARY _ecs)

set(SRC
    src/Main.cpp
    src/Player.cpp
    src/Rtype.cpp
    src/Entity.cpp
    src/Server.cpp
    src/Message.cpp
)

add_compile_options(-Wall -Wextra -std=c++17)

message("Compiling ${PROJECT_NAME}...")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../ecs/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
target_link_libraries(${PROJECT_NAME} PUBLIC ${ECS_LIBRARY})

message("Compiling ${PROJECT_NAME} done successfully!")
