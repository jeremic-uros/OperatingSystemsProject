


#include "PCB.h"
#include "SCHEDULE.H"
#include "Timer.h"
#include "TimerTab.h"
#include <dos.h>
#include <iostream.h>

extern volatile unsigned counter;
extern void stopProgram();
extern TimerTable sleepTable;
volatile PCB* PCB::running = 0;
volatile PCB* PCB::runningKernelThread = 0;
int PCB::idGenerator = 1;
ListPCB PCB::threads;

PCB::~PCB() {
   delete[] stack;
}

void PCB::startThread(ID id) {
   PCB* toStart = threads[id];
   if(toStart && !toStart->hasStarted) {
        Scheduler::put(toStart);
        toStart->hasStarted = 1;
   }
}
void PCB::waitThread(ID id) {
   PCB* toWait = threads[id];
   if(toWait){
	   if(!toWait->hasFinished) toWait->finished.wait(1);
   }
}

void PCB::sleepThread(unsigned int timeToSleep) {
	   Timer* timer = new Timer(timeToSleep);
	   sleepTable.add(timer);
	   timer->sleep();
}

void PCB::finishThread() {
    PCB::running->hasFinished = 1;
    ((PCB*)PCB::running)->finished.signalAll();
}

void PCB::dispatchThread() {
	if(!PCB::running->hasFinished && !PCB::running->isBlocked) Scheduler::put((PCB*)PCB::running);
	PCB::running = Scheduler::get();
    counter = PCB::running->timeSlice;
    if(counter == 0) counter = -1;
}

PCB* PCB::createThread(Time timeSlice,StackSize stackSize,Thread* thread) {
    PCB* newThread = new PCB(timeSlice);
    thread->id = newThread->getID();
    if(stackSize >= 4096) stackSize = 4096; // in case of argument error
    if(timeSlice < 0) timeSlice = 1;
    unsigned* stack = new unsigned[stackSize];
    if(!newThread || !stack) {
        cout << "\nNOT ENOUGH MEMORY...";
        stopProgram();
    }
    newThread->stack = stack; //for deleting afterwards
    stack[stackSize-1] = FP_SEG(thread);
    stack[stackSize-2] = FP_OFF(thread);
    stack[stackSize-3] = 0x200;
    stack[stackSize-4] = FP_SEG(Thread::wrapper);
    stack[stackSize-5] = FP_OFF(Thread::wrapper);
    newThread->sp = FP_OFF(stack+stackSize-14);
    newThread->ss = FP_SEG(stack+stackSize-14);
    PCB::threads.add(newThread,thread->id); //add to list of threads PCB's
    return newThread;
}

void PCB::destroyThread(ID id) {
   delete PCB::threads.remove(id);
}

