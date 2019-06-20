
#ifndef PARAMS_H_
#define PARAMS_H_

class Thread;
struct Params_createThread {
   unsigned long stackSize;
   unsigned int timeSlice;
   Thread* thread;
};

struct Params_sleepThread {
	unsigned int timeToSleep;
};

struct Params_createSemaphore{
	int init;
	int* semId;
};

struct Params_waitSemaphore{
	int toBlock;
	int id;
	int ret;
};

struct Params_valSemaphore {
	int id;
	int ret;
};

class Event;
struct Params_createEvent {
    unsigned char ivtNo;
    Event* event;
};



#endif /* PARAMS_H_ */
