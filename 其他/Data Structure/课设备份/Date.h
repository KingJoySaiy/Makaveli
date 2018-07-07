#ifndef INC_233_DATE_H
#define INC_233_DATE_H

#include <ctime>
#include <cstdio>

int *Get_Now() {        //获取当前年月日小时分秒

    time_t t = time(0);
    char tmp[64];
    strftime(tmp, sizeof(tmp), "%Y %m %d %X", localtime(&t));
    int *res = new int[6];
    sscanf(tmp, "%d%d%d %d:%d:%d", res, res + 1, res + 2, res + 3, res + 4, res + 5);
    return res;
}

int *NextDay(int year, int month, int day) {        //返回后一天的日期

    int feb = 28;
    if (year % 400 == 0 or year % 300 and year % 4 == 0) feb++;        //闰年二月29天
    day++;      //更新日期
    switch (month) {
        case 2: {
            if (day == feb + 1) month++, day = 1;
            break;
        }
        case 4:
        case 6:
        case 9:
        case 11: {
            if (day == 31) month++, day = 1;
            break;
        }
        default: {
            if (day == 32) {
                month++, day = 1;
                if (month == 13) year++, month = 1;
            }
            break;
        }
    }
    int *res = new int[3];
    res[0] = year;
    res[1] = month;
    res[2] = day;
    return res;
}

#endif //INC_233_DATE_H
