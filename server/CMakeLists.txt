cmake_minimum_required(VERSION 3.20)
project(r-type_server)

message("Configuring ${PROJECT_NAME}...")
message("Looking for boost...")
find_package(Boost REQUIRED COMPONENTS system)
message("Boost found!")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    src/Main.cpp
)

add_compile_options(-Wall -Wextra -Werror -std=c++17)

message("Compiling ${PROJECT_NAME}...")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PRIVATE include)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)

message("Compiling ${PROJECT_NAME} done successfully!")
