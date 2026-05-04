#include<iostream>
#include<thread>
#include<semaphore>
using namespace std;
binary_semaphore  sem{1};
int balance=0;
int count=0;
void addmonet(int a){
    sem.acquire();
    balance+=a;
    cout<<"balance is added: "<<balance<<endl;
    cout<<count<<endl;
    count++;
    sem.release();
}

int main(){
    thread t1(addmonet,100);
    thread t2(addmonet,100);
    thread t3(addmonet,100);
    t1.join();
    t2.join();
    t3.join();
    return 0;
}
