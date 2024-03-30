#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<chrono>

using namespace std;

mutex mtx;

void func1() {
	lock_guard<mutex> lock(mtx);
	cout<<"Performing steps from func1" <<endl;
}

void func2() {
	if(mtx.try_lock()) {
		cout<<"Trying to perform steps from func2" <<endl;
		mtx.unlock();
	} else {
		this_thread::sleep_for(chrono::seconds(2));
		mtx.lock();
			cout<<"Performing steps from func2" << endl;
		mtx.unlock();
	}
}

int main() {
	
	std::thread thread1(func1), thread2(func2);
	thread1.join();
	thread2.join();	
	return 0;
}
