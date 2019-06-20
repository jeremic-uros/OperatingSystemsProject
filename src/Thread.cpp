
#include "Thread.h"
#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.H"
#include "Params.h"

unsigned h1,h2;

Thread::Thread(StackSize stackSize, Time timeSlice) :id(0) {
  Params_createThread* params = new Params_createThread();
  params->stackSize = stackSize;
  params->timeSlice = timeSlice;
  params->thread = this;
  h1 = FP_OFF(params);
  h2 = FP_SEG(params);
  asm {
	  mov bx,1
	  mov dx,h1
	  mov es,h2
	  int 61h
  }
}

void Thread::start() {
  volatile int ThreadID = id;
  asm{
	  mov bx,3
	  mov dx,ThreadID
	  int 61h
  }
}

Thread::~Thread() {
   volatile int ThreadID = id;
   asm {
      mov bx,2
	  mov dx,ThreadID
	  int 61h
   }
}

void Thread::waitToComplete() {
   unsigned ThreadID = id;
   asm {
	  mov bx,4
	  mov dx,ThreadID
	  int 61h
   }
}

void Thread::sleep(Time timeToSleep) {
  Params_sleepThread* params = new Params_sleepThread();
  params->timeToSleep = timeToSleep;
  h1 = FP_OFF(params);
  h2 = FP_SEG(params);
  asm {
	  mov bx,5
	  mov dx,h1
	  mov es,h2
	  int 61h
  }
}

void Thread::wrapper(Thread* running) {
    asm {
    	sub bp,4
		mov sp,bp
    }
	running->run();
	asm {
		mov bx,6
		int 61h
	}
	dispatch();
}


void dispatch() {
	  asm{
		  mov bx,7
		  int 61h
	  }
}












