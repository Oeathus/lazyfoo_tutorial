#include "main.h"

bool init() {
    bool success = true;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) >= 0) {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
            fprintf(stderr, "Warning: Linear texture filtering not enabled! : %s", SDL_GetError());
        }

        if ((gWindow = SDL_CreateWindow("LazyFoo Tutorial",
                                        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
                                        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN)) != NULL) {
            if ((gRenderer = SDL_CreateRenderer(gWindow, -1,
                                                SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC))
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

    gFont = TTF_OpenFont("resources/fonts/SourceCodePro/Regular.ttf", 12);
    if (gFont == NULL) {
        printf("Failed to load lazy font! SDL_ttf Error: %s\n", TTF_GetError());
        success = false;
    }

    //Load dot texture
    if (!LTexture_loadFromFile(&gDotTexture, gRenderer, "resources/images/dot.bmp")) {
        fprintf(stderr, "Failed to load dot texture!\n");
        success = false;
    }

    //Load BG texture
    if (!LTexture_loadFromFile(&gBGTexture, gRenderer, "resources/images/bg.png")) {
        fprintf(stderr, "Failed to load BG texture!\n");
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
    LTexture_free(&gDotTexture);
    LTexture_free(&gBGTexture);
    LTexture_free(&gTimeTextTexture);

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

    SDL_Color textColor = {0, 0, 0, 255};
    LTimer fpsTimer = {0, 0, false, false};
    int countedFrames = 0;
    LTimer_start(&fpsTimer);
    char fpsText[11] = {0};

    Dot dot1;
    Dot_init(&dot1, DOT_WIDTH / 2, DOT_HEIGHT / 2);

    SDL_Rect camera = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_Point camPoint;

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
                    default:
                        break;
                }
            }

            Dot_handleEvent(&dot1, &e);
        }

        float avgFPS = countedFrames / (LTimer_getTicks(&fpsTimer) / 1000.f);
        if (avgFPS > 2000000) {
            avgFPS = 0;
        }

        memset(fpsText, 0, 11);
        snprintf(fpsText, 11, "FPS: %2.2f", avgFPS);

        if (!LTexture_loadFromRenderedText(&gTimeTextTexture, gRenderer, gFont, fpsText, textColor)) {
            fprintf(stderr, "Unable to render FPS texture!\n");
        }

        Dot_move(&dot1, NULL, NULL);
        camera.x = (dot1.mPosX + (DOT_WIDTH / 2)) - SCREEN_WIDTH / 2;
        camera.y = (dot1.mPosY + (DOT_HEIGHT / 2)) - SCREEN_HEIGHT / 2;

        if (camera.x < 0) {
            camera.x = 0;
        }
        if (camera.y < 0) {
            camera.y = 0;
        }
        if (camera.x > LEVEL_WIDTH - camera.w) {
            camera.x = LEVEL_WIDTH - camera.w;
        }
        if (camera.y > LEVEL_HEIGHT - camera.h) {
            camera.y = LEVEL_HEIGHT - camera.h;
        }

        camPoint.x = camera.x;
        camPoint.y = camera.y;

        SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
        SDL_RenderClear(gRenderer);

        SDL_SetRenderDrawColor(gRenderer, 0x00, 0x00, 0x00, 0xFF);

        LTexture_render(&gBGTexture, gRenderer, 0, 0, &camera, 0, NULL, SDL_FLIP_NONE);

        Dot_render(&dot1, &gDotTexture, gRenderer, NULL, 0, NULL, SDL_FLIP_NONE, &camPoint);

        LTexture_render(&gTimeTextTexture, gRenderer,
                        0, SCREEN_HEIGHT - gTimeTextTexture.mHeight,
                        NULL, 0, NULL, SDL_FLIP_NONE);

        SDL_RenderPresent(gRenderer);
        ++countedFrames;
    }

    Dot_free(&dot1);
    closer();
    return EXIT_SUCCESS;
}
