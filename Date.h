#ifndef DATE_H
#define DATE_H
#include <ctime>
#include <iostream>

class Date {
private:
    int year;
    int month;
    int day;

public:
    Date() {
        std::time_t t = std::time(nullptr);
        std::tm* now = std::localtime(&t);
        year = now->tm_year + 1900;
        month = now->tm_mon + 1;
        day = now->tm_mday;
    }

    Date(int y, int m, int d) {
        year = y;
        month = m;
        day = d;
    }

    bool operator>(const Date& other) const {
        if (year != other.year) return year > other.year;
        if (month != other.month) return month > other.month;
        return day > other.day;
    }

    int operator-(const Date& other) const {
        std::tm a = {};
        a.tm_year = year - 1900;
        a.tm_mon = month - 1;
        a.tm_mday = day;

        std::tm b = {};
        b.tm_year = other.year - 1900;
        b.tm_mon = other.month - 1;
        b.tm_mday = other.day;

        std::time_t time_a = std::mktime(&a);
        std::time_t time_b = std::mktime(&b);

        return static_cast<int>(std::difftime(time_a, time_b) / 86400);
    }

    Date operator+(int days) const {
        std::tm temp = {};
        temp.tm_year = year - 1900;
        temp.tm_mon = month - 1;
        temp.tm_mday = day;

        std::time_t time = std::mktime(&temp);
        time += static_cast<long long>(days) * 24 * 3600;

        std::tm* new_time = std::localtime(&time);
        return Date(new_time->tm_year + 1900, new_time->tm_mon + 1, new_time->tm_mday);
    }

    void show() const {
        std::cout << year << "-" << month << "-" << day;
    }
};
#endif