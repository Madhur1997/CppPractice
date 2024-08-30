#include<iostream>
#include<vector>
#include<thread>
#include<mutex>
#include<atomic>

using namespace std;

static int shared_value;


int main() {
	shared_value = 0;
	auto lambda_thread_func = []() {
		shared_value+=2;
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
