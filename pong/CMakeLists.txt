cmake_minimum_required(VERSION 3.8)
project(pong)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(ECS_LIBRARY ecs)
add_subdirectory(../ecs build/ecs)

set(SRC_PONG
    src/main.cpp
    src/Pong.cpp
    src/LoadMenu.cpp
    src/LoadGame.cpp
    src/LoadEnd.cpp
    src/LoadSettings.cpp
)

set(SRC
    ${SRC_PONG}
)

message("Compiling ${PROJECT_NAME}...")

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR})

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../ecs/include)

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${ECS_LIBRARY})


