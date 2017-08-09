//
// Created by Timothy Haskins on 8/8/17.
//
#include "LTexture.h"

bool LTexture_loadFromFile(LTexture* texture, const char* path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);

    if (loadedSurface == NULL) {
        fprintf(stderr, "Unable to load image %s, SDL_Image Error: %s\n", path, IMG_GetError());
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
    newTexture = SDL_CreateTextureFromSurface(texture->gRenderer, loadedSurface);

    if (newTexture == NULL) {
        fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", path, IMG_GetError());
        return false;
    }

    LTexture_free(texture);

    texture->mWidth = loadedSurface->w;
    texture->mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    texture->mTexture = newTexture;

    return texture->mTexture != NULL;
}

bool LTexture_loadFromRenderedText(LTexture* texture, TTF_Font* font, char* textureText, SDL_Color textColor) {
    LTexture_free(texture);

    SDL_Surface* textSurface = TTF_RenderText_Solid(font, textureText, textColor);
    if (textSurface != NULL) {
        texture->mTexture = SDL_CreateTextureFromSurface(texture->gRenderer, textSurface);

        if (texture->mTexture != NULL) {
            texture->mWidth = textSurface->w;
            texture->mHeight = textSurface->h;
        } else {
            fprintf(stderr, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
        }

        SDL_FreeSurface(textSurface);
    } else {
        fprintf(stderr, "Unable to create texture from rendered text! SDL Error: %s\n", SDL_GetError());
    }

    return texture->mTexture != NULL;
}

void LTexture_setColor(LTexture* texture, Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture->mTexture, red, green, blue);
}

void LTexture_setBlendMode(LTexture* texture, SDL_BlendMode blending) {
    SDL_SetTextureBlendMode(texture->mTexture, blending);
}

void LTexture_setAlpha(LTexture* texture, Uint8 alpha) {
    SDL_SetTextureAlphaMod(texture->mTexture, alpha);
}

void LTexture_render(LTexture* texture, int x, int y, SDL_Rect* clip,
                     double angle, SDL_Point* center, SDL_RendererFlip flip) {
    SDL_Rect renderQuad = {x, y, texture->mWidth, texture->mHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopyEx(texture->gRenderer, texture->mTexture, clip, &renderQuad,
                     angle, center, flip);
}

void LTexture_free(LTexture* texture) {
    if (texture->mTexture != NULL) {
        SDL_DestroyTexture(texture->mTexture);
        texture->mTexture = NULL;
        texture->mWidth = 0;
        texture->mHeight = 0;
        texture->gRenderer = NULL;
    }
}
