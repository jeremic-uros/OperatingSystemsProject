#ifndef _KERNEL_SEM_H_
#define _KERNEL_SEM_H_
#include "ListSem.h"
class PCB;
class Semaphore;

class KernelSem {
public:
   KernelSem(int init = 1) : value(init),blockedFirst(0),blockedLast(0),id(idGenerator++) {}
   virtual ~KernelSem();
   virtual int wait(int toBlock);
   virtual void signal();
   void signalAll();
   int val() const;
   static void createSem(int init,int* semId);
   static void destroySem(int id);
   static int waitSem(int id,int toBlock);
   static void signalSem(int id);
   static int valueSem(int id);
protected:
   void block();
   void unblock();
private:
   int value;
   int id;
   static int idGenerator;
   static ListKernelSem semaphores;
   struct BlockedThread{
	   PCB* pcb;
	   BlockedThread* next;
	   BlockedThread(PCB* pcb1) : pcb(pcb1),next(0) {}
   };
   BlockedThread* blockedFirst,*blockedLast;
};

#endif // _KERNEL_SEM_H_
