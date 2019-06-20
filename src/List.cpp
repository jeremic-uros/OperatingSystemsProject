
#include "List.h"
#include <IOSTREAM.H>
extern void stopProgram();
 void List::add(void* ele,int id) {
       Elem* newElem = new Elem(ele,id);
       if(!newElem) {
	      cout << "\nNOT ENOUGH MEMORY...";
	      stopProgram();
       }
       if(first == 0) first = last = newElem;
       else {
    	   last->next = newElem;
    	   last = newElem;
       }
   }


 void* List::remove(int id) {
	Elem* cur = first,*prev = 0;
	while(!cur && cur->id != id){
		prev = cur;
        cur = cur->next;
	}
	void* ret = 0;
	if(cur){
	   void* ret = cur->element;
       if(cur == first) {
          first = first->next;
          if(!first) last = 0;
       }
       else if(cur == last){
          prev->next = 0;
          last = prev;
       }
       else {
          prev->next = cur->next;
       }
       delete cur;
	}
	return 0;
}

void* List::operator [](int id) {
       Elem* cur = first;
       while(cur && cur->id != id)
    	   cur = cur->next;
       if(cur) return cur->element;
       else return 0;
  }

