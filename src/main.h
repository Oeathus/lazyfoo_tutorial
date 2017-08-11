//
// Created by Timothy A Haskins Jr on 5/23/17.
//

#ifndef LAZYFOO_MAIN_H
#define LAZYFOO_MAIN_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL_mixer.h>

#include "LTexture.h"
#include "LButton.h"
#include "LTimer.h"

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480
#define SCREEN_FPS 60
#define SCREEN_TICKS_PER_FRAME (1000 / SCREEN_FPS)

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;

TTF_Font* gFont = NULL;
LTexture gPromptTextTexture = {NULL, 0, 0};
LTexture gTimeTextTexture = {NULL, 0, 0};

Mix_Music* gMusic = NULL;

Mix_Chunk* gScratch = NULL;
Mix_Chunk* gHigh = NULL;
Mix_Chunk* gMedium = NULL;
Mix_Chunk* gLow = NULL;

bool init();

bool loadMedia();

void closer();

SDL_Texture* loadTexture(const char* path);

#endif //LAZYFOO_MAIN_H
