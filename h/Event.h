// File: event.h
#ifndef _event_h_
#define _event_h_
typedef unsigned char IVTNo;
#include "IVTEntry.h"
#include <dos.h>

#define PREPAREENTRY(ivtNo, toKeep) extern volatile char systemCall;\
        void interrupt routine##ivtNo##(...) { \
        if(systemCall)\
	        IVTEntry::getEntry(##ivtNo##)->addToInterruptQueue();\
	    else\
            IVTEntry::getEntry(##ivtNo##)->signalCallWrapper(); \
	    if(##toKeep##){ \
	    	IVTEntry::getEntry(##ivtNo##)->callOldRoutine();\
	    }\
    }\
    IVTEntry entry##ivtNo##(##ivtNo##,routine##ivtNo##);




class KernelEv;
class Event {
public:
 Event (IVTNo ivtNo);
 ~Event ();
 void wait ();
protected: 
 friend class KernelEv;
 void signal(); // can call KernelEv
private:
 int id;
};
#endif 
