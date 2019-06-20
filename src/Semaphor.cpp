

#include "Semaphor.h"
#include <dos.h>
#include "Params.h"
unsigned s1,s2;
Semaphore::Semaphore(int init) :id(0){
	  Params_createSemaphore* params = new Params_createSemaphore();
	  params->init = init;
	  params->semId = &id;
	  s1 = FP_OFF(params);
	  s2 = FP_SEG(params);
	  asm {
		  mov bx,8
		  mov dx,s1
		  mov es,s2
		  int 61h
	  }
}
int Semaphore::wait(int toBlock) {
	Params_waitSemaphore* params = new Params_waitSemaphore();
	params->toBlock = toBlock;
	params->id = id;
	s1 = FP_OFF(params);
	s2 = FP_SEG(params);
	asm {
		  mov bx,10
		  mov dx,s1
		  mov es,s2
		  int 61h
	  }
	int ret = params->ret;
	delete params;
	return ret;
}
void Semaphore::signal() {
	int SemaphoreID = id;
	asm{
		mov bx,11
		mov dx,SemaphoreID
		int 61h
	}

}
int Semaphore::val() const {
	Params_valSemaphore* params = new Params_valSemaphore();
	params->id = id;
	s1 = FP_OFF(params);
	s2 = FP_SEG(params);
	asm {
		  mov bx,12
		  mov dx,s1
		  mov es,s2
		  int 61h
	}
	int ret = params->ret;
	delete params;
	return ret;
}
Semaphore::~Semaphore() {
	int SemaphoreID = id;
	asm {
		mov bx,9
		mov dx,SemaphoreID
		int 61h
	}
}
