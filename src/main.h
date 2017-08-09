//
// Created by Timothy A Haskins Jr on 5/23/17.
//

#ifndef LAZYFOO_MAIN_H
#define LAZYFOO_MAIN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdbool.h>
#include "LTexture.h"

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

const int WALKING_ANIMATION_FRAMES = 4;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;
LTexture gTexture = {NULL, NULL, 0, 0};

bool init();

bool loadMedia();

void closer();

SDL_Texture* loadTexture(const char* path);

#endif //LAZYFOO_MAIN_H
