//
// Created by kyuu on 2025/6/2.
//

#ifndef BANK_ACCUMULATOR_H
#define BANK_ACCUMULATOR_H
#include"date.h"

class Accumulator{
private:
    Date lastDate;
    double value;
    double sum;
public:
    Accumulator( Date date,double value): lastDate(date),value(value),sum(0){};

    double getSum(Date date,double value){
        return sum+value*(date-lastDate);
    }

    void change(Date date,double value){
        sum= getSum(date,value);
        lastDate=date;
        this->value=value;
    }

    void reset(Date date,double value){
        lastDate=date;
        this->value=value;
        sum=0;
    }

};
#endif //BANK_ACCUMULATOR_H