cmake_minimum_required(VERSION 3.8)
set(CMAKE_TOOLCHAIN_FILE ${CMAKE_SOURCE_DIR}/vcpkg/scripts/buildsystems/vcpkg.cmake)
project(r-type)

add_subdirectory(ecs)
add_subdirectory(server)
add_subdirectory(client)
#add_subdirectory(docs)
# add_subdirectory(docs)
