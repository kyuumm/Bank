//
// Created by kyuu on 2025/5/20.
//声明（接口）说明函数

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H

class SavingsAccount{
private:
    int id;
    double balance;
    double rate;
    int lastDate;
    double accumulation;

    void record(int date,double amount);

    double accumulate(int date){
        return accumulation+balance*(date-lastDate);
    }

public:
    SavingsAccount(int date,int id,double rate);

    int getId()const{return id;}
    double getBalance()const{return balance;}
    double getRate()const{return rate;}

    void show()const;
    void deposit(int date,double amount);
    void withdraw(int date,double amount);
    void settle(int date);
};

#endif //BANK_ACCOUNT_H
