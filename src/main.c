#include "main.h"

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO) >= 0) {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "SDL Hint???? : %s", SDL_GetError());
        }

        if ((gWindow = SDL_CreateWindow("LazyFoo Tutorial",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) != NULL) {
            if ((gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
                != NULL) {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

                int imgFlags = IMG_INIT_PNG;

                if (!(IMG_Init(imgFlags) & imgFlags)) {
                    success = false;
                }

                if (TTF_Init() == -1) {
                    success = false;
                }
            } else {
                success = false;
            }
        } else {
            success = false;
        }
    } else {
        success = false;
    }

    if (!success) {
        fprintf(stderr, "SLD failed to initialize: %s\n", SDL_GetError());
    }

    return success;
}

bool loadMedia() {
    bool success = true;

    gTexture.gRenderer = gRenderer;
    if ((gFont = TTF_OpenFont("resources/Oeathus.ttf", 28)) != NULL) {
        SDL_Color textColor = {0, 0, 0};

        if (!LTexture_loadFromRenderedText(
                &gTexture, gFont, "The quick brown fox jumps over the lazy dog", textColor)) {
            fprintf(stderr, "Failed to render text texture!\n");
            success = false;
        }
    } else {
        fprintf(stderr, "Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    return success;
}

void closer() {
    LTexture_free(&gTexture);

    TTF_CloseFont(gFont);
    gFont = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    TTF_Quit();
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
            }
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        LTexture_render(&gTexture,
                        (SCREEN_WIDTH - gTexture.mWidth) / 2,
                        (SCREEN_HEIGHT - gTexture.mHeight) / 2,
                        NULL, 0, NULL, SDL_FLIP_NONE
        );

        SDL_RenderPresent(gRenderer);
    }

    closer();
    return EXIT_SUCCESS;
}
