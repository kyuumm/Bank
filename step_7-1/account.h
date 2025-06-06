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


class AccountRecord {
private:
    Date date;
    const Account* account;//�˻���
    double amount;//���
    double balance;//���
    string desc;

public:
    AccountRecord(const Date& date, const Account* account, double amount, double balance, const string& desc);
    void show()const;
};

//*********************************
typedef multimap<Date, AccountRecord>RecordMap;
//*********************************

class Account {
private:
    string id;
    double balance;
    static double total;

    static RecordMap recordMap;
protected:
    Account(const Date& date, const string& id);
    void error(const std::string& msg) const;
    void record(const Date& date, double amount, const string& desc);


public:
    string getId()const { return id; }
    double getBalance() const { return balance; }
    static double getTotal() { return total; }

    virtual void show() const;

    virtual void deposit(const Date& date, double amount, const string& desc) = 0;
    virtual void withdraw(const Date& date, double amount, const string& desc) = 0;
    virtual void settle(const Date& date) = 0;

    static void query(const Date& begin, const Date& end);
};

class SavingsAccount :public Account {
private:
    double rate;
    Accumulator acc;
public:
    SavingsAccount(const Date& date, const string& id, double rate);

    void deposit(const Date& date, double amount, const string& desc);
    void withdraw(const Date& date, double amount, const string& desc);

    void settle(const Date& date);
    double getRate() { return rate; }
};

class CreditAccount :public Account {
private:
    Accumulator acc;
    double rate;
    double credit;
    double fee;

    double getDebt()const {
        double balance = getBalance();
        return (balance < 0 ? balance : 0);
    }
public:
    CreditAccount(const Date& date, const string& id, double credit, double rate, double fee);

    void  deposit(const Date& date, double amount, const string& desc);
    void withdraw(const Date& date, double amount, const string& desc);

    double getAvailableCredit()const {
        if (getBalance() < 0) { return credit + getBalance(); }
        else return credit;
    }

    void settle(const Date& date);
    double getRate() { return rate; }
    double getFee() { return fee; }
    double getCredit() { return credit; }
    void show()const;
};

class AccountExcpetion :public runtime_error {
private:
    const Account* account;
public:
    AccountExcpetion(const Account* acc, const string& desc) : runtime_error(desc), account(acc) {}

    const Account* getAccount()const { return account; }
};

//typedef:
//����������ȡһ�������ֵĹؼ���
//typedef �������� ������




//typedef std::multimap<Date, AccountRecord> RecordMap;
//����������ʲô��
//
//std::multimap<Date, AccountRecord> ��һ�� STL�������ͣ���ʾһ������ӳ�䣨multimap����
//
//���еļ���key���� Date ���ͣ����ڣ���
//
//ֵ��value���� AccountRecord ���ͣ���Ŀ��¼����
//
//��������ܴ洢�����ͬ���ڶ�Ӧ�Ĳ�ͬ��Ŀ����Ϊ��multimap������map��������ظ�����

#endif //BANK_ACCOUNT_H