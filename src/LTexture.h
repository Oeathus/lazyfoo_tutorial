//
// Created by Timothy Haskins on 8/8/17.
//
#ifndef LAZYFOO_LTEXTURE_H
#define LAZYFOO_LTEXTURE_H

#include "globals.h"

typedef struct LTexture {
    SDL_Texture* mTexture;
    int mWidth;
    int mHeight;
} LTexture;

bool LTexture_loadFromFile(LTexture* texture, SDL_Renderer* renderer, const char* path);

bool LTexture_loadFromRenderedText(LTexture* texture, SDL_Renderer* renderer, TTF_Font* font, char* textureText,
                                   SDL_Color textColor);

void LTexture_setColor(LTexture* texture, Uint8 red, Uint8 green, Uint8 blue);

void LTexture_setBlendMode(LTexture* texture, SDL_BlendMode blending);

void LTexture_setAlpha(LTexture* texture, Uint8 alpha);

void LTexture_render(LTexture* texture, SDL_Renderer* renderer, int x, int y, SDL_Rect* clip, double angle,
                     SDL_Point* center, SDL_RendererFlip flip);

void LTexture_free(LTexture* texture);

#endif //LAZYFOO_LTEXTURE_H
