//---------------------------Reader Writer Using Queue--------------------------------
#include <bits/stdc++.h>

#include<mutex>

#include<condition_variable>

#include<thread>

using namespace std;
condition_variable cv;
double balance = 0;
mutex m;
std::queue < string > q;
#define max_size 10
void publishdata(const string & str) {
    unique_lock < mutex > lock(m);
    cv.wait(lock, [] {
        return q.size() < max_size;
    });
    q.push(str);
    lock.unlock();
    cv.notify_one();
}
void consumedata() {
    unique_lock < mutex > lock(m);
    cv.wait(lock, [] {
        return q.size() > 0;
    });
    string val = q.front();
    q.pop();
    cout << "Reading Data: " << val << endl;
    lock.unlock();
    cv.notify_one();
}


int main() {
    thread t1(publishdata, "world");
    thread t2(consumedata);
    t1.join();
    t2.join();
    // your code goes here
    return 0;
}