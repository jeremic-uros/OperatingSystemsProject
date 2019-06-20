#include "KernelEv.h"
#include "KernlSem.h"
#include "PCB.h"
#include <iostream.h>

extern void stopProgram();
ListKernelEv KernelEv::events;
int KernelEv::idGenerator = 1;

void KernelEv::createEvent(IVTNo ivtNo,Event* eve) {
   KernelEv* newEvent = new KernelEv(ivtNo,eve);
   if(!newEvent) {
	   cout << "\nNOT ENOUGH MEMORY...";
	   stopProgram();
   }
   eve->id = newEvent->id;
   KernelEv::events.add(newEvent,newEvent->id);
}
void KernelEv::destoryEvent(int id) {
   delete KernelEv::events.remove(id);
}
void KernelEv::waitEvent(int id) {
   KernelEv* toWait = KernelEv::events[id];
   toWait->wait();
}
void KernelEv::signalEvent(int id) {
   KernelEv* toSignal = KernelEv::events[id];
   toSignal->signal();
}

KernelEv::KernelEv(IVTNo ivtNo,Event* eve ) :id(idGenerator++) {
     ivtEntry = IVTEntry::getEntry(ivtNo);
     ivtEntry->setEvent(eve);
     ivtEntry->setInterruptVector();
     ThreadId = ((PCB*)PCB::running)->getID();
     waitForEvent = new KernelSem(0);
}

void KernelEv::wait() {
     if( ((PCB*)PCB::running)->getID() == ThreadId){
         waitForEvent->wait(1);
     }
}

void KernelEv::signal() {
         waitForEvent->signal();
}

KernelEv::~KernelEv() {
    delete waitForEvent;
    ivtEntry->restoreInterruptVector();
}
