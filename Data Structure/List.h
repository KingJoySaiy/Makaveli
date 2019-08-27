#ifndef INC_233_LIST_H
#define INC_233_LIST_H

#include <iostream>

#define ERROR 0
#define OK true
#define List SinList

using std::cin;
using std::cout;
using std::endl;

/********* Sequence List ********/
#define initSize 1000
#define incrementSize 100

template <class T>
class seqList {
private:
	T* base;
	int length, listSize;
public:
	seqList() {	//constructor
		base = new T[initSize];
		length = 0;
		listSize = initSize;
	}
	int Length() {	//list length
		return length;
	}
	T get(int i) {	// get value
		if (i < 0 or i >= length) return ERROR;
		return base[i];
	}
	T find(T x) {	// find location via value x
		for (int i = 0; i < length; i++) {
			if (base[i] == x) return i;
		}
		return ERROR;
	}
	bool checkLength() {	//realloc momory when list is full
		if (length >= listSize) {
			base = (T*)realloc(base, (listSize + incrementSize) * sizeof(T));
			if (!base) return ERROR;
			listSize += incrementSize;
		}
		return OK;
	}
	bool insert(T x) {	// insert at the end
		if (!checkLength()) return ERROR;
		base[length++] = x;
		return OK;
	}
	bool insert(int i, T x) {	// insert x at i-th location
		if (i < 0 or i > length or !checkLength()) return ERROR;
		for (int j = length; j > i; j--) {
			base[j] = base[j - 1];
		}
		base[i] = x;
		length++;
		return OK;
	}
	bool Delete(int i) {	// delete at i
		if (i < 0 or i >= length)
			return ERROR;
		for (int j = i; j < length - 1; j++)
			base[j] = base[j + 1];
		length--;
		return OK;
	}
	void show() {	//print whole list
		for (int i = 0; i < length; i++)
			cout << base[i] << ' ';
		cout << endl;
	}
};

/******** List with single next-pointer ********/
template<class T> class SinList;
template<class T> void Mix(SinList<T>*, SinList<T>*);
template<class T> SinList<T> *Union(SinList<T> *, SinList<T> *);

template<class T>
class SinList {
private:
	T data;
	int length;
	SinList *next;
public:
	SinList() {
		length = 0;
		next = nullptr;
	}
	SinList(T x) : data(x) {}
	int Length() {
		return length;
	}
	int find(T x) {	//find value x, return location
		SinList *p = this->next;
		int id = 1;
		while (p != nullptr) {
			if (p->data == x) return id;
			p = p->next;
			id++;
		}
		return ERROR;
	}
	T get(SinList *head, int i) {	//get value at i
		SinList *p = head->next;
		int ct = 1;
		while (p != nullptr and ct < i) p = p->next, ct++;
		if (p == nullptr or ct > i) return ERROR;
		return p->data;
	}
	bool Delete(SinList *head, int i) {         //delete at i
		SinList *p = head;
		int ct = 1;
		while (p != nullptr and ct < i) p = p->next, ct++;
		if (p == nullptr or p->next == nullptr or ct > i) return ERROR;
		SinList *t = p->next;
		p->next = t->next;
		delete t;
		length--;
		return OK;
	}
	bool insert(int i, T x) {    //insert at i
		if (i < 1 or i > length) return ERROR;
		SinList *p = this, *t = new SinList(x);
		int ct = 1;
		while (p != nullptr and ct < i) p = p->next, ct++;
		if (p == nullptr or ct > i) {
			return ERROR;
		}
		t->next = p->next;
		p->next = t;
		length++;
		return OK;
	}
	void insertHead(SinList *head, T x) {     //insert at head
		SinList *p = new SinList(x);
		p->next = head->next;
		head->next = p;
		length++;
	}
	void insertBack(SinList *head, T x) {     //insert at back
		SinList *p = head, *t = new SinList(x);
		while (p->next != nullptr) p = p->next;
		p->next = t;
		length++;
	}
	void show() {	//print all data
		SinList *t = this->next;
		while (t != nullptr) {
			cout << t->data << ' ';
			t = t->next;
		}
		cout << endl;
	}
	friend SinList<T>* Union<>(SinList<T> *, SinList<T> *);
	friend void Mix<>(SinList<T>*, SinList<T>*);
};

