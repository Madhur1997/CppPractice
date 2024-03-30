#include<iostream>
#include<thread>
#include<future>

using namespace std;

void getSum(promise<long> && pro, long range) {
	cout << "Executing the sum function in thread " << this_thread::get_id() << endl;

	long sum = 0;
	for(long i=1; i<=range; i++) {
		sum += i;
	}

	pro.set_value(sum);
}

int main() {

	promise<long> pr;
	future<long> fu = pr.get_future();

	cout << "Executing in the main thread " << this_thread::get_id() << endl;
	thread t1(getSum, move(pr), (long)1000000000);

	cout<< "Sum is " << fu.get() << endl;
	t1.join();

	return 0;
}
