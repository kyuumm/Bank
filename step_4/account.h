//
// Created by kyuu on 2025/5/30.
//

#ifndef BANK_ACCOUNT_H
#define BANK_ACCOUNT_H
#include<string>
#include"date.h"
#include"accumulator.h"
using namespace std;
class Account{
    private:
        string id;
        double balance;
        static double total;
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
#endif //BANK_ACCOUNT_H
