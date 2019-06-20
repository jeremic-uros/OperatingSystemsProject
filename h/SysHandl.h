
#ifndef SYSHANDL_H_
#define SYSHANDL_H_
#include "Thread.h"
///////////////System calls////////////////
//		1 - Thread create
//		2 - Thread destroy
//		3 - Thread start
//		4 - Thread join(waitToComplete)
//		5 - Thread sleep
//		6 - Thread finish
//		7 - Dispatch thread
//      8 - Semaphore create
//		9 - Semaphore destroy
//		10 - Sempahore wait
//		11 - Semaphore signal
//		12 - Semaphore value
//		13 - Event create
//		14 - Event destroy
//		15 - Event wait
//		16 - Event signal
//		17 - Wake threads from sleep
///////////////////////////////////////////

class SysCallHandler : public Thread{
public:
	SysCallHandler() : Thread(4096,0) {}
	void run();
};





#endif /* SYSHANDL_H_ */
