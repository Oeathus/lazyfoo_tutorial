cmake_minimum_required(VERSION 3.8)
project(LazyFoo)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/main.c
        src/LTexture.c)

add_executable(LazyFoo ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED >=2.0.0)

include_directories(${SDL2_INCLUDE_DIR})
target_link_libraries(LazyFoo ${SDL2_LIBRARY} ${SDL2_IMAGE_LIBRARY})