/******** Other Operations of Single List ********/
template <class T>
List<T> *Union(List<T> *la, List<T> *lb) {  //union 2 ascending lists & remove duplicates
//(never alloc other momory, new list also ascending)
	List<T> *a = la->next, *b = lb->next;
	List<T> *lc = la, *c = la, *tmp;
	while (a != nullptr and b != nullptr) {
		if (a->data < b->data) {
			c->next = a;
			c = a;
			a = a->next;
		} else if (a->data > b->data) {
			c->next = b;
			c = b;
			b = b->next;
		} else {
			c->next = a;
			c = a;
			a = a->next;
			tmp = b;
			b = b->next;
			delete tmp;
		}
	}
	c->next = a ? a : b;        //insert remaining node
	lb->next = nullptr;
	delete lb;                  //delete head node of list_b
	return lc;
}

template <class T>
void Intersect(List<T> *la, List<T> *lb) {  //intersect 2 ascending list(list_a & list_b) to list_a

	List<T> *a = la->next, *b = lb->next;
	List<T> *p = la, *t;
	while (a != nullptr and b != nullptr) {
		if (a->data == b->data) {   //add intersection to result
			p->next = a;
			p = a;
			a = a->next;
			t = b;
			b = b->next;
			delete t;
		} else if (a->data < b->data) {
			t = a;
			a = a->next;
			delete t;
		} else {
			t = b;
			b = b->next;
			delete t;
		}
	}
	while (a != nullptr) {      //delete useless memory
		t = a;
		a = a->next;
		delete t;
	}
	while (b != nullptr) {
		t = b;
		b = b->next;
		delete t;
	}
	p->next = lb->next = nullptr;
	delete lb;
}

/******** List with double pointer ********/
template<class T> class DbList;
template<class T> bool exchange(DbList<T>*);

template<class T>
class DbList { 
private:
	T data;
	DbList *prior, *next;
public:
	DbList() {
		prior = next = nullptr;
	}
	DbList(T x) : data(x) {}
	void insertHead(DbList *head, T x) {     //insert at head
		auto *p = new DbList(x);
		p->next = head->next;
		p->prior = head;
		if(head->next != nullptr) head->next->prior = p;    //pay attention to the 1st insertion
		head->next = p;
	}
	void insertBack(DbList *head, T x) {     //insert at back
		DbList *p = head, *t = new DbList(x);
		while (p->next != nullptr) p = p->next;
		p->next = t;
		t->prior = p;
	}
	bool Delete(int i) {      //delete at i
		DbList *p = this;
		int ct = 0;
		while (p != nullptr and ct < i) p = p->next, ct++;
		if (p == nullptr or ct > i) return ERROR;
		p->prior->next = p->next;
		p->next->prior = p->prior;
		delete p;
		return OK;
	}
	int find(T x) {	//find value x, return location
		DbList *p = this->next;
		int id = 1;
		while (p != nullptr) {
			if (p->data == x) return id;
			p = p->next;
			id++;
		}
		return ERROR;
	}
	void show() {
		DbList *t = this->next;
		while (t != nullptr) {
			cout << t->data << ' ';
			t = t->next;
		}
		cout << endl;
	}
	friend bool exchange<>(DbList<T>*);
};

/******** Other Operations of Double List ********/
template <class T>
bool exchange(DbList<T> *p) {       //exchange p & its prior node

	if (p->prior == nullptr) return ERROR;         //list empty, only remains head node
	if (p->prior->prior == nullptr) return ERROR;  //1st node cannot exchange with head node
	DbList<T> *t = p->prior;
	if (p->next != nullptr) p->next->prior = t;     //pay attentionn to the tail node
	t->prior->next = p;
	p->prior = t->prior;
	t->next = p->next;
	p->next = t;
	t->prior = p;
	return OK;
}

#endif //INC_233_LIST_H
