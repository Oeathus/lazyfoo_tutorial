//
// Created by Timothy Haskins on 8/10/17.
//

#ifndef LAZYFOO_LTIMER_H
#define LAZYFOO_LTIMER_H

#include "globals.h"

#define LTimer_isPaused(timer) (timer.mStarted && timer.mPaused)

typedef struct LTimer {
    Uint32 mStartTicks;
    Uint32 mPausedTicks;
    bool mPaused;
    bool mStarted;
} LTimer;

extern void LTimer_start(LTimer* timer);

extern void LTimer_stop(LTimer* timer);

extern void LTimer_pause(LTimer* timer);

extern void LTimer_unpause(LTimer* timer);

extern Uint32 LTimer_getTicks(LTimer* timer);

#endif //LAZYFOO_LTIMER_H
