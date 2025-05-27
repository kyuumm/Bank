//account.h
#ifndef __ACCOUNT_H__
#define __ACCOUNT_H__
#include <string>
#include "date.h"
#include"accumulator.h"
using namespace std;
class Account{
private:
    string id;
    double balance;
    static double total;

protected:
    Account(const Date &date,const string &id);

    void record(const Date &date, double amount, const string &desc);
    //报告错误信息
    void error(const std::string &msg) const;

public:

    string getId()const { return id; }
    double getBalance() const { return balance; }

    static double getTotal() { return total; }

    void show() const;
};

class SavingsAccount:public Account { //储蓄账户类
private:
    double rate;		//存款的年利率
    Accumulator acc;

public:
    //构造函数
    SavingsAccount(const Date &date, const std::string &id, double rate);


    double getRate() const { return rate; }
    //存入现金
    void deposit(const Date &date, double amount, const string &desc);
    //取出现金
    void withdraw(const Date &date, double amount, const string &desc);
    //结算利息，每年1月1日调用一次该函数
    void settle(const Date &date);
    //显示账户信息

};

class CreditAccount:public Account { //储蓄账户类
private:
    Accumulator acc;
    double rate;		//欠款的年利率
    double credit;
    double fee;

    double getDebt() const {//欠款额
        double balance =getBalance();
        return (balance<0?balance:0);
    }

public:
    //构造函数
    CreditAccount(const Date &date, const string &id,double credit, double rate,double fee);


    double getCredit()const{return credit;}

    double getRate() const { return rate; }

    double getFee()const {return fee;}

    double getAvailableCredit()const{
        if(getBalance()<0)
            return credit+getBalance();
        else
            return credit;
    }

    void deposit(const Date&date,double amount ,const string&desc);
    void withdraw(const Date&date,double amount ,const string&desc);

    void settle(const Date&date);

    void show()const;
};

#endif //__ACCOUNT_H__
