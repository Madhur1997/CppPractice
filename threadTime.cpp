#include<iostream>
#include<vector>
#include<thread>
#include<queue>
#include<mutex>
#include<atomic>
#include<functional>
#include<condition_variable>
#include<chrono>

using namespace std;
using namespace std::literals;

int main() {
	chrono::time_point<chrono::system_clock, chrono::duration<double>> t = chrono::system_clock::now();
	auto timeNew = t + 3s;
	cout<<t.time_since_epoch().count() << endl;
	return 0;
}
