
#ifndef IVTENTRY_H_
#define IVTENTRY_H_
#include <dos.h>
#include "Queue.h"
typedef void interrupt (*interruptRoutine) (...);
extern InterruptQueue intrQueue;
class Event;
class IVTEntry {
public:
	IVTEntry(unsigned char ivtNo,interruptRoutine newRt);
	~IVTEntry();
	static IVTEntry* getEntry(unsigned char ivtNo) { return entryTable[ivtNo]; }
	void setNewRoutine(interruptRoutine newRt) { newRoutine = newRt; }
	void setInterruptVector();
	void restoreInterruptVector();
	Event* getEvent() { return event; }
	void setEvent(Event* eve) { event = eve; }
	void signalCallWrapper();
	void callOldRoutine() { oldRoutine();}
	void addToInterruptQueue() {
         intrQueue.put((interruptRt)newRoutine);
	}
private:
	static IVTEntry** entryTable;
	unsigned char entryNumber;
	interruptRoutine oldRoutine,newRoutine;
	Event* event;
};


#endif /* IVTENTRY_H_ */
