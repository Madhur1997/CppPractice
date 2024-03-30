#include<iostream>
#include<chrono>
#include<thread>
#include<queue>
#include<functional>
#include<mutex>

using namespace std;
using namespace std::literals;

class LeakyBucket {
	queue<chrono::duration<double>> bucket;
	int bucketCapacity_;
	int rate_;
	mutex mtx;

	LeakyBucket(int bucketCapacity, int rate) : bucketCapacity_(bucketCapacity), rate_(rate) {}

public:

	bool canAccept(string req) {
		auto now = chrono::system_clock::now().time_since_epoch();
	
		unique_lock<mutex> lock(mtx);
		drip(now);

		if(bucket.size() >= bucketCapacity_) { 
			return false;
		}

		if(bucket.empty()) {
			bucket.push(now);
			return true;
		}
			
		auto duration = now.count() - bucket.front().count();
		int allowedRequests  = duration * rate_;
		if(allowedRequests >= bucket.size() + 1) {
			bucket.push(now);
			return true;
		}
		return false;
	}

	void drip(chrono::duration<double> currTime) {
		while(!bucket.empty() && bucket.front().count() < currTime.count()-1) {
			bucket.pop();
		}
	}

};

int main() {

	return 0;
}
