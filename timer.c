#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include "timer.h"

volatile sig_atomic_t time_up = 0;

void handle_alarm(int sig) {
    time_up = 1;
    printf("\n⏰ Time's up!\n");
}

void setup_timer() {
    time_up = 0;
    signal(SIGALRM, handle_alarm);
    alarm(10);  // 10 seconds
}

void disable_timer() {
    alarm(0);
}

