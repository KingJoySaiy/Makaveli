#ifndef INC_233_GRAPH_H
#define INC_233_GRAPH_H

#include "Struct.h"
#include "Hashmap.h"

const int maxn = 100;       //设置最多100个城市
string City[maxn];          //记录所有城市名

struct pair {

    int x, y;
};
struct Table {              //邻接矩阵的基本实现（由于查询次数较多，插入删除次数较少，故邻接表更适合）

    string matrix[maxn][maxn];      //根据起点索引和终点索引记录航班号
    int CityNum;
    Table() {

        for (int i = 0; i < maxn; i++) {        //初始化所有航班号为空串
            fill (matrix[i] , matrix[i] + maxn, "");
        }
        CityNum = 0;
    }
    pair GetIndex(const string &from, const string &to) {   //根据城市名获取其索引，找不到返回-1
        int x = -1, y = -1;
        for (int i = 0; i < CityNum; i++) { //遍历查找城市名是否没记录过
            if (City[i] == from) x = i;
            if (City[i] == to) y = i;
        }
        return pair{x, y};
    }
    void Insert(const string &id, const string &from, const string &to) {   //插入航班记录

        pair t = GetIndex(from, to);
        if (t.x == -1) {      //若城市未被记录过，则记录进去
            t.x = CityNum;
            City[CityNum++] = from;
        }
        if (t.y == -1) {
            t.y = CityNum;
            City[CityNum++] = to;
        }
        matrix[t.x][t.y] = id;
    }
    bool Delete(const string &from, const string &to) {     //删除某航班记录

        pair t = GetIndex(from, to);
        if (t.x == -1 or t.y == -1) return false;
        matrix[t.x][t.y].clear();       //能找到，则清空字符串
        return true;
    }
    string FindId(const string &from, const string &to) { //根据起点终点查询航班号，找不到返回空串

        pair t = GetIndex(from, to);
        return (t.x == -1 or t.y == -1) ? "" : matrix[t.x][t.y];
    }
};

#endif //INC_233_GRAPH_H
