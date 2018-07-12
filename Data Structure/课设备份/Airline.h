#ifndef INC_233_STRUCT_H
#define INC_233_STRUCT_H

#include <string>

using std::string;
using std::fill;

struct Airline {        //记录完整的航班信息

    string id, from, to;    //航班号，起点，终点
    int y1, M1, d1, h1, m1; //起飞时间
    int y2, M2, d2, h2, m2; //降落时间
    double cost, discount;  //票价，折扣
    int AllSeat;            //总的座位数
    int year[7], month[7], day[7], left[7];        //只记录该航班未来7天的余票
    Airline() {}

    Airline & operator = (const Airline &x) {
        id = x.id;
        from = x.from;
        to = x.to;
        h1 = x.h1;
        m1 = x.m1;
        h2 = x.h2;
        m2 = x.m2;
        cost = x.cost;
        discount = x.discount;
        AllSeat = x.AllSeat;
        y1 = x.y1;
        M1 = x.M1;
        d1 = x.d1;
        y2 = x.y2;
        M2 = x.M2;
        d2 = x.d2;
        year[0] = y1;
        month[0] = M1;
        day[0] = d1;
        left[0] = x.left[0];
        for (int i = 1; i < 7; i++) {
            int *nex = NextDay(year[i - 1], month[i - 1], day[i - 1]);
            year[i] = nex[0];
            month[i] = nex[1];
            day[i] = nex[2];
            delete nex;
            left[i] = x.left[i];
        }
        return *this;
    }
    Airline(const Airline &x) {
        *this = x;
    }
    Airline(string id, string from, string to, int y1, int M1, int d1, int h1, int m1, int y2, int M2, int d2, int h2,
            int m2,
            double cost, double discount, int AllSeat) :
            id(id), from(from), to(to), y1(y1), M1(M1), d1(d1), h1(h1), m1(m1), y2(y2), M2(M2), d2(d2), h2(h2), m2(m2),
            cost(cost),
            discount(discount), AllSeat(AllSeat) {
        year[0] = y1;
        month[0] = M1;
        day[0] = d1;
        left[0] = AllSeat;
        for (int i = 1; i < 7; i++) {
            int *nex = NextDay(year[i - 1], month[i - 1], day[i - 1]);
            year[i] = nex[0];
            month[i] = nex[1];
            day[i] = nex[2];
            delete nex;
            left[i] = AllSeat;
        }
        left[0] = AllSeat;
    }
    bool operator==(const Airline &t) const {
        return id == t.id;
    }
    double GetCost() {      //获取最终票价
        return cost * discount;
    }
};

#endif //INC_233_STRUCT_H
