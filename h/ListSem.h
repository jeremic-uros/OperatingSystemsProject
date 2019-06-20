
#ifndef LISTSEM_H_
#define LISTSEM_H_

#include "List.h"

class KernelSem;
class ListKernelSem{
    List list;
public:
    ListKernelSem() : list() {}
	KernelSem* operator[] (int id) {
		return (KernelSem*) (list[id]);
	}
	void add(KernelSem* sem,int id) {
        list.add(sem,id);
	}
	KernelSem* remove(int id) {
        return (KernelSem*) list.remove(id);
	}
};



#endif /* LISTSEM_H_ */
