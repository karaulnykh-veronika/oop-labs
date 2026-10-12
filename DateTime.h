#ifndef DATETIME_H
#define DATETIME_H

#include <iostream>
using namespace std;

class DateTime {
    int year, month, day;
    int hour, minute, second;

public:
    // конструкторы
    DateTime();
    DateTime(int d, int m, int y);
    DateTime(int d, int m, int y, int h, int min, int s);

    // проверка корректности
    bool isValid() const; // даты
    bool isLeapYear() const; // високосный ли год

    // юлианская дата (для разницы и сравнения)
    double toJulian() const;

    // вывод в разных форматах
    void print1() const;   // 1.01.2001
    void print2() const;   // 1 января 2001
    void print3() const;   // 01.01.01
    void print4() const;   // yyyy-MM-ddThh:mm:ss
    void print5() const;   // yyyy-MM-dd
    void print6() const;   // hh:mm:ss

    // день недели
    const char* getDayOfWeek() const;

    // операторы
    DateTime operator +(int days) const;
    DateTime operator -(int days) const;
    int operator -(const DateTime& other) const;   // разница в днях

    bool operator ==(const DateTime& other) const;
    bool operator <(const DateTime& other) const;
    bool operator >(const DateTime& other) const;
    bool operator >=(const DateTime& other) const;
    bool operator <=(const DateTime& other) const;

    // ввод-вывод
    friend istream& operator >>(istream& in, DateTime& dt);
    friend ostream& operator <<(ostream& out, const DateTime& dt);

    // пасха (католическая)
    static DateTime calcEaster(int year);
};

#endif