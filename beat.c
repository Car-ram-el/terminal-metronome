#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <sched.h>

const long NSEC_LIMIT = 1000000000; 

int main() {    
    struct timespec t0, target, interval, curTime;
    
    if (clock_gettime(CLOCK_MONOTONIC, &t0) == -1) {
        printf("Error getting current clock time\n");
        return 1;
    }
    
    target = t0;
    interval.tv_sec = 0, interval.tv_nsec = 500000000;
    int i = 0;

    while (1) {
        int res = clock_nanosleep(CLOCK_MONOTONIC, TIMER_ABSTIME, &target, NULL);
        if (res) { printf("Error in clock_nanosleep()"); return 1;}
        
    struct sched_param schedParam;    
    schedParam.sched_priority = sched_get_priority_max(SCHED_FIFO);
    if (sched_setscheduler(0, SCHED_FIFO, &schedParam) == -1) {
        printf("sched_setscheduler failed\n");
        return 1;
    }
        target.tv_sec += interval.tv_sec; // not used right now, but for later
        target.tv_nsec += interval.tv_nsec;
        if (target.tv_nsec >= NSEC_LIMIT) target.tv_sec++, target.tv_nsec -= 1e9;

        clock_gettime(CLOCK_MONOTONIC, &curTime);

        printf("%ld sec %ld nsec, tick\n", curTime.tv_sec, curTime.tv_nsec);
    }
}
