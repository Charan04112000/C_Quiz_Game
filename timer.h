#ifndef TIMER_H
#define TIMER_H

#include <signal.h>

extern volatile sig_atomic_t time_up;

void setup_timer();
void disable_timer();

#endif

