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
    // ��������أ�operator overloading����
    // �� C++ ��һ���ǳ���Ҫ�����ԣ�
    // ���������Լ������������������һ��ʹ�ó��������
    // ������ -��<��==��+ �ȵȣ���


        //������������
    int operator - (const Date& date)const {
        return totalDays - date.totalDays;
    }
    //�����Ⱥ�˳��
    bool operator < (const Date& date)const {
        return totalDays < date.totalDays;
    }
    bool operator <= (const Date& date)const {
        return totalDays < date.totalDays;
    }

    //static: �����������Ҫ�κζ���Ϳ��Ե���
    //����ֵ��Date�� �������������õ�һ���µ�Date����
    //ʹ�÷�����  Date d = Date::read();   ����d.read��Ҫ����ˣ�
    static Date read();


};

#endif //BANK_DATE_H