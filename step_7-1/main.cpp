//
// Created by kyuu on 2025/6/2.
//
//step5.cpp

#include "account.h"

#include <iostream>

#include <vector>

#include <algorithm>

#include<fstream>
#include<sstream>
#include<graphics.h>

using namespace std;

IMAGE img_bk;
IMAGE img_btn;

void loadResource() {
    loadimage(&img_bk, _T("asset/bk.jpg"));
    loadimage(&img_btn, _T("asset/btn.jpg"));
}


void drawDefaultUI() {
    putimage(0, 0, &img_bk);


	setbkmode(TRANSPARENT);
	settextcolor(BLACK);
    settextstyle(28, 0, _T("΢���ź�"));

    putimage(20, 230, &img_btn);
    outtextxy(20, 200, _T("��[A]����˻�"));

  
    outtextxy(100, 560, _T("���������ն������������"));

}


struct deleter {

    template <class T> void operator () (T* p) { delete p; }

};


//�����֣���ȡ��ʷ������뽻��ʽѭ����׷�Ӽ�¼
int main() {

    initgraph(480, 600);
    loadResource();



    ifstream fin("commands.txt");

    Date date(2008, 11, 1);//��ʼ����

    vector<Account*> accounts;//�����˻����飬Ԫ�ظ���Ϊ0


    if (fin) {


        string line;

        //getline(fin,line):��cin�ļ��ڻ�ȡһ��һ�е����ݣ�����ֵ��line
        while (getline(fin, line)) {
            if (line.empty())continue;

            //iss(istringstream): �����һ���ִʻ������տո��һ���е��ı��г�һ������
            istringstream iss(line);

            char fileCmd;
            iss >> fileCmd;
            //������cin>>����
            //iss>>variable
            //variable������int double char string Ҳ����˵��һ������ֻ���ȡ��Ӧ������


            if (fileCmd == 'a') {
                char type;
                string id;
                iss >> type >> id;

                if (type == 's') {
                    double rate;
                    iss >> rate;
                    accounts.push_back(new SavingsAccount(date, id, rate));

                }
                else {
                    double credit, rate, fee;
                    iss >> credit >> rate >> fee;
                    accounts.push_back(new CreditAccount(date, id, credit, rate, fee));
                }


            }

            //deposit
            else if (fileCmd == 'd') {

                int index;
                double amount;
                iss >> index >> amount;

                string desc;

                getline(iss, desc);

                if (index >= 0 && index < (int)accounts.size()) {
                    accounts[index]->deposit(date, amount, desc);
                }

            }

            //withdraw
            else if (fileCmd == 'w') {

                int index;
                double amount;
                iss >> index >> amount;
                string desc;

                getline(iss, desc);

                if (index >= 0 && index < (int)accounts.size()) {
                    accounts[index]->withdraw(date, amount, desc);
                }

            }

            //change day
            else if (fileCmd == 'c') {
                int d;
                iss >> d;

                if (d >= 1 && d <= date.getMaxDay()) {
                    date = Date(date.getYear(), date.getMonth(), d);
                }


            }

            //next month
            else if (fileCmd == 'n') {
                if (date.getMonth() == 12) { date = Date(date.getYear() + 1, 1, 1); }

                else { date = Date(date.getYear() + 1, date.getMonth() + 1, 1); }

                for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter) {
                    (*iter)->settle(date);
                }
            }

            //            //search
            //            else if(fileCmd=='s'){
            //                    for (size_t i = 0; i < accounts.size(); i++) {
            //
            //                        cout << "[" << i << "] ";
            //
            //                        accounts[i]->show();
            //
            //                        cout << endl;
            //
            //                    }
            //            }


                            //query
            else if (fileCmd == 'q') {
                int y1, m1, d1, y2, m2, d2;
                iss >> y1 >> m1 >> d1 >> y2 >> m2 >> d2;
                Date date1(y1, m1, d1), date2(y2, m2, d2);

                Account::query(date1, date2);
            }




        }

        fin.close();
    }

    //��ӻ��У�����commands����һ����
    //commands.txt*****************************
    {
        ofstream fout("commands.txt", ios::app);
        // ֻ�����һ�в��ǿ��е��������ӻ���
        string lastLine;
        ifstream checkLast("commands.txt");



        string line;
        while (getline(checkLast, line)) {
            if (!line.empty()) {
                lastLine = line;
            }
        }
        checkLast.close();

        if (!lastLine.empty()) {
            fout << endl;
        }
        fout.close();
    }


    cout << endl;
    cout << "(a)add account (d)deposit (w)withdraw (s)show (c)change day (n)next month (q)query (e)exit" << endl;

    char cmd;

    try {

        do {

            //��ʾ���ں��ܽ��

            drawDefaultUI();

            date.show();

            cout << "\tTotal: " << Account::getTotal() << "\tcommand> ";



            char type;

            int index, day;

            double amount, credit, rate, fee;

            string id, desc;

            Account* account;

            Date date1, date2;



            cin >> cmd;

            switch (cmd) {

            case 'a'://�����˻�

                cin >> type >> id;

                if (type == 's') {

                    cin >> rate;

                    account = new SavingsAccount(date, id, rate);

                }

                else {

                    cin >> credit >> rate >> fee;

                    account = new CreditAccount(date, id, credit, rate, fee);

                }

                accounts.push_back(account);

                //commands.txt*************************
                {
                    //д���ļ������fout
                    ofstream fout("commands.txt", ios::app);
                    fout << "a " << type << " " << id;

                    if (type == 's')  fout << " " << rate;
                    else fout << " " << credit << " " << rate << " " << fee;

                    fout << endl;

                    //�����ŵ���˼���ֲ������������������fout�������������Զ����ã��ļ����ر�
                    //Ҳ���Բ��Ӵ����ţ�ֱ�ӽ�βfout.close()
                }

                break;

            case 'd'://�����ֽ�

                cin >> index >> amount;

                getline(cin, desc);

                accounts[index]->deposit(date, amount, desc);


                //commands.txt*****************************
                {
                    ofstream fout("commands.txt", ios::app);

                    fout << "d " << index << " " << amount << " " << desc << endl;
                }

                break;



            case 'w'://ȡ���ֽ�

                cin >> index >> amount;

                getline(cin, desc);

                accounts[index]->withdraw(date, amount, desc);

                //commands.txt*****************************
                {
                    ofstream fout("commands.txt", ios::app);

                    fout << "w " << index << " " << amount << " " << desc << endl;
                }

                break;

            case 's'://��ѯ���˻���Ϣ

                for (size_t i = 0; i < accounts.size(); i++) {

                    cout << "[" << i << "] ";

                    accounts[i]->show();

                    cout << endl;

                }

                break;

            case 'c'://�ı�����

                cin >> day;

                if (day < date.getDay())

                    cout << "You cannot specify a previous day";

                else if (day > date.getMaxDay())

                    cout << "Invalid day";

                else

                    date = Date(date.getYear(), date.getMonth(), day);

                //commands.txt**********************
                {
                    ofstream fout("commands.txt", ios::app);
                    fout << "c " << day << endl;
                }

                break;

            case 'n'://�����¸���

                if (date.getMonth() == 12)

                    date = Date(date.getYear() + 1, 1, 1);

                else

                    date = Date(date.getYear(), date.getMonth() + 1, 1);

                for (vector<Account*>::iterator iter = accounts.begin(); iter != accounts.end(); ++iter)

                    (*iter)->settle(date);

                //commands.txt**********************
                {
                    ofstream fout("commands.txt", ios::app);
                    fout << "n " << endl;
                }

                break;

            case 'q'://��ѯһ��ʱ���ڵ���Ŀ

                date1 = Date::read();

                date2 = Date::read();

                Account::query(date1, date2);


                //commands.txt**********************
                {
                    ofstream fout("commands.txt", ios::app);
                    fout << "q " <<
                        date1.getYear() << " " << date1.getMonth() << " " << date1.getDay() << " " <<
                        date2.getYear() << " " << date2.getMonth() << " " << date2.getDay() <<
                        endl;
                }


                break;

            }

        } while (cmd != 'e');

    }
    catch (const AccountExcpetion& e) {
        cout << "Account:";
        e.getAccount()->show();
        cout << " Failed:" << e.what() << endl;
    }
    catch (const runtime_error& e) {
        cout << "other runtime error:" << e.what() << endl;
    }





    for_each(accounts.begin(), accounts.end(), deleter());

    return 0;

}