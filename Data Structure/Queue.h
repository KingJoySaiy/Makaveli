#ifndef INC_233_QUEUE_H
#define INC_233_QUEUE_H

#include <iostream>
#include <climits>

#define ERROR INT_MIN
#define OK true

const int maxn = 100;

template <class T>
class CircularQueue {         //Circular Queue

private:
    T *base;
    int front, rear;
public:
    CircularQueue() {	//constructor
    	base = new T[maxn];
    	front = rear = 0;
	}
    bool Empty() {      //check whether empty
        return front == rear;
    }
    int Length() {
        return (rear - front + maxn) % maxn;
    }
    T Front() {         //front of queue
        return front == rear ? ERROR : base[front];
    }
    bool push(T x) {   //push into queue
        if ((rear + 1) % maxn == front) return false;
        base[rear] = x;
        rear = (rear + 1) % maxn;
        return OK;
    }
    T pop(CircularQueue *t) {              //pop out of queue
        if (t->front == t->rear) return ERROR;
        T res = t->base[t->front];
        t->front = (t->front + 1) % maxn;
        return res;
    }
};

template <class T>
class LinkedQueue {  //Linked Queue (with head node)

private:
    struct node {       //node of queue
        T data;
        node *next = nullptr;
        node() {}
        node(T x) : data(x) {}
    } *front, *rear;

public:
	LinkedQueue() {	//constructor
		rear = front = new node();
		rear->next = nullptr;
	}

    bool Empty() {      //check whether empty	
        return front == rear;
    }
    bool push(T x) {  //push into queue
        node *p = new node(x);
        rear->next = p;
        rear = p;
    	return OK;
	}
    T pop() {           //pop out of queue
        if (front == rear) return ERROR;
        node *p = front->next;
        T res = p->data;
        front->next = p->next;
        if (rear == p) rear = front; //prevent back pointer from hanging on when 1st node poped out
        delete p;
        return res;
    }
    T Front() {       //front of queue
        if (Empty()) return ERROR;
        return front->next->data;
    }
};

#endif //INC_233_QUEUE_H
