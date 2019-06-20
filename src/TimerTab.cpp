

#include "TimerTab.h"
#include "lock.h"
#include <iostream.h>
extern volatile unsigned long minTimeElapsed;
extern volatile unsigned long elapsedTime;
extern void stopProgram();

void TimerTable::add(Timer* timer) {
   lock
   TableElement* elem = new TableElement(timer);
   if(!elem) {
	   cout << "\nNOT ENOUGH MEMORY...";
	   stopProgram();
   }
   if(first == 0) first = last = elem;
   else{
	   last->next = elem;
	   last = elem;
   }
   if(timer->getRemainingTime() < minTimeElapsed - elapsedTime) minTimeElapsed = timer->getRemainingTime();
   unlock
}

void TimerTable::setCurFirst() {
	cur = first;
}

Timer* TimerTable::getTimer() {
	if(cur) {
		return cur->timer;
	}
	else
		return 0;
}
void TimerTable::nextTimer() {
	if(cur){
		cur = cur->next;
	}
}

void TimerTable::removeCurentTimer() {
	//lock
    if(cur) {
    	TableElement* old = cur->next;
    	delete cur->timer;
    	if(old == 0) {
    		if(cur == first) {
    		   first = last = 0;
    		   delete cur;
    		}
    		else{
               cur->timer = first->timer;
               old = first;
               first = first->next;
               delete old;
    		}
    		 cur = 0;
    	}
    	else{
    	    cur->timer = old->timer;
            cur->next = old->next;
            if(cur->next == 0) last = cur;
            delete old;
    	}
    }
	//unlock
}

TimerTable::~TimerTable() {
	while(first){
		TableElement* old = first;
		first = first->next;
		delete old->timer;
		delete old;
	}
}



