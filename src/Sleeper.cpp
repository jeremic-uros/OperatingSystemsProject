
#include "Sleeper.h"
#include "lock.h"

unsigned long Sleeper::MAX_TIME = ~0;
volatile unsigned int minTimeElapsed = ~0;
extern volatile unsigned int elapsedTime;


void Sleeper::checkTable() {
	volatile unsigned long elapsed;
    elapsed = elapsedTime;
    elapsedTime = 0;
    minTimeElapsed = Sleeper::MAX_TIME;
    lock
    sleepingThreads->setCurFirst();
    Timer* next = sleepingThreads->getTimer();
    while(next){
         int ret = next->updateTime(elapsed);
         if(ret <= 0 ) {
      	   sleepingThreads->removeCurentTimer();
         }
         else {
      	   sleepingThreads->nextTimer();
      	   if( ret  < minTimeElapsed) minTimeElapsed = ret;
         }
         next = sleepingThreads->getTimer();
    }
    unlock
}

