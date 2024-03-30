#include<iostream>
#include<vector>
#include<thread>
#include<mutex>

using namespace std;

int shared_value = 0;
mutex gLock;

int main() {
	
	auto lambda_thread_func = []() {
		lock_guard<mutex> lockGuard(gLock);
		shared_value++;
	};		

	vector<thread> threads;
	for(int i=0; i<10000; i++) {
		threads.emplace_back(lambda_thread_func);
	}

	for(int i=0; i<10000; i++) {
		threads[i].join();
	}

	cout<<"Hello from main thread" << " sharedValue: " << shared_value<<endl;
	
	return 0;
}
