

#include "Timer.h"

long Timer::updateTime(unsigned long elapsedTime) {
   counter -= elapsedTime; // 55ms
   if(counter <= 0) sleepingThread.signal();
   return counter;
}



