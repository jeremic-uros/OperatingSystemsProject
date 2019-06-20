
#ifndef LIST_H_
#define LIST_H_


class List{
    struct Elem {
    	void* element;
    	int id;
    	Elem* next;
    	Elem(void* ele,int idd) : element(ele),next(0),id(idd) {}
    };
    Elem* first,*last;
  public:
    List() : first(0),last(0) {}
    void* operator[] (int id);
    void add(void* ele,int id);
    void* remove(int id);
};




#endif /* LIST_H_ */
