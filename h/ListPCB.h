
#ifndef LISTPCB_H_
#define LISTPCB_H_
#include "List.h"

class PCB;
class ListPCB{
    List list;
public:
    ListPCB() : list() {}
	PCB* operator[] (int id) {
		return (PCB*) (list[id]);
	}
	void add(PCB* pcb,int id) {
        list.add(pcb,id);
	}
	PCB* remove(int id) {
        return (PCB*) list.remove(id);
	}
};

#endif /* LISTPCB_H_ */
