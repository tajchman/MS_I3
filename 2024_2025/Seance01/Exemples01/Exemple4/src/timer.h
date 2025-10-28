#ifndef _TIMER_H
#define _TIMER_H

#ifdef WIN32
#include <windows.h>

typedef struct Tm
{
    const char * name;
    double elapsed;
    LARGE_INTEGER frequency;
    LARGE_INTEGER t0;
} Timer;

#else
#include <time.h>

typedef struct Tm
{
    const char * name;
    double elapsed;
    struct timespec ts0;
} Timer;

#endif

void TimerStart(Timer *T);
void TimerStop(Timer *T);

#endif
