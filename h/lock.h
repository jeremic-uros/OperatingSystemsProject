#ifndef _LOCK_H_
#define _LOCK_H_

extern volatile int contextSwitchLock;
extern unsigned int lockCount;
#define lock contextSwitchLock = 1; \
	         lockCount++;
#define unlock if(!(--lockCount)) contextSwitchLock = 0;

#endif
