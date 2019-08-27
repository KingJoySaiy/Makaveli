#ifndef INC_233_Stack_H
#define INC_233_Stack_H

#include <iostream>

#define ERROR false
#define OK true

using std::cin;
using std::cout;
using std::endl;

/******** Sqeuence Stack ********/
#define initSize 1000
#define addSize 100		//add if stack full

template<class T>
class seqStack {
private:
	T *base, *top;
	int stackSize;
public:
	seqStack() {		//constructor
		top = base = new T[initSize];
		stackSize = initSize;
	}
	int Size() {       //element count
		return int(top - base);
	}
	bool push(T x) {   //push x
		if (top - base == stackSize) {
			base = (T*)realloc(base, (stackSize + addSize) * sizeof(seqStack));
			if (!base) return ERROR;	//alloc memory failed
		}
		*(top++) = x;
		return true;
	}
	bool Empty() {      //check whether empty
		return top == base;
	}
	T pop() {            //pop the top, return data
		if (Empty()) return ERROR;
		return *--top;
	}
	T Top() {            //get top
		return *(top - 1);
	}
};
#undef initSize
#undef addSize

/******** List Stack ********/
template <class T>
class listStack {	//with head node, 1st data is meaningless
private:
	T data;
	listStack *next;
public:
	listStack() {
		next = nullptr;
	}
	listStack(T x) : data(x) {}
	bool Empty() {	//whether empty
		return next == nullptr;
	}
	int Size() {	//element count
		listStack<T> *t = this;
		int ct = 0;
		while (t->next != nullptr) {
			t = t->next;
			ct++;
		}
		return ct;
	}
	bool push(T x) {	//push x
		listStack<T> *node = new listStack<T>(x);
		node->next = next;
		next = node;
		return OK;
	}
	int pop() {	//pop the top, return data
		if (Empty()) return ERROR;
		listStack<T> *t = next;
		int x = t->data;
		next = t->next;
		delete t;
		return x;
	}
	T top() {	//get top
		if (Empty()) return ERROR;
		return next->data;
	}
};

#endif //INC_233_Stack_H
