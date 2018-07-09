#ifndef INC_233_Queue_H
#define INC_233_Queue_H

#include <iostream>
#include <climits>

#define ERROR INT_MIN

using std::cin;
using std::cout;
using std::endl;
const int maxn = 100;

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



template <class T>
struct Node {        //定义循環隊列類的节点类型

    T data;
    Node *next = nullptr;
    Node() {}
    Node(T x) : data(x) {}
};

template <class T>
class Queue2 {       //定义循環队列类（只設尾指針，不設頭指針）

private:
    Node<T> *back;
public:
    Queue2() {       //構造函數
        back = new Node<T>;
    }
    Queue2 *Create() {       //創建循環隊列

        Queue2 *t = new Queue2;
        t->back->next = t->back;    //創建頭結點
        return t;
    }
    bool empty() {           //判斷隊列是否為空

        return back->next == back;
    }
    void push(T x) {       //入隊操作

        Node<T> *t = new Node<T>(x);
        t->next = back->next;
        back = back->next = t;
    }
    T pop() {              //出隊操作

        if (empty()) return ERROR;    //空隊無法彈出
        Node<T> *t = back->next->next;
        T res = t->data;
        if (t == back) {      //隊列只有一個元素時隊尾指針指向頭結點
            back = back->next;
            back->next = back;
        } else back->next->next = t->next;
        delete t;
        return res;
    }
    T top() {
        if (empty()) return ERROR;  //空隊則報錯
        return back->next->next->data;
    }
    void pop_all() {         //置空队列

        back = back->next;
        Node<T> *t;
        while (back != back->next) {
            t = back->next;
            back->next = t->next;
            delete t;
        }
    }
    void show() {           //輸出完整的隊列

        Node<T> *t = back->next->next;
        while (t != back->next) {
            cout << t->data << ' ';
            t = t->next;
        }
        cout << endl;
    }
};


#endif //INC_233_Queue_H
