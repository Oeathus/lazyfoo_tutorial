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

    //Load sprites
    if (LTexture_loadFromFile(&gTexture, "resources/images/button.png")) {
        //Set sprites
        for (int i = 0; i < BUTTON_SPRITE_TOTAL; ++i) {
            gSpriteClips[i].x = 0;
            gSpriteClips[i].y = i * 200;
            gSpriteClips[i].w = BUTTON_WIDTH;
            gSpriteClips[i].h = BUTTON_HEIGHT;
        }

        //Set buttons in corners
        LButton_setPosition(&gButtons[0], 0, 0);
        LButton_setPosition(&gButtons[1], SCREEN_WIDTH - BUTTON_WIDTH, 0);
        LButton_setPosition(&gButtons[2], 0, SCREEN_HEIGHT - BUTTON_HEIGHT);
        LButton_setPosition(&gButtons[3], SCREEN_WIDTH - BUTTON_WIDTH, SCREEN_HEIGHT - BUTTON_HEIGHT);
    } else {
        fprintf(stderr, "Failed to load button sprite texture!\n");
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

    LTexture* currentTexture = NULL;
    double angle = 0;
    SDL_RendererFlip flip = SDL_FLIP_NONE;

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

            for (int i = 0; i < TOTAL_BUTTONS; ++i) {
                LButton_handleEvent(&(gButtons[i]), &e);
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_UP]) {
            flip = SDL_FLIP_VERTICAL;
        } else if (currentKeyStates[SDL_SCANCODE_LEFT]) {
            flip = SDL_FLIP_HORIZONTAL;
        } else {
            flip = SDL_FLIP_NONE;
        }

        if (currentKeyStates[SDL_SCANCODE_DOWN]) {
            angle = 90.0;
        } else if (currentKeyStates[SDL_SCANCODE_RIGHT]) {
            angle = 270.0;
        } else {
            angle = 0.0;
        }

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        for (int i = 0; i < TOTAL_BUTTONS; ++i) {
            LButton_render(&(gButtons[i]), &gTexture, &(gSpriteClips[gButtons[i].mCurrentSprite]),
                           angle, NULL, flip);
        }

        SDL_RenderPresent(gRenderer);
    }

    closer();
    return EXIT_SUCCESS;
}
