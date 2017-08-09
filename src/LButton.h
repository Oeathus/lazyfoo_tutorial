//
// Created by Timothy Haskins on 8/9/17.
//

#ifndef LAZYFOO_LBUTTON_H
#define LAZYFOO_LBUTTON_H

#include <stdio.h>
#include <stdbool.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#include "LTexture.h"

#define BUTTON_WIDTH 300
#define BUTTON_HEIGHT 200
#define TOTAL_BUTTONS 4

typedef enum {
    BUTTON_SPRITE_MOUSE_OUT = 0,
    BUTTON_SPRITE_MOUSE_OVER_MOTION = 1,
    BUTTON_SPRITE_MOUSE_DOWN = 2,
    BUTTON_SPRITE_MOUSE_UP = 3,
    BUTTON_SPRITE_TOTAL = 4
} LButtonSprite;

typedef struct {
    SDL_Point mPosition;
    LButtonSprite mCurrentSprite;
} LButton;

extern void LButton_setPosition(LButton* button, int x, int y);

extern void LButton_handleEvent(LButton* button, SDL_Event* e);

extern void LButton_render(LButton* button, LTexture* texture, SDL_Rect* clip);

#endif //LAZYFOO_LBUTTON_H
