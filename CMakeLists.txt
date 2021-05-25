cmake_minimum_required(VERSION 2.8)

project(game)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
set(CMAKE_CXX_STANDARD 11)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
include_directories("/usr/local/include/eigen3")
include_directories(
        ${PROJECT_SOURCE_DIR}/include
)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)

add_executable(ex ${DIR_SRCS} ${DIR_SRCS})

target_link_libraries(ex
        ${SDL2_LIBRARIES}
        ${SDL2_IMAGE_LIBRARIES}
)
