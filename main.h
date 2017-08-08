//
// Created by Timothy A Haskins Jr on 5/23/17.
//

#ifndef LAZYFOO_MAIN_H
#define LAZYFOO_MAIN_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <unistring/stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

struct LTexture {
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
};
typedef struct LTexture LTexture;

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
LTexture gTexture = {NULL, 0, 0};
LTexture gTextureBackground = {NULL, 0, 0};

bool init();

bool loadMedia();

void closer();

SDL_Texture* loadTexture(const char* path);

bool loadLTextureFromFile(LTexture* texture, const char* path);

void renderLTexture(LTexture* texture, int x, int y);

void destroyLTexture(LTexture* texture);

#endif //LAZYFOO_MAIN_H
