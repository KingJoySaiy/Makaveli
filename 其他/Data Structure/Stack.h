#ifndef INC_233_Stack_H
#define INC_233_Stack_H

#include <iostream>
#include <climits>

#define ERROR INT_MIN

using std::cin;
using std::cout;
using std::endl;
const int maxn = 100;

template<class T>
class Stack1 {      //順序棧的實現

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

#endif //INC_233_Stack_H
