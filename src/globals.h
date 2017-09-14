//
// Created by Timothy Haskins on 8/11/17.
//

#ifndef LAZYFOO_GLOBALS_H
#define LAZYFOO_GLOBALS_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

#define LEVEL_WIDTH 1280
#define LEVEL_HEIGHT 960

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

typedef struct Circle {
    int x;
    int y;
    int r;
} Circle;

#endif //LAZYFOO_GLOBALS_H
