#include<bits/stdc++.h>
#include<mutex>
#include<condition_variable>
using namespace std;
class bank{
    public:
	virtual bool login()=0;
	virtual bool logout()=0;
	virtual void fetch_balance()=0;
	virtual void withdraw(int amount)=0;
	virtual void deposite(int amount)=0;
	virtual ~bank()=default;
};
class bank_Acount:public bank{
	int balance=500;
	public:
	condition_variable cv;
	mutex m;
	bool login()override{
		return true;
	}
	bool logout( )override{
	    return false;
	}
	void fetch_balance()override{
		cout<<"Current Balance: "<<balance<<endl;
	}
	void withdraw(int amount)override{
		unique_lock<mutex>ul(m);
		cv.wait(ul,[&](){ return balance>0; });
		if(balance>amount){
			balance-=amount;
		cout<<"you have deducted: "<<amount<<"RS"<<endl;
		cout<<"Current Balance: "<<balance<<endl;
	}
	else{
		cout<<"Insufficient Balance"<<endl;
	}
	}
	void deposite(int amount)override{
		lock_guard<mutex>lock(m);
		balance+=amount;
		cout<<"You have deposited amount: "<<amount<<" and Current Balance is: "<<balance<<endl;
		cv.notify_one();
	}
	
		
};
class ATM:public bank{
	int hash=1234;
	bool authantication=false;
	bank* realbank;
	public:
	ATM(bank* r):realbank(r){}
	bool login()override{
		cout<<"ENTER PIN: "<<endl;
		int pin;
		cin>>pin;
		if(pin==hash){
			authantication=true;
			 
		}
		else{
			cout<<"wrong password "<<endl;
		}
		return authantication;
			
	}
	 bool logout() override {
        authantication = false;
        cout << "[ATM] Logged out\n";
        return authantication;
    }

	void fetch_balance()override{
		if(authantication==true){
			realbank->fetch_balance();
		}
	}
	void withdraw(int amount)override{
	    if(authantication==true){
		realbank->withdraw(amount);
	    }
	}
	void deposite(int amount)override{
	    if(authantication==true){
		realbank->deposite(amount);
	    }
	}
	
	
	
};
int main(){
	bank *b=new bank_Acount();
	ATM *c= new ATM(b);
	c->login();
	c->fetch_balance();
	thread t(&ATM::withdraw, c, 20);
	thread t1(&ATM::deposite, c, 4000);
	t.join();
	t1.join();
	c->logout();
	
	
	return 0;
}
