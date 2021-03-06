cmake_minimum_required(VERSION 3.8)
project(LazyFoo)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES
        src/globals.h
        src/LTexture.h
        src/LTexture.c
        src/LButton.h
        src/LButton.c
        src/LTimer.c
        src/Dot.h
        src/Dot.c
        src/main.h
        src/main.c)

add_executable(LazyFoo ${SOURCE_FILES})

set(CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)
find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED >=2.0.0)
find_package(SDL2_ttf REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIR}
        ${SDL2_IMAGE_INCLUDE_DIR}
        ${SDL2_TTF_INCLUDE_DIR}
        ${SDL2_MIXER_INCLUDE_DIR})

target_link_libraries(LazyFoo
        ${SDL2_LIBRARY}
        ${SDL2_IMAGE_LIBRARIES}
        ${SDL2_TTF_LIBRARIES}
        ${SDL2_MIXER_LIBRARIES})