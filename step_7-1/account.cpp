//
// Created by kyuu on 2025/6/2.
//


#include "account.h"
#include <cmath>
#include <iostream>
using namespace std;

double Account::total = 0;

RecordMap Account::recordMap;

Account::Account(const Date &date, const string &id):id(id),balance(0){
    date.show();
    cout << "\t#" << id << " created" << endl;
}

void AccountRecord::show()const{
    date.show();
    cout<<"\t#"<<account->getId()<<"\t"<<amount<<"\t"<<balance<<"\t"<<desc<<endl;
}

AccountRecord::AccountRecord(const Date&date,const Account *account,double amount,double balance,const string &desc):date(date),account(account),amount(amount),balance(balance),desc(desc){}



void Account::record(const Date &date, double amount, const string &desc) {
//    accumulation = accumulate(date);
//    lastDate = date;
    amount = floor(amount * 100 + 0.5) / 100;	//保留小数点后两位
    balance += amount;
    total+=amount;

    AccountRecord record(date,this,amount,balance,desc);


    recordMap.insert(make_pair(date,record));

    record.show();
}


void Account::error(const string &msg) const {
    cout << "Error(#" << id << "): " << msg << endl;
}

void Account::show() const {
    cout << id << "\tBalance: " << balance;
}

void Account::query(const Date&begin,const Date&end){
    if (begin <= end){
        RecordMap::iterator iter1 = recordMap.lower_bound(begin);
        RecordMap::iterator iter2 = recordMap.upper_bound(end);

        // 添加最大记录显示限制
        const int MAX_RECORDS = 1000;
        int recordCount = 0;

        for (RecordMap::iterator iter = iter1; iter != iter2; ++iter) {
            if (recordCount >= MAX_RECORDS) {
                cout << "Warning: Too many records to display. Only showing first " << MAX_RECORDS << " records." << endl;
                break;
            }
            iter->second.show();
            recordCount++;
        }
    } else {
        cout << "Error: Invalid date range" << endl;
    }
}

//SavingsAccount类相关成员函数的实现******************************************
SavingsAccount::SavingsAccount(const Date &date, const string &id, double rate)
        : Account(date,id), rate(rate), acc(date,0) {

}

void SavingsAccount::deposit(const Date &date, double amount, const string &desc) {
    record(date, amount, desc);
    acc.change(date,getBalance());
}

void SavingsAccount::withdraw(const Date &date, double amount, const string &desc) {
    if (amount > getBalance())
       // error("not enough money");
        throw AccountExcpetion(this,"Insufficient balance.");
    else{
        record(date, -amount, desc);
        acc.change(date,getBalance());
    }

}

void SavingsAccount::settle(const Date &date) {
    if(date.getMonth()==1&&date.getDay()==1){
        double interest = acc.getSum(date,getBalance()) * rate	//计算年息
                          / (date-Date(date.getYear() - 1, 1, 1));
        if (interest != 0)
            record(date, interest, "interest");
        acc.reset(date,getBalance());
    }

}


//CreditAccount实现**********************************************

CreditAccount::CreditAccount(const Date &date, const string &id, double credit, double rate, double fee)
        :Account(date,id), credit(credit), rate(rate), fee(fee), acc(date,0) {
}

void CreditAccount::deposit(const Date &date, double amount, const string &desc) {
    record(date, amount, desc);
    acc.change(date,getDebt());
}

void CreditAccount::withdraw(const Date &date, double amount, const string &desc) {
    if (amount > getBalance()+credit)
       // error("not enough credit");
        throw AccountExcpetion(this,"not enough credit.");
    else{
        record(date, -amount, desc);
        acc.change(date,getDebt());
    }
}

void CreditAccount::settle(const Date &date) {
    double interest = acc.getSum(date,getDebt()) * rate;//计算年息
    if (interest != 0)
        record(date, interest, "interest");
    if(date.getMonth()==1){
        record(date,-fee,"annual fee");
    }
    acc.reset(date,getDebt());
}

void CreditAccount::show()const{
    Account::show();
    cout<<"\tAvailable credit:"<<getAvailableCredit();
}