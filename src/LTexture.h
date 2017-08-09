//
// Created by Timothy Haskins on 8/8/17.
//
#ifndef LAZYFOO_LTEXTURE_H
#define LAZYFOO_LTEXTURE_H

#include <stdio.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdbool.h>

typedef struct {
    SDL_Texture* mTexture;
    SDL_Renderer* gRenderer;
    int mWidth;
    int mHeight;
} LTexture;

bool LTexture_loadFromFile(LTexture* texture, const char* path);

void LTexture_setColor(LTexture* texture, Uint8 red, Uint8 green, Uint8 blue);

void LTexture_setBlendMode(LTexture* texture, SDL_BlendMode blending);

void LTexture_setAlpha(LTexture* texture, Uint8 alpha);

void LTexture_render(LTexture* texture, int x, int y, SDL_Rect* clip,
                     double angle, SDL_Point* center, SDL_RendererFlip flip);

void LTexture_free(LTexture* texture);

#endif //LAZYFOO_LTEXTURE_H
