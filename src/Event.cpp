
#include "Event.h"
#include "Params.h"
#include <dos.h>

unsigned g1,g2;

Event::Event(IVTNo ivtNo) : id(0){
    Params_createEvent* params = new Params_createEvent();
    params->ivtNo = ivtNo;
    params->event = this;
    g1 = FP_OFF(params);
    g2 = FP_SEG(params);
	asm{
		mov bx,13
		mov dx,g1
		mov es,g2
		int 61h
	}
}
Event::~Event() {
	int EventID = id;
	asm{
		mov bx,14
		mov dx,EventID
		int 61h
	}
}
void Event::wait() {
	int EventID = id;
	asm{
		mov bx,15
		mov dx,EventID
		int 61h
	}
}
void Event::signal() {
	int EventID = id;
	asm{
		mov bx,16
		mov dx,EventID
		int 61h
	}
}

