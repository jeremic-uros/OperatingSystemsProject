

#include <dos.h>
#include "PCB.h"
#include "SCHEDULE.h"
#include "Queue.h"

extern volatile unsigned long minTimeElapsed;
extern void tick();
extern volatile unsigned char systemCall;
extern InterruptQueue intrQueue;
volatile int contextSwitchLock = 0;
volatile Time elapsedTime = 0;
unsigned tsp;
unsigned tss;
volatile unsigned counter = 10;

void interrupt timer() {
  asm int 60h;
  if(!systemCall) {
    tick();
    counter--;
    elapsedTime++;
    if(elapsedTime >= minTimeElapsed){
    	asm{
    		mov bx,17
			int 61h
    	}
    }
	if(!contextSwitchLock && counter == 0)
          dispatch();
  }
  else{
	  intrQueue.put(timer);
  }
}


unsigned oldTimerSEG,oldTimerOFF;
void inicTimer() {
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax

		mov ax, word ptr es:0022h
		mov word ptr oldTimerSEG, ax
		mov ax, word ptr es:0020h
		mov word ptr oldTimerOFF, ax

		mov word ptr es:0022h, seg timer
		mov word ptr es:0020h, offset timer

		mov ax, oldTimerSEG
		mov word ptr es:0182h, ax
		mov ax, oldTimerOFF
		mov word ptr es:0180h, ax

		pop ax
		pop es
		sti
	}
}

void restoreTimer() {
	asm {
		cli
		push es
		push ax

		mov ax,0
		mov es,ax


		mov ax, word ptr oldTimerSEG
		mov word ptr es:0022h, ax
		mov ax, word ptr oldTimerOFF
		mov word ptr es:0020h, ax

		pop ax
		pop es
		sti
	}
}


