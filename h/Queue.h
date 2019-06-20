
#ifndef QUEUE_H_
#define QUEUE_H_
#include "lock.h"
#include <iostream.h>
typedef void interrupt (*interruptRt) ();
extern void stopProgram();

class InterruptQueue {
      struct Elem{
          interruptRt toDo;
          Elem* next;
          Elem(interruptRt Rt) : toDo(Rt),next(0) {}
      };
      Elem* first,*last;
      int count;
public:
      InterruptQueue() : first(0),last(0),count(0){}
      void put(interruptRt Rt){
    	  lock
    	  Elem* newElem = new Elem(Rt);
    	  if(!newElem){
    		   cout << "\nNOT ENOUGH MEMORY...";
    		   stopProgram();
    	  }
    	  if(first == 0) { first = last = newElem;}
    	  else{
    		  last->next = newElem;
    		  last = newElem;
    	  }
    	  count++;
    	  unlock
      }
      interruptRt get() {
    	  lock
          interruptRt ret = first->toDo;
    	  Elem* toDelete = first;
          first = first->next;
          if(!first) last = 0;
          delete toDelete;
          count--;
          unlock
          return ret;
      }
      int isEmpty() { return ((count == 0)?1:0); }
};




#endif /* QUEUE_H_ */
