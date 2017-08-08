#include "main.h"

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
        success = false;
    else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
            fprintf(stderr, "SDL Hint???? : %s", SDL_GetError());

        if ((gWindow = SDL_CreateWindow("LazyFoo Tutorial",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL)
            success = false;
        else {
            if ((gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED)) == NULL)
                success = false;
            else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags))
                    success = false;
            }
        }
    }

    if (!success)
        fprintf(stderr, "SLD failed to initialize: %s\n", SDL_GetError());

    return success;
}

bool loadMedia() {
    bool success = true;

    if (loadLTextureFromFile(&gSpriteSheetTexture, "resources/dots.png")) {
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 100;
        gSpriteClips[0].h = 100;

        gSpriteClips[1].x = 100;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 100;
        gSpriteClips[1].h = 100;

        gSpriteClips[2].x = 0;
        gSpriteClips[2].y = 100;
        gSpriteClips[2].w = 100;
        gSpriteClips[2].h = 100;

        gSpriteClips[3].x = 100;
        gSpriteClips[3].y = 100;
        gSpriteClips[3].w = 100;
        gSpriteClips[3].h = 100;
    } else {
        success = false;
        fprintf(stderr, "loadMedia() Failed!\n");
    }

    return success;
}

void closer() {
    destroyLTexture(&gTexture);
    destroyLTexture(&gTextureBackground);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

SDL_Texture* loadTexture(const char* path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadSurface = IMG_Load(path);

    if (loadSurface == NULL)
        fprintf(stderr, "Unable to load image %s! SDL_Image Error: %s", path, IMG_GetError());
    else {
        if ((newTexture = SDL_CreateTextureFromSurface(gRenderer, loadSurface)) == NULL)
            fprintf(stderr, "Unable to create texture from %s! SDL Error: %s", path, SDL_GetError());

        SDL_FreeSurface(loadSurface);
    }

    return newTexture;
}

bool loadLTextureFromFile(LTexture* texture, const char* path) {
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path);

    if (loadedSurface == NULL) {
        fprintf(stderr, "Unable to load image %s, SDL_Image Error: %s\n", path, IMG_GetError());
        return false;
    }

    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 255, 255));
    newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

    if (newTexture == NULL) {
        fprintf(stderr, "Unable to create texture from %s! SDL Error: %s\n", path, IMG_GetError());
        return false;
    }

    destroyLTexture(texture);

    texture->mWidth = loadedSurface->w;
    texture->mHeight = loadedSurface->h;

    SDL_FreeSurface(loadedSurface);

    texture->mTexture = newTexture;

    return texture->mTexture != NULL;
}

void setLTextureColor(LTexture* texture, Uint8 red, Uint8 green, Uint8 blue) {
    SDL_SetTextureColorMod(texture->mTexture, red, green, blue);
}

void renderLTexture(LTexture* texture, int x, int y, SDL_Rect* clip) {
    SDL_Rect renderQuad = {x, y, texture->mWidth, texture->mHeight};

    if (clip != NULL) {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }

    SDL_RenderCopy(gRenderer, texture->mTexture, clip, &renderQuad);
}

void destroyLTexture(LTexture* texture) {
    if (texture->mTexture != NULL) {
        SDL_DestroyTexture(texture->mTexture);
        texture->mTexture = NULL;
        texture->mWidth = 0;
        texture->mHeight = 0;
    }
}

int main(int argc, char* argv[argc + 1]) {
    bool quit = false;
    SDL_Event e;

    Uint8 r = 255;
    Uint8 g = 255;
    Uint8 b = 255;

    if (!init()) {
        fprintf(stderr, "SDL failed to initialize: %s\n", SDL_GetError());
    } else if (!loadMedia()) {
        fprintf(stderr, "SDL failed to load media: %s\n", SDL_GetError());
    }

    while (!quit) {
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                quit = true;
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_q:
                        r += 32;
                        break;
                    case SDLK_w:
                        g += 32;
                        break;
                    case SDLK_e:
                        b += 32;
                        break;
                    case SDLK_a:
                        r -= 32;
                        break;
                    case SDLK_s:
                        g -= 32;
                        break;
                    case SDLK_d:
                        b -= 32;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        setLTextureColor(&gSpriteSheetTexture, r, g, b);

        renderLTexture(&gSpriteSheetTexture,
                       0, 0, &gSpriteClips[0]);

        renderLTexture(&gSpriteSheetTexture,
                       SCREEN_WIDTH - gSpriteClips[1].w, 0,
                       &gSpriteClips[1]);

        renderLTexture(&gSpriteSheetTexture,
                       0, SCREEN_HEIGHT - gSpriteClips[2].h,
                       &gSpriteClips[2]);

        renderLTexture(&gSpriteSheetTexture,
                       SCREEN_WIDTH - gSpriteClips[3].w,
                       SCREEN_HEIGHT - gSpriteClips[3].h,
                       &gSpriteClips[3]);

        SDL_RenderPresent(gRenderer);
    }

    closer();
    return EXIT_SUCCESS;
}
