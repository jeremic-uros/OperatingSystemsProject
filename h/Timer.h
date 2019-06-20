


#ifndef TIMER_H_
#define TIMER_H_
#include "KernlSem.h"

class Timer {
public:
	Timer(unsigned long startTime) : counter(startTime),sleepingThread(0) {	}
    long updateTime(unsigned long elapsedTime);
    void sleep() { sleepingThread.wait(1); }
    unsigned long getRemainingTime() const { return counter; }
private:
	long counter;
	KernelSem sleepingThread;
};




#endif /* TIMER_H_ */
