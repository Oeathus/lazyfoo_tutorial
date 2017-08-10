//
// Created by Timothy Haskins on 8/10/17.
//

#include "LTimer.h"

void LTimer_start(LTimer* timer) {
    timer->mStarted = true;
    timer->mPaused = false;
    timer->mStartTicks = SDL_GetTicks();
    timer->mPausedTicks = 0;
}

void LTimer_stop(LTimer* timer) {
    timer->mStarted = false;
    timer->mPaused = false;
    timer->mStartTicks = 0;
    timer->mPausedTicks = 0;
}

void LTimer_pause(LTimer* timer) {
    if (timer->mStarted && !timer->mPaused) {
        timer->mPaused = true;
        timer->mPausedTicks = SDL_GetTicks() - timer->mStartTicks;
        timer->mStartTicks = 0;
    }
}

void LTimer_unpause(LTimer* timer) {
    if (timer->mStarted && timer->mPaused) {
        timer->mPaused = false;
        timer->mStartTicks = SDL_GetTicks() - timer->mPausedTicks;
        timer->mPausedTicks = 0;
    }
}

Uint32 LTimer_getTicks(LTimer* timer) {
    Uint32 time = 0;

    if (timer->mStarted) {
        if (timer->mPaused) {
            time = timer->mPausedTicks;
        } else {
            time = SDL_GetTicks() - timer->mStartTicks;
        }
    }

    return time;
}