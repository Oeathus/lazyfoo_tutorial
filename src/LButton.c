//
// Created by Timothy Haskins on 8/9/17.
//
#include "LButton.h"

void LButton_setPosition(LButton* button, int x, int y) {
    button->mPosition.x = x;
    button->mPosition.y = y;
}

void LButton_handleEvent(LButton* button, SDL_Event* e) {
    if (e->type == SDL_MOUSEMOTION
        || e->type == SDL_MOUSEBUTTONDOWN
        || e->type == SDL_MOUSEBUTTONUP) {
        int x, y;
        bool inside = true;

        SDL_GetMouseState(&x, &y);

        if (x < button->mPosition.x) {
            inside = false;
        } else if (x > button->mPosition.x + BUTTON_WIDTH) {
            inside = false;
        } else if (y < button->mPosition.y) {
            inside = false;
        } else if (y > button->mPosition.y + BUTTON_HEIGHT) {
            inside = false;
        }

        if (inside) {
            switch (e->type) {
                case SDL_MOUSEMOTION:
                    button->mCurrentSprite = BUTTON_SPRITE_MOUSE_OVER_MOTION;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    button->mCurrentSprite = BUTTON_SPRITE_MOUSE_DOWN;
                    break;
                case SDL_MOUSEBUTTONUP:
                    button->mCurrentSprite = BUTTON_SPRITE_MOUSE_UP;
                    break;
            }
        } else {
            button->mCurrentSprite = BUTTON_SPRITE_MOUSE_OUT;
        }
    }
}

void LButton_render(LButton* button, LTexture* texture, SDL_Rect* clip,
                    double angle, SDL_Point* center, SDL_RendererFlip flip) {
    LTexture_render(texture, NULL, button->mPosition.x, button->mPosition.y, clip, angle, center, flip);
}
