//
// Created by Timothy Haskins on 8/11/17.
//
#include "Dot.h"

void Dot_init(Dot* dot, int x, int y) {
    dot->mPosX = x;
    dot->mVelX = 0;
    dot->mPosY = y;
    dot->mVelY = 0;
    dot->mCollider.r = DOT_WIDTH / 2;
    //Initialize colliders relative to position
    shiftColliders(dot);
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

void Dot_move(Dot* dot, SDL_Rect* square, Circle* circle) {
    //Move the dot left or right
    dot->mPosX += dot->mVelX;
    shiftColliders(dot);

    //If the dot collided or went too far to the left or right
    if ((dot->mPosX - dot->mCollider.r < 0)
        || (dot->mPosX + dot->mCollider.r > LEVEL_WIDTH)) {
        //Move back
        dot->mPosX -= dot->mVelX;
        shiftColliders(dot);
    }

    //Move the dot up or down
    dot->mPosY += dot->mVelY;
    shiftColliders(dot);

    //If the dot collided or went too far up or down
    if ((dot->mPosY - dot->mCollider.r < 0)
        || (dot->mPosY + dot->mCollider.r > LEVEL_HEIGHT)) {
        //Move back
        dot->mPosY -= dot->mVelY;
        shiftColliders(dot);
    }
}

void Dot_render(Dot* dot, LTexture* texture, SDL_Renderer* renderer, SDL_Rect* clip, double angle, SDL_Point* center,
                SDL_RendererFlip flip, SDL_Point* cam) {
    int x = (dot->mPosX - dot->mCollider.r);
    int y = (dot->mPosY - dot->mCollider.r);

    if (cam != NULL) {
        x -= cam->x;
        y -= cam->y;
    }

    LTexture_render(texture, renderer,
                    x, y,
                    clip, angle, center, flip);
}

void Dot_free(Dot* dot) {
    dot->mPosY = 0;
    dot->mVelY = 0;
    dot->mPosX = 0;
    dot->mVelX = 0;
}

void shiftColliders(Dot* dot) {
    dot->mCollider.x = dot->mPosX;
    dot->mCollider.y = dot->mPosY;
}