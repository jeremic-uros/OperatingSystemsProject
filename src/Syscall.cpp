
#include <dos.h>
#include "PCB.h"
#include "lock.h"
#include "Queue.h"

unsigned ttsp;
unsigned ttss;
volatile unsigned char systemCall = 0;
volatile unsigned char inic = 1;
volatile unsigned int sysCallNumber = -1;
volatile int idHandle = 0;
unsigned char interruptHandlerLock = 0;
InterruptQueue intrQueue;
interruptRt rt = 0;

void* parameters = 0;
void interrupt syscall() {
	if(!inic) {  // for creating krenel Thread SysHandler
	//Transfer to Kernel
	if(!systemCall) {
        asm{
          //Get parameters
          mov   sysCallNumber,bx
          mov   bx, offset parameters
		  mov   idHandle,dx
		  mov	word ptr [bx+2],es
		  mov	word ptr [bx],dx
       }
       asm{ //Save thread context
	      mov ttsp,sp
	      mov ttss,ss
       }
	   PCB::running->sp = ttsp;
	   PCB::running->ss = ttss;
	   ttsp = PCB::runningKernelThread->sp;
	   ttss = PCB::runningKernelThread->ss;
	   asm {
		   mov sp,ttsp
		   mov ss,ttss
	   }
	   systemCall = 1;
	   lock
	}
	else{ 	//Back to running
	  unlock
	  asm {
		  mov ttsp,sp
		  mov ttss,ss
	  }
	  PCB::runningKernelThread->sp = ttsp;
	  PCB::runningKernelThread->ss = ttss;
	  ttsp = PCB::running->sp;
	  ttss = PCB::running->ss;
	  asm {
		 mov sp,ttsp
		 mov ss,ttss
	  }
      systemCall = 0;
      while(!intrQueue.isEmpty()){
    	  rt = intrQueue.get();
          rt();
      }
	}
  }
}

void setSysCallVect() {
	asm {
	  cli
	  push es
	  push ax

	  mov ax,0
	  mov es,ax

	  mov word ptr es:0186h, seg syscall
	  mov word ptr es:0184h, offset syscall

	  pop ax
	  pop es
	  sti
	}
}


