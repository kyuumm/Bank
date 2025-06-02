//
// Created by kyuu on 2025/5/30.
//

#ifndef BANK_DATE_H
#define BANK_DATE_H

class Date{
private:
    int year;
    int month;
    int day;
    int totalDays;

public:
    Date(int year,int month,int day);
    int getYear()const{return year;}
    int getMonth()const{return month;}
    int getDay()const{return day;}
    int getMaxDay()const;

    bool isLeapYear()const{
        return year%4==0 && year%100!=0 ||year%400==0;
    }
    void show()const;

    int distance(const Date &date)const{
        return totalDays-date.totalDays;
    }
};

#endif //BANK_DATE_H
