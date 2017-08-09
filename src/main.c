#include "main.h"

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        success = false;
    } else {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "SDL Hint???? : %s", SDL_GetError());
        }

        if ((gWindow = SDL_CreateWindow("LazyFoo Tutorial",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) == NULL) {
            success = false;
        } else {
            if ((gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
                == NULL) {
                success = false;
            } else {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    success = false;
                }
            }
        }
    }

    if (!success) {
        fprintf(stderr, "SLD failed to initialize: %s\n", SDL_GetError());
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    gSpriteSheetTexture.gRenderer = gRenderer;

    if (LTexture_loadFromFile(&gSpriteSheetTexture, "resources/foo.png")) {
        //Set sprite clips
        gSpriteClips[0].x = 0;
        gSpriteClips[0].y = 0;
        gSpriteClips[0].w = 64;
        gSpriteClips[0].h = 205;

        gSpriteClips[1].x = 64;
        gSpriteClips[1].y = 0;
        gSpriteClips[1].w = 64;
        gSpriteClips[1].h = 205;

        gSpriteClips[2].x = 128;
        gSpriteClips[2].y = 0;
        gSpriteClips[2].w = 64;
        gSpriteClips[2].h = 205;

        gSpriteClips[3].x = 196;
        gSpriteClips[3].y = 0;
        gSpriteClips[3].w = 64;
        gSpriteClips[3].h = 205;
    } else {
        fprintf(stderr, "Failed to load walking animation texture!\n");
        success = false;
    }

    return success;
}

void closer() {
    LTexture_free(&gSpriteSheetTexture);
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);

    gRenderer = NULL;
    gWindow = NULL;

    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[argc + 1]) {
    bool quit = false;
    SDL_Event e;

    int frame = 0;
    double degrees = 0;
    SDL_RendererFlip flipType = SDL_FLIP_NONE;

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
                    case SDLK_a:
                        degrees -= 60;
                        break;
                    case SDLK_d:
                        degrees += 60;
                        break;
                    case SDLK_q:
                        flipType = SDL_FLIP_HORIZONTAL;
                        break;
                    case SDLK_w:
                        flipType = SDL_FLIP_NONE;
                        break;
                    case SDLK_e:
                        flipType = SDL_FLIP_VERTICAL;
                        break;
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_Rect* currentClip = &gSpriteClips[frame / 4];
        LTexture_render(&gSpriteSheetTexture,
                        (SCREEN_WIDTH - currentClip->w) / 2,
                        (SCREEN_HEIGHT - currentClip->h) / 2,
                        currentClip, degrees, NULL, flipType);

        SDL_RenderPresent(gRenderer);

        if (++frame / 4 >= WALKING_ANIMATION_FRAMES) {
            frame = 0;
        }
    }

    closer();
    return EXIT_SUCCESS;
}
