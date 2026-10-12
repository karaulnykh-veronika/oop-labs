#include "DateTime.h"
#include <iomanip>

// конструкторы 

DateTime::DateTime() { // создаем 01.01.1900 00:00:00
    day = 1; month = 1; year = 1900;
    hour = 0; minute = 0; second = 0;
}

DateTime::DateTime(int d, int m, int y) { // создаем дату с временем 00
    day = d; month = m; year = y;
    hour = 0; minute = 0; second = 0;
}

DateTime::DateTime(int d, int m, int y, int h, int min, int s) { // создаем полную дату
    day = d; month = m; year = y;
    hour = h; minute = min; second = s;
}

// проверка

bool DateTime::isLeapYear() const {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

bool DateTime::isValid() const {
    if (year < 1900) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1) return false;

    int daysInMonth[] = { 0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (isLeapYear()) daysInMonth[2] = 29;

    if (day > daysInMonth[month]) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    if (second < 0 || second > 59) return false;

    return true;
}

// юлианская дата

double DateTime::toJulian() const {
    int y = year, m = month;
    if (m <= 2) { y--; m += 12; }

    int A = y / 100;
    int B = 2 - A + A / 4;

    return (int)(365.25 * (y + 4716)) + (int)(30.6001 * (m + 1))
           + day + B - 1524.5
           + (hour + minute / 60.0 + second / 3600.0) / 24.0;
}

// вывод в форматах

void DateTime::print1() const { // 1.01.2001
    cout << day << ".";
    if (month < 10) cout << "0";
    cout << month << "." << year;
}

void DateTime::print2() const { // 1 января 2001
    const char* months[] = { "", "января", "февраля", "марта", "апреля",
        "мая", "июня", "июля", "августа", "сентября",
        "октября", "ноября", "декабря" };
    cout << day << " " << months[month] << " " << year;
}

void DateTime::print3() const { // 01.01.01
    if (day < 10) cout << "0";
    cout << day << ".";
    if (month < 10) cout << "0";
    cout << month << ".";
    int y = year % 100;
    if (y < 10) cout << "0";
    cout << y;
}

void DateTime::print4() const { // yyyy-MM-ddThh:mm:ss
    cout << year << "-";
    if (month < 10) cout << "0";
    cout << month << "-";
    if (day < 10) cout << "0";
    cout << day << "T";
    if (hour < 10) cout << "0";
    cout << hour << ":";
    if (minute < 10) cout << "0";
    cout << minute << ":";
    if (second < 10) cout << "0";
    cout << second;
}

void DateTime::print5() const { // yyyy-MM-dd
    cout << year << "-";
    if (month < 10) cout << "0";
    cout << month << "-";
    if (day < 10) cout << "0";
    cout << day;
}

void DateTime::print6() const { // hh:mm:ss
    if (hour < 10) cout << "0";
    cout << hour << ":";
    if (minute < 10) cout << "0";
    cout << minute << ":";
    if (second < 10) cout << "0";
    cout << second;
}

// день недели (формула Зеллера)

const char* DateTime::getDayOfWeek() const {
    int d = day, m = month, y = year;

    if (m < 3) { m += 12; y--; } // январь-13 февраль-14

    int K = y % 100; // год в веке
    int J = y / 100; // номер века

    int h = (d + 13 * (m + 1) / 5 + K + K / 4 + J / 4 + 5 * J) % 7;

    const char* days[] = { "Суббота", "Воскресенье", "Понедельник",
        "Вторник", "Среда", "Четверг", "Пятница" };

    return days[h];
}

// операторы 

int DateTime::operator -(const DateTime& other) const { // разница в днях
    return (int)(toJulian() - other.toJulian());
}

DateTime DateTime::operator +(int days) const { // добавление  дней через обратное преобразование юлианской даты.
    double jd = toJulian() + days;
    long long jd_int = (long long)jd;

    long long L = jd_int + 68569;
    long long N = 4 * L / 146097;
    L = L - (146097 * N + 3) / 4;
    long long I = 4000 * (L + 1) / 1461001;
    L = L - 1461 * I / 4 + 31;
    long long J = 80 * L / 2447;
    int newDay = (int)(L - 2447 * J / 80);
    L = J / 11;
    int newMonth = (int)(J + 2 - 12 * L);
    int newYear = (int)(100 * (N - 49) + I + L);

    return DateTime(newDay, newMonth, newYear, hour, minute, second);
}

DateTime DateTime::operator -(int days) const {
    return *this + (-days);
}

bool DateTime::operator ==(const DateTime& other) const { // сравнение
    return year == other.year && month == other.month && day == other.day
        && hour == other.hour && minute == other.minute && second == other.second;
}

bool DateTime::operator <(const DateTime& other) const {
    return toJulian() < other.toJulian();
}

bool DateTime::operator >(const DateTime& other) const {
    return toJulian() > other.toJulian();
}

bool DateTime::operator >=(const DateTime& other) const {
    return !(*this < other);
}

bool DateTime::operator <=(const DateTime& other) const {
    return !(*this > other);
}

// ввод-вывод 

istream& operator >>(istream& in, DateTime& dt) {
    int d, m, y;
    char c1, c2;
    in >> d >> c1 >> m >> c2 >> y;

    if (c1 == '-' && c2 == '-') {
        dt.day = d; dt.month = m; dt.year = y;
    } else {
        dt.day = d; dt.month = m; dt.year = y;
    }

    dt.hour = 0; dt.minute = 0; dt.second = 0;
    return in;
}

ostream& operator <<(ostream& out, const DateTime& dt) {
    out << dt.year << "-";
    if (dt.month < 10) out << "0";
    out << dt.month << "-";
    if (dt.day < 10) out << "0";
    out << dt.day << "T";
    if (dt.hour < 10) out << "0";
    out << dt.hour << ":";
    if (dt.minute < 10) out << "0";
    out << dt.minute << ":";
    if (dt.second < 10) out << "0";
    out << dt.second;
    return out;
}

// пасха (алгоритм Гаусса)

DateTime DateTime::calcEaster(int year) {
    int a = year % 19; // остаток дней 
    int b = year % 4;
    int c = year % 7;

    int k = year / 100;
    int p = (13 + 8 * k) / 25;
    int q = k / 4;

    int M = (15 - p + k - q) % 30; // поправки
    int N = (4 + k - q) % 7;

    int d = (19 * a + M) % 30; // день и сдвиг
    int e = (2 * b + 4 * c + 6 * d + N) % 7;

    int easterDay, easterMonth;

    if (d + e <= 9) {
        easterDay = 22 + d + e;
        easterMonth = 3;
    } else {
        easterDay = d + e - 9;
        easterMonth = 4;
    }

    return DateTime(easterDay, easterMonth, year);
}