#ifndef INC_233_StackQueue_H
#define INC_233_StackQueue_H

#include <iostream>
#include <climits>

#define ERROR INT_MIN

using std::cin;
using std::cout;
using std::endl;
const int maxn = 100;

template<class T>
class Stack1 { //順序棧

private:
    T *base, *top;
    int Stacksize;
public:
    Stack1 *create() {  //棧的初始化
        Stack1 *s = new Stack1;
        s->top = s->base = new T[maxn];
        s->Stacksize = maxn;
        return s;
    }
    int Size() {       //棧的元素個數
        return int(top - base);
    }
    bool push(T x) {   //入棧
        if (top - base == Stacksize) return false;
        *top++ = x;
        return true;
    }
    bool Empty() {      //判斷棧是否為空
        return top == base;
    }
    T pop() {            //出棧
        if (Empty()) return ERROR;
        return *--top;
    }
    T Top() {            //返回棧頂
        return *(top - 1);
    }
};

/************************/
template <class T>
struct Stack {      //鏈棧(不帶頭節點)
    T data;
    Stack *next = nullptr;
    Stack() {}
    Stack(T x) : data(x) {}
};
template <class T>
Stack<T>* push(Stack<T> *s, T x) {    //入棧（返回新棧）
    Stack<T> *p = new Stack<T>(x);
    p->next = s;
    return p;
}
template <class T>
Stack<T>* pop(Stack<T> *s) {          //出棧（返回新棧）
    if (s == nullptr) return nullptr;
    Stack<T> *p = s;
    delete p;
    return s->next;
}
template <class T>
T Top(Stack<T> *s) {                  //返回棧頂
    if (s != nullptr) return s->data;
    return ERROR;
}
/************************/

template <class T>
class Queue1 {         //循環隊列的基本操作

private:
    T *base;
    int front, rear;
public:
    Queue1 *create() {  //隊列的初始化
        Queue1 *que = new Queue1;
        que->base = new T[maxn];
        que->front = que->rear = 0;
        return que;
    }
    bool Empty() {      //判斷是否隊空
        return front == rear;
    }
    int Length() {      //返回隊列的長度
        return (rear - front + maxn) % maxn;
    }
    T Front() {         //返回隊首
        return front == rear ? ERROR : base[front];
    }
    bool push(T x) {   //入隊
        if ((rear + 1) % maxn == front) return false;
        base[rear] = x;
        rear = (rear + 1) % maxn;
        return true;
    }
    T pop(Queue1 *t) {              //出隊
        if (t->front == t->rear) return ERROR;
        T res = t->base[t->front];
        t->front = (t->front + 1) % maxn;
        return res;
    }
};

template <class T>
class Queue {  //鏈隊(帶頭節點)

private:
    struct node {       //鏈隊的結點類型
        T data;
        node *next = nullptr;
        node() {}
        node(T x) : data(x) {}
    } *front, *rear;

public:
    Queue *create() {   //創建鏈隊
        Queue *que = new Queue;
        que->rear = que->front = new node;
        que->front->next = nullptr;
        return que;
    }
    bool Empty() {      //判斷是否隊空
        return front == rear;
    }
    void push(int x) {  //入隊
        node *p = new node(x);
        rear->next = p;
        rear = p;
    }
    T pop() {           //出隊
        if (front == rear) return ERROR;
        node *p = front->next;
        T res = p->data;
        front->next = p->next;
        if (rear == p) rear = front; //首元節點出隊時防止隊尾指針懸空
        delete p;
        return res;
    }
    T Front() {       //取出隊頭元素
        if (Empty()) return ERROR;
        return front->next->data;
    }
};


#endif //INC_233_StackQueue_H

