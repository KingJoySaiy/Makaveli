#include <iostream>
#include <windows.h>
#include "HashMap.h"
#include "Graph.h"

using namespace std;

Map map;            //id -> (airline, left[7])
Table table;        //(from, to) -> id

int main() {

    Airline airline = Airline("iidd", "北京", "上海", 12, 0, 13, 0, 99, 1, 50);

    table.Insert(airline.id, airline.from, airline.to);
    map.AddAirline(airline);
    Airline *search = map.FindAirline("iidd");

    cout << search->from << " " << search->to << endl;
    for (int i = 0; i < 7; i++) {
        cout << search->year[i] << ' ' << search->month[i] << ' '
             << search->day[i] << ' ' << search->left[i] << endl;
    }
    cout << map.DeleteAirline("iidd") << endl;
    cout << map.DeleteAirline("iidd") << endl;


    cout << table.FindId("北京", "上海") << endl;



//	int *t = Get_Now();
//	Sleep(1000 * (24 * 60 * 60 - 3600 * t[3] - 60 * t[4] - t[5]));
//	delete t;
//	p.NewDay();
//	while(1) {
//		Sleep(24 * 60 * 60 * 1000);
//		p.NewDay();
//	}

//    system("pause");

    return 0;
}
