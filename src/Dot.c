//
// Created by Timothy Haskins on 8/11/17.
//
#include "Dot.h"

void Dot_init(Dot* dot) {
    dot->mPosY = 0;
    dot->mPosX = 0;
    dot->mVelY = 0;
    dot->mVelX = 0;
    dot->mCollider.w = DOT_WIDTH;
    dot->mCollider.h = DOT_HEIGHT;
}

void Dot_handleEvent(Dot* dot, SDL_Event* e) {
    if (e->type == SDL_KEYDOWN && e->key.repeat == 0) {
        switch (e->key.keysym.sym) {
            case SDLK_UP:
                dot->mVelY -= DOT_VEL;
                break;
            case SDLK_DOWN:
                dot->mVelY += DOT_VEL;
                break;
            case SDLK_LEFT:
                dot->mVelX -= DOT_VEL;
                break;
            case SDLK_RIGHT:
                dot->mVelX += DOT_VEL;
                break;
            default:
                break;
        }
    } else if (e->type == SDL_KEYUP && e->key.repeat == 0) {
        //Adjust the velocity
        switch (e->key.keysym.sym) {
            case SDLK_UP:
                dot->mVelY += DOT_VEL;
                break;
            case SDLK_DOWN:
                dot->mVelY -= DOT_VEL;
                break;
            case SDLK_LEFT:
                dot->mVelX += DOT_VEL;
                break;
            case SDLK_RIGHT:
                dot->mVelX -= DOT_VEL;
                break;
            default:
                break;
        }
    }
}

void Dot_move(Dot* dot, SDL_Rect* wall) {
    dot->mPosX += dot->mVelX;
    dot->mCollider.x = dot->mPosX;

    if (dot->mPosX < 0 || (dot->mPosX + DOT_WIDTH > SCREEN_WIDTH)
        || (wall != NULL && checkCollision(dot->mCollider, *wall))) {
        dot->mPosX -= dot->mVelX;
    }

    dot->mPosY += dot->mVelY;
    dot->mCollider.y = dot->mPosY;

    if (dot->mPosY < 0 || (dot->mPosY + DOT_HEIGHT > SCREEN_HEIGHT)
        || (wall != NULL && checkCollision(dot->mCollider, *wall))) {
        dot->mPosY -= dot->mVelY;
    }
}

void Dot_render(Dot* dot, LTexture* texture, SDL_Renderer* renderer, SDL_Rect* clip, double angle,
                SDL_Point* center, SDL_RendererFlip flip) {
    LTexture_render(texture, renderer, dot->mPosX, dot->mPosY, clip, angle, center, flip);
}