
#ifndef SLEEPER_H_
#define SLEEPER_H_
#include "TimerTab.h"

class Sleeper {
public:
	Sleeper(TimerTable* sleepingTh) : sleepingThreads(sleepingTh) {}
    void checkTable();
private:
   static unsigned long MAX_TIME;
   TimerTable* sleepingThreads;
};

#endif /* SLEEPER_H_ */
