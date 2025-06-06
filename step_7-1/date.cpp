//
// Created by kyuu on 2025/6/2.
//
#include"date.h"
#include<iostream>
#include<stdexcept>

using namespace std;

namespace {//namespace 下面的定义只在当前文件中有效
    const int DAYS_BEFORE_MONTH[] = { 0,31,59,90,120,151,181,212,243,273,304,334,365 };
}
Date::Date(int year, int month, int day) {

    if (month < 1 || month>12 ) { throw runtime_error("Invalid date"); }

    this->year = year;
    this->month = month;

    if (day<1 || day>getMaxDay()) { throw runtime_error("Invalid date"); }

    this->day = day;

    int years = year - 1;
    totalDays = years * 365 + years / 4 - years / 100 + years / 400 + DAYS_BEFORE_MONTH[month - 1] + day;
    if (isLeapYear() && month > 2) totalDays++;
}

int Date::getMaxDay() const {
    if (isLeapYear() && month == 2) return 29;
    else return DAYS_BEFORE_MONTH[month] - DAYS_BEFORE_MONTH[month - 1];
}

void Date::show() const {
    cout << getYear() << "-" << getMonth() << "-" << getDay();
}

Date Date::read() {
    int year, month, day;
    char c1, c2;

    cin >> year >> c1 >> month >> c2 >> day;

    if (!cin) throw runtime_error("Failed to read date");

    return Date(year, month, day);
}