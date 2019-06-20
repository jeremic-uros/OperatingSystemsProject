
#include <iostream.h>
#include <stdlib.h>
#include "Thread.h"
#include "PCB.h"
#include "SCHEDULE.H"
#include "Sleeper.h"
#include "SysHandl.h"
#include <dos.h>

extern int userMain (int argc, char* argv[]);
extern void inicTimer();
extern void restoreTimer();
extern void setSysCallVect();
extern volatile unsigned char inic;

TimerTable sleepTable;
Sleeper* sleeper;

class MainThread : public Thread {
	int arg1;
	char** arg2;
public:
	MainThread(int ar1,char** ar2) : Thread(4096,1), arg1(ar1) , arg2(ar2) {}
	void run() {
		userMain(arg1,arg2);
	}
};

class IdleThread : public Thread {
	int toStop;
public:
	IdleThread() : Thread(4096,1),toStop(0) {}
	void run(){
		while(!toStop){dispatch();}
	}
	void stop() { toStop = 1;}
};

PCB kernelPCB(1);
MainThread* mainTh;
IdleThread* idleTh;
void main(int argc, char* argv[]) {
    PCB::running = &kernelPCB;
	inicTimer();
    setSysCallVect();
    SysCallHandler* sysHandler = new SysCallHandler();
    PCB::runningKernelThread = PCB::createThread(0,2048,sysHandler);
    inic = 0;
    sleeper = new Sleeper(&sleepTable);
    mainTh = new MainThread(argc,argv);
    idleTh = new IdleThread();
    idleTh->start();
    mainTh->start();
    mainTh->waitToComplete();
    delete sleeper;
    delete mainTh;
    idleTh->stop();
    idleTh->waitToComplete();
    delete idleTh;
	restoreTimer();
}

void stopProgram() {
    restoreTimer();
    exit(1);
}
