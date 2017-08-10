#include "main.h"

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) >= 0) {
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

                if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
                    fprintf(stderr, "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
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

    //Load music
    gMusic = Mix_LoadMUS("resources/audio/beat.wav");
    if (gMusic == NULL) {
        printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    } //Load sound effects
    gScratch = Mix_LoadWAV("resources/audio/scratch.wav");
    if (gScratch == NULL) {
        printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gHigh = Mix_LoadWAV("resources/audio/high.wav");
    if (gHigh == NULL) {
        printf("Failed to load high sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gMedium = Mix_LoadWAV("resources/audio/medium.wav");
    if (gMedium == NULL) {
        printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }
    gLow = Mix_LoadWAV("resources/audio/low.wav");
    if (gLow == NULL) {
        printf("Failed to load low sound effect! SDL_mixer Error: %s\n", Mix_GetError());
        success = false;
    }

    return success;
}

void closer() {
    LTexture_free(&gTexture);

    TTF_CloseFont(gFont);
    gFont = NULL;

    Mix_FreeChunk(gScratch);
    Mix_FreeChunk(gHigh);
    Mix_FreeChunk(gMedium);
    Mix_FreeChunk(gLow);
    gScratch = NULL;
    gHigh = NULL;
    gMedium = NULL;
    gLow = NULL;

    Mix_FreeMusic(gMusic);
    gMusic = NULL;

    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;

    Mix_Quit();
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
            } else if (e.type == SDL_KEYDOWN) {
                switch (e.key.keysym.sym) {
                    case SDLK_1:
                        Mix_PlayChannel(-1, gHigh, 0);
                        break;
                    case SDLK_2:
                        Mix_PlayChannel(-1, gMedium, 0);
                        break;
                    case SDLK_3:
                        Mix_PlayChannel(-1, gLow, 0);
                        break;
                    case SDLK_4:
                        Mix_PlayChannel(-1, gScratch, 0);
                        break;
                    case SDLK_9:
                        if (Mix_PlayingMusic()) {
                            if (Mix_PausedMusic()) {
                                Mix_ResumeMusic();
                            } else {
                                Mix_PauseMusic();
                            }
                        } else {
                            Mix_PlayMusic(gMusic, -1);
                        }
                        break;
                    case SDLK_0:
                        Mix_HaltMusic();
                        break;
                }
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
