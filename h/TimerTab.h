
#ifndef TIMERTAB_H_
#define TIMERTAB_H_
#include "Timer.h"

class TimerTable {
	struct TableElement {
        Timer* timer;
        TableElement* next;
        TableElement(Timer* t) : timer(t) , next(0) {}
	};
	TableElement *first,*last;
	TableElement* cur;
public:
	TimerTable() : first(0), last(0),cur(0) {}
	~TimerTable();
	void add(Timer* timer);
	void setCurFirst();
    Timer* getTimer();
    void nextTimer();
    void removeCurentTimer();
};


#endif /* TIMERTAB_H_ */
