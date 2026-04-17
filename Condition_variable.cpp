#include <bits/stdc++.h>
#include<mutex>
#include<condition_variable>
#include<thread>
using namespace std;
condition_variable cv;
double balance=0;
mutex m;
void addmoney(int amount){
    lock_guard<mutex>lock(m);
    balance+=amount;
    cout<<"Amount added in your Acount: "<<amount<<endl;
    cout<<"current balance :"<<balance<<endl;
    cv.notify_one();
}
void withdraw(int amount){
    unique_lock<mutex>ul(m);
    cv.wait(ul,[&](){return balance>= 0;});
    if(balance>=amount){
        balance-=amount;
        cout<<"you have withdraw amount"<<amount<<endl;
        cout<<"current balance after deduction :"<<balance<<endl;
    }else{
        cout<<"insufficient balance!!"<<endl;
    }
}


int main() {
    thread t1(withdraw,2000);
    thread t2(addmoney,1000);
    t1.join();
    t2.join();
	// your code goes here
return 0;
}
