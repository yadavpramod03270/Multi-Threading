#include<bits/stdc++.h>
#include<thread>
#include<mutex>
using namespace std;
timed_mutex m;
int incr=0;
void increment(int i){
    if(m.try_lock_for(std::chrono::seconds(1))){
    ++incr;
    this_thread::sleep_for(std::chrono::seconds(2));
    cout<<"thread "<<i<<" enter"<<endl;
    m.unlock();
    }
    else{
        cout<<"thread "<<i<<" couldn't  enter"<<endl;
    }
    
}
int main(){
    thread t1(increment,1);
    thread t2(increment,2);
    t1.join();
    t2.join();
cout<<"increment: "<<incr<<endl;
    return 0;
}