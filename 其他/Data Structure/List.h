#ifndef INC_233_LIST_H
#define INC_233_LIST_H

#include <iostream>
#include <climits>

#define ERROR INT_MIN
#define List SinList

using std::cin;
using std::cout;
using std::endl;
const int maxn = 100;

template<class T> class SinList;
template<class T> void Mix(SinList<T>*, SinList<T>*);
template<class T> SinList<T> *Union(SinList<T> *, SinList<T> *);

template<class T>
class SeqList {      //順序表的實現

private:
    T *base = new T[maxn];
    int length = 0;
public:
    int Length() {
        return length;
    }
    T get(int i) {          //取值
        if (i < 0 or i >= length) return ERROR;
        return base[i];
    }
    T find(T x) {           //按值查找
        for (int i = 0; i < length; i++)
            if (base[i] == x) return i;
        return ERROR;
    }
    bool insert(T x) {      //末尾插入
        if (length == maxn) return false;
        base[length++] = x;
        return true;
    }
    bool insert(int i, T x) {     //指定位置插入某值
        if (i < 0 or i > length) return false;
        for (int j = length; j > i; j--)
            base[j] = base[j - 1];
        base[i] = x;
        length++;
        return true;
    }
    bool Delete(int i) {        //刪除某位置的值
        if (i < 0 or i >= length) return false;
        for (int j = i; j < length - 1; j++)
            base[j] = base[j + 1];
        length--;
        return true;
    }
    void show() {
        for (int i = 0; i < length; i++)
            cout << base[i] << ' ';
        cout << endl;
    }
};

template<class T>
class SinList {    //單鏈表的實現

private:
    T data;
    static int length;
    SinList *next = nullptr;
public:
    SinList() {}

    SinList(T x) : data(x) {}

    int Length() {
        return length;
    }
    SinList *create() {        //創建單鏈表
        auto *head = new SinList;
        return head;
    }
    SinList *find(SinList *head, T x) { //查找某值
        SinList *p = head->next;
        while (p != nullptr and p->data != x) p = p->next;
        return p;
    }
    T get(SinList *head, int i) {       //獲取指定位置的值
        SinList *p = head->next;
        int ct = 0;
        while (p != nullptr and ct < i) p = p->next, ct++;
        if (p == nullptr or ct > i) return -1;
        return p->data;
    }
    bool Delete(SinList *head, int i) {         //刪除某位置處的值
        SinList *p = head;
        int ct = 0;
        while (p != nullptr and ct < i) p = p->next, ct++;
        if (p == nullptr or p->next == nullptr or ct > i) return false;
        SinList *t = p->next;
        p->next = t->next;
        delete t;
        length--;
        return true;
    }
    bool insert(SinList *head, int i, T x) {    //在指定位置插入值
        SinList *p = head, *t = new SinList(x);
        int ct = 0;
        while (p != nullptr and ct < i) p = p->next, ct++;
        if (p == nullptr or ct > i) {
            return false;
        }
        t->next = p->next;
        p->next = t;
        length++;
        return true;
    }
    void inserthead(SinList *head, T x) {     //頭插法
        SinList *p = new SinList(x);
        p->next = head->next;
        head->next = p;
        length++;
    }
    void insertback(SinList *head, T x) {     //尾插法
        SinList *p = head, *t = new SinList(x);
        while (p->next != nullptr) p = p->next;
        p->next = t;
        length++;
    }
    void show() {
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

template <class T> int SinList<T>::length = 0;

template<class T>
class DbList {   //雙向鏈表的插入刪除功能

private:
    T data;
    DbList *prior = nullptr, *next = nullptr;
public:
    DbList() {}
    DbList(T x) : data(x) {}
    bool insert(DbList *head, int i, T x) { //在指定位置插入數值
        DbList *p = head, *t = new DbList(x);
        int ct = 0;
        while (p != nullptr and ct < i) p = p->next, ct++;
        if (p == nullptr or ct > i) return false;
        t->prior = p->prior;
        t->next = p;
        p->prior->next = t;
        p->prior = t;
        return true;
    }
    bool Delete(DbList *head, int i) {      //刪除某位置處的結點
        DbList *p = head;
        int ct = 0;
        while (p != nullptr and ct < i) p = p->next, ct++;
        if (p == nullptr or ct > i) return false;
        p->prior->next = p->next;
        p->next->prior = p->prior;
        delete p;
        return true;
    }
};

template <class T>
List<T> *Union(List<T> *la, List<T> *lb) {  //把兩個帶頭結點的升序鏈表合併，不開額外空間，去重，新鏈表也升序

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
    c->next = a ? a : b;        //插入剩餘的結點
    lb->next = nullptr;
    delete lb;                  //釋放b的頭結點
    return lc;
}

template <class T>
void Mix(List<T> *la, List<T> *lb) {  //已知ab為兩個升序集合，求其交集並存到a中

    List<T> *a = la->next, *b = lb->next;
    List<T> *p = la, *t;
    while (a != nullptr and b != nullptr) {
        if (a->data == b->data) {   //交集併入到結果表中
            p->next = a;
            p = a;
            a = a->next;
            t = b;
            b = b->next;
            delete t;
        }
        else if (a->data < b->data) {
            t = a;
            a = a->next;
            delete t;
        }
        else {
            t = b;
            b = b->next;
            delete t;
        }
    }
    while (a != nullptr) {      //釋放多餘的結果空間
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


#endif //INC_233_LIST_H
