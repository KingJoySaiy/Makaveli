#ifndef INC_233_HASHMAP_H
#define INC_233_HASHMAP_H

#include "Struct.h"

const int mod = 100;                //设置哈希表模为100

struct List {                       //单链表存储哈希表的每条链

    Airline airline;
    List *next = nullptr;
    List(){}
    List(Airline x) :airline(x) {}
    List *Create_List() {          //创建单链表，返回头节点
        List *head = new List();
        return head;
    }
    List* Insert(Airline x) {            //插入新节点(头插法)
        List *t = new List(x);
        t->next = this->next;
        this->next = t;
        return this;
    }
    bool Delete(List *head, string id) {        //按航班号删除已有的航班信息

        List *t = head->next, *pre = head;
        while (t != nullptr) {
            if(t->airline.id == id) {
                pre->next = t->next;
                delete t;
                return true;
            }
            pre = t;
            t = t->next;
        }
        return false;
    }
    Airline* Find(List *head, string id) {	//查询链表中是否有某航班, 若有则返回该航班信息
        List *t = head->next;
        while (t != nullptr) {
            if (t->airline.id == id) return &(t->airline);
            t = t->next;
        }
        return nullptr;
    }
};

struct Map {        //哈希表记录每个航班的信息 key -> id, value -> others（拉链法实现）

    List *a[mod];
    Map () {
        for(int i = 0; i < mod; i++)
            a[i] = List().Create_List();
    }
    void AddAirline(Airline airline) {     //插入新的航班信息(root)

        int ct = 0;
        for(auto &p : airline.id) ct += int(p);
        a[ct % mod] = a[ct % mod]->Insert(airline);       //索引取值：id的ASCII码总和对mod取模
    }
    bool DeleteAirline(string id) {         //根据航班号删除已有的航班信息(root)

        int ct = 0;
        for(auto &p : id) ct += int(p);
        return a[ct % mod]->Delete(a[ct % mod], id);
    }
    Airline* FindAirline(string id) {       //找出哈希表中有无某航班，若有则返回该航班信息(root, user)

        int ct = 0;
        Airline *res;
        for(auto &p : id) ct += int(p);
        if((res = a[ct % mod]->Find(a[ct % mod], id)) != nullptr) return res;
        return nullptr;
    }
};


#endif //INC_233_HASHMAP_H

