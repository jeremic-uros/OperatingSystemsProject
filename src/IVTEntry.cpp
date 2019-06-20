
#include "IVTEntry.h"
#include "KernelEv.h"

IVTEntry** IVTEntry::entryTable = new IVTEntry*[256];



IVTEntry::IVTEntry(unsigned char ivtNo,interruptRoutine newRt)  : entryNumber(ivtNo),oldRoutine(0),newRoutine(newRt),event(0) {
    IVTEntry::entryTable[ivtNo] = this;
    asm cli
	oldRoutine = getvect(ivtNo);
    asm sti
}

IVTEntry::~IVTEntry() {
   IVTEntry::entryTable[entryNumber] = 0;
   asm cli
   setvect(entryNumber,oldRoutine);
   asm sti
}


void IVTEntry::setInterruptVector() {
	asm cli
    setvect(entryNumber,newRoutine);
	asm sti
}
void IVTEntry::restoreInterruptVector(){
	asm cli
	setvect(entryNumber,oldRoutine);
	asm sti
}

void IVTEntry::signalCallWrapper() {
	 KernelEv::signalEvent(event);
}
