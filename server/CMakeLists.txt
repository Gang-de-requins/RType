cmake_minimum_required(VERSION 3.8)
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
set(ECS_LIBRARY ecs)

set(SRC_SERVER
    src/Main.cpp
    src/Player.cpp
    src/Rtype.cpp
    src/Entity.cpp
    src/Server.cpp
    src/Message.cpp
)

set(SRC
    ${SRC_SERVER}
)

if (WIN32)
	add_compile_options(/W4 /WX /std:c++17)
else()
	add_compile_options(-Wall -Wextra -Werror -std=c++17)
endif()

message("Compiling ${PROJECT_NAME}...")

add_executable(${PROJECT_NAME} ${SRC})

target_include_directories(${PROJECT_NAME} PUBLIC include)
target_include_directories(${PROJECT_NAME} PUBLIC ../ecs/include)

target_link_libraries(${PROJECT_NAME} PRIVATE Boost::system)
target_link_libraries(${PROJECT_NAME} PRIVATE raylib)
target_link_libraries(${PROJECT_NAME} PRIVATE ${ECS_LIBRARY})

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
if (WIN32)
    install(FILES ${CMAKE_BINARY_DIR}/server/Debug/raylib.dll DESTINATION bin)
endif()

set(CPACK_GENERATOR "ZIP")
set(CPACK_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PLATFORM_NAME}")
set(CPACK_SOURCE_GENERATOR "ZIP")
set(CPACK_SOURCE_PACKAGE_FILE_NAME "${PROJECT_NAME}-${PLATFORM_NAME}")

include(CPack)
