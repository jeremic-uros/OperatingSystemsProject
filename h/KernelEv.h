
#ifndef KERNELEV_H_
#define KERNELEV_H_
#include "Event.h"
#include "ListEve.h"

class KernelSem;
class KernelEv {
public:
	KernelEv(IVTNo ivtNo,Event* eve);
	~KernelEv();
    void wait();
    void signal();
    static void createEvent(IVTNo ivtNo,Event* eveID);
    static void destoryEvent(int id);
    static void waitEvent(int id);
    static void signalEvent(int id);
private:
    friend class IVTEntry;
    static void signalEvent(Event* eve) { eve->signal(); }
    IVTEntry* ivtEntry;
    int ThreadId;
    static int idGenerator;
    int id;
    KernelSem* waitForEvent;
    static ListKernelEv events;
};




#endif /* KERNELEV_H_ */
