#include<iostream>
#include<thread>
#include<future>

using namespace std;
using namespace std::literals;

long getSum(long range) {
	cout << "Executing the sum function in thread " << this_thread::get_id() << endl;

	long sum = 0;
	for(long i=1; i<=range; i++) {
		sum += i;
	}

	this_thread::sleep_for(2s);
	return sum;
}

int main() {

	cout << "Executing in the main thread " << this_thread::get_id() << endl;

	auto start = chrono::system_clock::now();
	future<long> fu = std::async(std::launch::async, getSum, 1000000);

	this_thread::sleep_for(5s);
	cout<< fu.get() << endl;

	auto end = chrono::system_clock::now();
	chrono::duration<double> duration_seconds = end-start;
	cout<< "Duration is " << duration_seconds.count() << endl;

	return 0;
}
