//
// Created by kyuu on 2025/6/2.
//

#ifndef BANK_DATE_H
#define BANK_DATE_H

class Date {
private:
    int year;
    int month;
    int day;

    int totalDays;
public:
    Date(int year = 1, int month = 1, int day = 1);

    int getYear()const { return year; }
    int getMonth()const { return month; }
    int getDay()const { return day; }
    int getMaxDay()const;

    bool isLeapYear()const {
        return year % 4 == 0 && year % 100 != 0 || year % 400 == 0;
    }

    void show()const;

    //    int distance(const Date&date)const{
    //        return totalDays-date.totalDays;
    //    }

    // operator:
    // 运算符重载（operator overloading），
    // 是 C++ 的一个非常重要的特性，
    // 用来让你自己定义的类像内置类型一样使用常见运算符
    // （比如 -、<、==、+ 等等）。


        //日期相差多少天
    int operator - (const Date& date)const {
        return totalDays - date.totalDays;
    }
    //日期先后顺序
    bool operator < (const Date& date)const {
        return totalDays < date.totalDays;
    }
    bool operator <= (const Date& date)const {
        return totalDays < date.totalDays;
    }

    //static: 这个函数不需要任何对象就可以调用
    //返回值是Date： 调用这个函数会得到一个新的Date对象
    //使用方法：  Date d = Date::read();   不是d.read不要搞混了！
    static Date read();


};

#endif //BANK_DATE_H