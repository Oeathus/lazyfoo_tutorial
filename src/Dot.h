//
// Created by Timothy Haskins on 8/11/17.
//

#ifndef LAZYFOO_DOT_H
#define LAZYFOO_DOT_H

#include "globals.h"
#include "LTexture.h"

static const int DOT_WIDTH = 20;
static const int DOT_HEIGHT = 20;
static const int DOT_VEL = 10;

typedef struct Dot {
    int mPosX;
    int mPosY;
    int mVelX;
    int mVelY;
    SDL_Rect mCollider;
} Dot;

extern void Dot_init(Dot* dot);

extern void Dot_handleEvent(Dot* dot, SDL_Event* e);

extern void Dot_move(Dot* dot, SDL_Rect* wall);

extern void Dot_render(Dot* dot, LTexture* texture, SDL_Renderer* renderer, SDL_Rect* clip, double angle,
                       SDL_Point* center, SDL_RendererFlip flip);

#endif //LAZYFOO_DOT_H
