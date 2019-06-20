
#ifndef LISTEVE_H_
#define LISTEVE_H_
#include "List.h"

class KernelEv;
class ListKernelEv {
	    List list;
public:
    ListKernelEv() : list() {}
	KernelEv* operator[] (int id) {
		return (KernelEv*) (list[id]);
	}
	void add(KernelEv* eve,int id) {
        list.add(eve,id);
	}
	KernelEv* remove(int id) {
        return (KernelEv*) list.remove(id);
	}
};


#endif /* LISTEVE_H_ */
