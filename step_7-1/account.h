//
// Created by kyuu on 2025/6/2.
//

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H
#include<string>
#include"date.h"
#include"accumulator.h"
#include<stdexcept>
#include<map>


using namespace std;

class Account;


class AccountRecord{
private:
    Date date;
    const Account *account;//账户们
    double amount;//金额
    double balance;//余额
    string desc;

public:
    AccountRecord(const Date&date,const Account *account,double amount,double balance,const string &desc);
    void show()const;
};

//*********************************
typedef multimap<Date,AccountRecord>RecordMap;
//*********************************

class Account{
private:
    string id;
    double balance;
    static double total;

    static RecordMap recordMap;
protected:
    Account(const Date &date,const string &id);
    void error(const std::string &msg) const;
    void record(const Date&date,double amount,const string &desc);


public:
    string getId()const { return id; }
    double getBalance() const { return balance; }
    static double getTotal() { return total; }

    virtual void show() const;

    virtual void deposit(const Date&date,double amount,const string&desc)=0;
    virtual void withdraw(const Date&date,double amount,const string&desc)=0;
    virtual void settle(const Date&date)=0;

    static void query(const Date&begin,const Date&end);
};

class SavingsAccount:public Account{
private:
    double rate;
    Accumulator acc;
public:
    SavingsAccount(const Date&date,const string &id,double rate);

    void deposit(const Date&date,double amount,const string& desc);
    void withdraw(const Date&date,double amount,const string& desc);

    void settle(const Date&date);
    double getRate(){return rate;}
};

class CreditAccount:public Account{
private:
    Accumulator acc;
    double rate;
    double credit;
    double fee;

    double getDebt()const{
        double balance=getBalance();
        return (balance<0?balance:0);
    }
public:
    CreditAccount(const Date&date,const string &id,double credit,double rate,double fee);

    void  deposit(const Date&date,double amount,const string& desc);
    void withdraw(const Date&date,double amount,const string& desc);

    double getAvailableCredit()const{
        if (getBalance()<0){return credit+getBalance();}
        else return credit;
    }

    void settle(const Date&date);
    double getRate(){return rate;}
    double getFee(){return fee;}
    double getCredit(){return credit;}
    void show()const;
};

class AccountExcpetion:public runtime_error{
private:
    const Account* account;
public:
    AccountExcpetion(const Account*acc,const string & desc): runtime_error(desc),account(acc){}

    const Account*getAccount()const{return account;}
};

//typedef:
//给已有类型取一个新名字的关键字
//typedef 已有类型 新名字




//typedef std::multimap<Date, AccountRecord> RecordMap;
//这里它做了什么？
//
//std::multimap<Date, AccountRecord> 是一个 STL容器类型，表示一个多重映射（multimap），
//
//其中的键（key）是 Date 类型（日期），
//
//值（value）是 AccountRecord 类型（账目记录）。
//
//这个容器能存储多个相同日期对应的不同账目（因为是multimap，不是map，允许键重复）。

#endif //BANK_ACCOUNT_H