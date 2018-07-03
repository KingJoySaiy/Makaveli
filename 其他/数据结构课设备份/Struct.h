#ifndef INC_233_STRUCT_H
#define INC_233_STRUCT_H

#include <string>

using std::string;
using std::fill;

//管理员：登陆 -> 录入/修改信息/User的查询
//User：注册/登入 -> 查询机票/订票/退票/改签

//输入航班号，查询后7天的航班信息，余票
//输入起点终点，查询后7天航班信息（有重边）

#include <ctime>
#include <cstdio>

int* Get_Now() {		//获取当前年月日小时分秒

    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y %m %d %X", localtime(&t));
    int *res = new int[6];
    sscanf(tmp, "%d%d%d %d:%d:%d", res, res + 1, res + 2, res + 3, res + 4, res + 5);
    return res;
}
int* NextDay(int year, int month, int day) {		//返回后一天的日期
    int feb = 28;
    if(year % 400 == 0 or year % 300 and year % 4 == 0) feb++;		//闰年二月29天
    day++;
    switch(month) {
        case 2: {
            if(day == feb + 1) month++, day = 1;
            break;
        }
        case 4: case 6: case 9: case 11:{
            if(day == 31) month++, day = 1;
            break;
        }
        default: {
            if(day == 32) {
                month++, day = 1;
                if(month == 13) year++, month = 1;
            }
            break;
        }
    }
    int *res = new int[6];
    res[0] = year; res[1] = month; res[2] = day;
    return res;
}
struct Airline {        //记录完整的航班信息

    string id, from, to;    //航班号，起点，终点
    int h1, m1;             //起飞时间
    int h2, m2;             //降落时间
    double cost, discount;  //票价，折扣
    int AllSeat;            //总的座位数
    int year[7], month[7], day[7], left[7];		//只记录该航班未来7天的余票

    Airline() {}
    Airline& operator = (const Airline &x) {
        id = x.id; from = x.from; to = x.to; h1 = x.h1; m1 = x.m1;
        h2 = x.h2; m2 = x.m2; cost = x.cost; discount = x.discount; AllSeat = x.AllSeat;
        for (int i = 0; i < 7; i++) {
            year[i] = x.year[i];
            month[i] = x.month[i];
            day[i] = x.day[i];
            left[i] = x.left[i];
        }
        return *this;
    }
    Airline(const Airline &x) {
        *this = x;
    }
    Airline(string id, string from, string to, int h1, int m1, int h2, int m2,
            double cost, double discount, int AllSeat) :
            id(id), from(from), to(to), h1(h1), m1(m1), h2(h2), m2(m2), cost(cost),
            discount(discount), AllSeat(AllSeat) {

        int *nex = Get_Now();
        year[0] = nex[0]; month[0] = nex[1]; day[0] = nex[2];
        delete nex;
        for(int i = 1; i < 7; i++) {
            nex = NextDay(year[i - 1], month[i - 1], day[i - 1]);
            year[i] = nex[0]; month[i] = nex[1]; day[i] = nex[2];
            delete nex;
            left[i] = AllSeat;
        }
        left[0] = AllSeat;
    }
    bool operator == (const Airline &t) const {
        return id == t.id;
    }
//    void NewDay() {         //新的一天，更新余票记录信息
//        for(int i = 0; i < 6; i++) {
//            year[i] = year[i + 1];
//            month[i] = month[i + 1];
//            day[i] = day[i + 1];
//            left[i] = left[i + 1];
//        }
//        int *nex = NextDay(year[4], month[4], day[4]);
//        year[6] = nex[0]; month[6] = nex[1]; day[6] = nex[2];
//        delete nex;
//        left[6] = AllSeat;
//    }
    double GetCost() {      //获取最终票价

        return cost * discount;
    }
};

#endif //INC_233_STRUCT_H

