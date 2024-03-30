#include<iostream>
#include<thread>
#include<condition_variable>
#include<mutex>

using namespace std;
using namespace std::literals;

int main() {

	thread t1([] { cout<<"Hello"; });

	this_thread::sleep_for(5s);
	if(t1.joinable()) {
		cout<<"true"<<endl;
		t1.join();
	} else {
		cout<<"false"<<endl;
	}
	return 0;
}
