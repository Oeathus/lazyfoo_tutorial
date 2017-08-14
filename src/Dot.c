//
// Created by Timothy Haskins on 8/11/17.
//
#include "Dot.h"

void Dot_init(Dot* dot, int x, int y) {
    dot->mPosX = x;
    dot->mVelX = 0;
    dot->mPosY = y;
    dot->mVelY = 0;

    dot->mColliders.count = 11;
    dot->mColliders.boxes = calloc(dot->mColliders.count, sizeof(SDL_Rect));
    //Initialize the collision boxes' width and height
    dot->mColliders.boxes[0].w = 6;
    dot->mColliders.boxes[0].h = 1;
    dot->mColliders.boxes[1].w = 10;
    dot->mColliders.boxes[1].h = 1;
    dot->mColliders.boxes[2].w = 14;
    dot->mColliders.boxes[2].h = 1;
    dot->mColliders.boxes[3].w = 16;
    dot->mColliders.boxes[3].h = 2;
    dot->mColliders.boxes[4].w = 18;
    dot->mColliders.boxes[4].h = 2;
    dot->mColliders.boxes[5].w = 20;
    dot->mColliders.boxes[5].h = 6;
    dot->mColliders.boxes[6].w = 18;
    dot->mColliders.boxes[6].h = 2;
    dot->mColliders.boxes[7].w = 16;
    dot->mColliders.boxes[7].h = 2;
    dot->mColliders.boxes[8].w = 14;
    dot->mColliders.boxes[8].h = 1;
    dot->mColliders.boxes[9].w = 10;
    dot->mColliders.boxes[9].h = 1;
    dot->mColliders.boxes[10].w = 6;
    dot->mColliders.boxes[10].h = 1;
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

void Dot_move(Dot* dot, MColliders* otherColliders) {
    dot->mPosX += dot->mVelX;
    shiftColliders(dot);

    if (dot->mPosX < 0 || (dot->mPosX + DOT_WIDTH > SCREEN_WIDTH) ||
        checkCollision(&(dot->mColliders), otherColliders)) {
        dot->mPosX -= dot->mVelX;
    }

    dot->mPosY += dot->mVelY;
    shiftColliders(dot);

    if (dot->mPosY < 0 || (dot->mPosY + DOT_HEIGHT > SCREEN_HEIGHT) ||
        checkCollision(&(dot->mColliders), otherColliders)) {
        dot->mPosY -= dot->mVelY;
    }
}

void Dot_render(Dot* dot, LTexture* texture, SDL_Renderer* renderer, SDL_Rect* clip, double angle,
                SDL_Point* center, SDL_RendererFlip flip) {
    LTexture_render(texture, renderer, dot->mPosX, dot->mPosY, clip, angle, center, flip);
}

void Dot_free(Dot* dot) {
    if (dot->mColliders.count && dot->mColliders.boxes) {
        while (--(dot->mColliders.count)) {
            dot->mColliders.boxes[dot->mColliders.count].x = 0;
            dot->mColliders.boxes[dot->mColliders.count].y = 0;
            dot->mColliders.boxes[dot->mColliders.count].w = 0;
            dot->mColliders.boxes[dot->mColliders.count].h = 0;
        }
        free(dot->mColliders.boxes);
        dot->mColliders.boxes = NULL;
    }
    dot->mPosY = 0;
    dot->mVelY = 0;
    dot->mPosX = 0;
    dot->mVelX = 0;
}

void shiftColliders(Dot* dot) {
    int r = 0;
    for (size_t id = 0; id < dot->mColliders.count; ++id) {
        dot->mColliders.boxes[id].x = dot->mPosX + (DOT_WIDTH - dot->mColliders.boxes[id].w) / 2;
        dot->mColliders.boxes[id].y = dot->mPosY + r;
        r += dot->mColliders.boxes[id].h;
    }
}