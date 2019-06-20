
#include "KernlSem.h"
#include "lock.h"
#include "SCHEDULE.H"
#include "PCB.h"
#include <iostream.h>


extern void stopProgram();
ListKernelSem KernelSem::semaphores;
int KernelSem::idGenerator = 1;

void KernelSem::createSem(int init,int* semId) {
    KernelSem* newSem = new KernelSem(init);
    if(!newSem) {
    	cout << "\nNOT ENOUGH MEMORY...";
    	stopProgram();
    }
    *semId = newSem->id;
    KernelSem::semaphores.add(newSem,newSem->id);
}
void KernelSem::destroySem(int id) {
    delete KernelSem::semaphores.remove(id);
}
int KernelSem::waitSem(int id,int toBlock) {
    KernelSem* toWait = KernelSem::semaphores[id];
    return toWait->wait(toBlock);
}

void KernelSem::signalSem(int id) {
	KernelSem* toSignal = KernelSem::semaphores[id];
	toSignal->signal();
}
int KernelSem::valueSem(int id) {
    KernelSem* value = KernelSem::semaphores[id];
    return value->val();
}

KernelSem::~KernelSem() {}
int KernelSem::val() const { return value; }
int KernelSem::wait(int toBlock) {
    lock
	int ret = 0;
    if(!toBlock && value <= 0) return -1;
	if(--value < 0){
        block();
        ret = 1;
	}
	unlock
	return ret;
}
void KernelSem::signal() {
	lock
	if(value++<0) unblock();
	unlock
}

void KernelSem::signalAll() {
	lock
	while(blockedFirst)
		unblock();
	unlock
}

void KernelSem::block() {
	PCB::running->isBlocked = 1;
	BlockedThread* toAdd = new BlockedThread((PCB*)PCB::running);
    if(blockedFirst == 0) blockedFirst = blockedLast = toAdd;
    else {
    	blockedLast->next = toAdd;
    	blockedLast = toAdd;
    }
    PCB::dispatchThread();
}
void KernelSem::unblock() {
	if(blockedFirst) {
	  BlockedThread* out = blockedFirst;
      blockedFirst = blockedFirst->next;
      if(!blockedFirst) blockedLast = 0;
	  out->pcb->isBlocked = 0;
      Scheduler::put(out->pcb);
      delete out;
	}
}
