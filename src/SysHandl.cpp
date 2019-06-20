

#include "SysHandl.h"
#include "PCB.h"
#include "KernlSem.h"
#include "KernelEv.h"
#include "Sleeper.h"
#include <dos.h>
#include "Params.h"

extern void* parameters;
extern volatile unsigned int sysCallNumber;
extern volatile int idHandle;
extern Sleeper* sleeper;

void SysCallHandler::run() {
	while(1){
		switch(sysCallNumber){
		case 1:
            Params_createThread* par_create = (Params_createThread*) parameters;
            PCB::createThread(par_create->timeSlice,par_create->stackSize,par_create->thread);
            delete par_create;
            break;
		case 2:
			PCB::destroyThread(idHandle);
			break;
		case 3:
			PCB::startThread(idHandle);
			break;
		case 4:
			PCB::waitThread(idHandle);
			break;
		case 5:
            Params_sleepThread* par_sleep = (Params_sleepThread*) parameters;
			PCB::sleepThread(par_sleep->timeToSleep);
			delete par_sleep;
			break;
		case 6:
            PCB::finishThread();
            break;
		case 7:
            PCB::dispatchThread();
            break;
		case 8:
			Params_createSemaphore* par_createSem = (Params_createSemaphore*) parameters;
			KernelSem::createSem(par_createSem->init,par_createSem->semId);
			delete par_createSem;
			break;
		case 9:
			KernelSem::destroySem(idHandle);
			break;
		case 10:
			Params_waitSemaphore* par_waitSem = (Params_waitSemaphore*) parameters;
			par_waitSem->ret = KernelSem::waitSem(par_waitSem->id,par_waitSem->toBlock);
			break;
		case 11:
		    KernelSem::signalSem(idHandle);
		    break;
		case 12:
			Params_valSemaphore* par_valSem = (Params_valSemaphore*) parameters;
			par_valSem->ret = KernelSem::valueSem(par_valSem->id);
			break;
		case 13:
		    Params_createEvent* par_createEve = (Params_createEvent*) parameters;
		    KernelEv::createEvent(par_createEve->ivtNo,par_createEve->event);
		    delete par_createEve;
		    break;
		case 14:
			KernelEv::destoryEvent(idHandle);
			break;
		case 15:
			KernelEv::waitEvent(idHandle);
			break;
		case 16:
			KernelEv::signalEvent(idHandle);
			break;
		case 17:
			sleeper->checkTable();
			break;
		default:
            break;
		}
        asm int 61h
	}
}

