//
// Created by Timothy Haskins on 8/11/17.
//

#ifndef LAZYFOO_GLOBALS_H
#define LAZYFOO_GLOBALS_H

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

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

typedef struct MColliders {
    SDL_Rect* boxes;
    size_t count;
} MColliders;

bool checkCollisionMC(MColliders* a, MColliders* b);

bool checkCollisionCC(Circle* a, Circle* b);

bool checkCollisionCR(Circle* a, SDL_Rect* b);

double distanceSquared(int x1, int y1, int x2, int y2);

#endif //LAZYFOO_GLOBALS_H
