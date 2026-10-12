#include "DateTime.h"
#include "quickSort.h"
#include <iostream>
#include <locale.h>
#include <vector>
using namespace std;

int main() {
    setlocale(LC_ALL, "Russian");

    // тест основных методов 
    DateTime dt1(21, 12, 2021, 7, 54, 34);
    cout << "Дата: "; dt1.print1(); cout << endl;
    cout << "Формат 2: "; dt1.print2(); cout << endl;
    cout << "Формат 3: "; dt1.print3(); cout << endl;
    cout << "Полный: " << dt1 << endl;
    cout << "День недели: " << dt1.getDayOfWeek() << endl;

    // разница
    DateTime dt2(1, 1, 2022);
    cout << "\nРазница в днях: " << (dt2 - dt1) << endl;

    // добавление
    DateTime dt3 = dt2 + 30;
    cout << "1.01.2022 + 30 дней = " << dt3 << endl;

    // сравнение
    cout << "\ndt1 < dt2? " << (dt1 < dt2) << endl;
    cout << "dt1 == dt2? " << (dt1 == dt2) << endl;

    // Пасха
    DateTime easter = DateTime::calcEaster(2026);
    cout << "\nПасха 2026: " << easter << endl;

    // сортировка (Приложение №1)
    vector<DateTime> dates;
    dates.push_back(DateTime(1, 1, 1995));
    dates.push_back(DateTime(26, 4, 1994));
    dates.push_back(DateTime(5, 12, 1992));
    dates.push_back(DateTime(12, 7, 1994));
    dates.push_back(DateTime(11, 9, 1993));
    dates.push_back(DateTime(21, 7, 1992));
    dates.push_back(DateTime(29, 6, 1997));
    dates.push_back(DateTime(6, 2, 1997));
    dates.push_back(DateTime(31, 10, 1995));
    dates.push_back(DateTime(18, 8, 1993));
    dates.push_back(DateTime(2, 3, 1995));
    dates.push_back(DateTime(12, 8, 1996));
    dates.push_back(DateTime(28, 1, 1997));
    dates.push_back(DateTime(15, 12, 1995));
    dates.push_back(DateTime(9, 6, 1997));
    dates.push_back(DateTime(10, 11, 1993));
    dates.push_back(DateTime(5, 7, 1994));
    dates.push_back(DateTime(6, 6, 1993));
    dates.push_back(DateTime(21, 8, 1997));
    dates.push_back(DateTime(28, 9, 1996));
    dates.push_back(DateTime(14, 1, 1993));
    dates.push_back(DateTime(2, 10, 1992));
    dates.push_back(DateTime(13, 6, 1997));
    dates.push_back(DateTime(18, 8, 1996));
    dates.push_back(DateTime(8, 6, 1994));
    dates.push_back(DateTime(4, 5, 1993));


    quickSort(dates, 0, dates.size() - 1);

    cout << "\nОтсортированные даты:\n";
    for (int i = 0; i < (int)dates.size(); i++)
        cout << dates[i] << endl;

    return 0;
}