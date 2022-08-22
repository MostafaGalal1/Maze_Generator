cmake_minimum_required(VERSION 3.22)
project(Maze_Generator)

set(CMAKE_CXX_STANDARD 14)

MATH(EXPR stack_size "16 * 1024 * 1024") # 16 Mb
set(CMAKE_EXE_LINKER_FLAGS "-Wl,--stack,${stack_size}")

set(SDL2_INCLUDE_DIR C:/libs/SDL/include)
set(SDL2_LIB_DIR C:/libs/SDL/lib/x64)
set(SDL2_IMAGE_INCLUDE_DIR C:/libs/SDL_image/include)
set(SDL2_IMAGE_LIB_DIR C:/libs/SDL_image/lib)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})
include_directories(${SDL2_IMAGE_INCLUDE_DIR})
link_directories(${SDL2_IMAGE_LIB_DIR})

add_executable(Maze_Generator main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2 SDL2_image)
