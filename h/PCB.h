
#ifndef _PCB_H_
#define _PCB_H_
#include "Thread.h"
#include "KernlSem.h"
#include "ListPCB.h"

class PCB {
	static int idGenerator;
	ID id;
    unsigned int ss;
    unsigned int sp;
    unsigned int timeSlice;
    unsigned char hasFinished;
    unsigned char hasStarted;
    unsigned char isBlocked;
    unsigned* stack;
    KernelSem finished;
    static ListPCB threads; // list of all threads PCB's
public:
    friend class Thread;
    friend void interrupt timer();
    friend void interrupt syscall();
    friend PCB* createThread(Time,StackSize,Thread*);
    friend class KernelSem;
    volatile static PCB* running;
    volatile static PCB* runningKernelThread;
    PCB(unsigned int time) : ss(0) , sp(0) , timeSlice(time) , hasFinished(0) , hasStarted(0) , stack(0) , isBlocked(0) ,finished(0) {
    	id = idGenerator++;
    }
    ~PCB();
    ID getID() { return id; }
    static void startThread(ID id);
    static void waitThread(ID id);
    static PCB* createThread(Time timeSlice,StackSize stackSize,Thread* thread);
    static void destroyThread(ID id);
    static void sleepThread(unsigned int timeToSleep);
    static void finishThread();
    static void dispatchThread();
};

#endif /* _PCB_H_ */
