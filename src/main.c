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

    gModulatedTexture.gRenderer = gRenderer;
    gBackgroundTexture.gRenderer = gRenderer;

    if (LTexture_loadFromFile(&gModulatedTexture, "resources/fadeout.png")) {
        LTexture_setBlendMode(&gModulatedTexture, SDL_BLENDMODE_BLEND);
    } else {
        success = false;
        fprintf(stderr, "LTexture_loadFromFile Failed!\n");
    }

    if (!LTexture_loadFromFile(&gBackgroundTexture, "resources/fadein.png")) {
        success = false;
        fprintf(stderr, "LTexture_loadFromFile Failed!\n");
    }

    return success;
}

void closer() {
    LTexture_free(&gModulatedTexture);
    LTexture_free(&gBackgroundTexture);
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

    Uint8 a = 255;

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
                if (e.key.keysym.sym == SDLK_w) {
                    if (a + 32 > 255) {
                        a = 255;
                    } else {
                        a += 32;
                    }
                } else if (e.key.keysym.sym == SDLK_s) {
                    if (a - 32 < 0) {
                        a = 0;
                    } else {
                        a -= 32;
                    }
                }
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        LTexture_render(&gBackgroundTexture, 0, 0, NULL);

        LTexture_setAlpha(&gModulatedTexture, a);
        LTexture_render(&gModulatedTexture, 0, 0, NULL);

        SDL_RenderPresent(gRenderer);
    }

    closer();
    return EXIT_SUCCESS;
}
