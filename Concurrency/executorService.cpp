#include<iostream>
#include<thread>
#include<vector>
#include<chrono>
#include<condition_variable>
#include<queue>
#include<mutex>
#include<functional>

using namespace std;
using namespace std::literals;

#define pTT pair<RunnableTaskWithPeriodAndDelays, chrono::time_point<chrono::system_clock, chrono::duration<double>>>

class IRunnableInterface {
public:
	chrono::duration<double> initialDelay;
	chrono::duration<double> period;
	chrono::duration<double> delay;
	virtual void run() = 0;
};

class RunnableTaskWithPeriodAndDelays : public IRunnableInterface {
	function<void()> taskFn;
public:
	RunnableTaskWithPeriodAndDelays() {}
	RunnableTaskWithPeriodAndDelays(function<void()> f) : taskFn(f) {
		initialDelay = 0ms;
		period = 0ms;
		delay = 0ms;
	}
	void run() {
		cout<<"run function called from thread" << this_thread::get_id() <<endl;
		taskFn();
	}
};

class ExecutorService {

	struct comparator {
		public:
		bool operator()(const pTT & p1, const pTT & p2) {
			return p1.second > p2.second;
		}
	};

	int numThreads_;
	atomic<bool> running;
	mutex mtx;
	condition_variable cvWorker, cvScheduler;
	vector<thread> workerThreads;
	thread scheduler;
	priority_queue<pTT, vector<pTT>, comparator> taskQueue;
public:
	ExecutorService(int numThreads) : numThreads_(numThreads), running(true) {
		for(int i=0; i<numThreads; i++) { 
			workerThreads.emplace_back([this] {
				while(this->running) {
					unique_lock<mutex> lock(this->mtx);
					auto now = chrono::system_clock::now();
					cvWorker.wait(lock, [this] { auto now = chrono::system_clock::now(); return ((!this->taskQueue.empty() && now > this->taskQueue.top().second) || !this->running); });
					if(!this->running) {
						return;
					}
					pTT p = std::move(this->taskQueue.top());
					this->taskQueue.pop();
					if(p.first.period > 0ms) {
				   		// schedule the next task before starting this task	
						auto now = chrono::system_clock::now();
						auto nextTime = now + p.first.period;
						this->taskQueue.push(make_pair(p.first, nextTime));
					}
					lock.unlock();
					p.first.run();
					if(p.first.delay > 0ms) {
				   		// schedule the next task after the end of this task	
						auto now = chrono::system_clock::now();
						auto nextTime = now + p.first.delay;
						unique_lock<mutex> lock(this->mtx);
						this->taskQueue.push(make_pair(p.first, nextTime));
					}
				}
			});
		}

		scheduler = thread([this] {
			while(this->running) {
				cout<<"Scheduler in action" <<endl;

				unique_lock<mutex> lock(this->mtx);
				cvScheduler.wait(lock, [this]{
					return (!this->running || (!this->taskQueue.empty()));
				});
				if(!this->running) {
					return;
				}
				auto now = chrono::system_clock::now();
				if(this->taskQueue.top().second > now) {
					cvScheduler.wait_until(lock, taskQueue.top().second, [this] {
						auto now = chrono::system_clock::now();
						return (!this->running || (!this->taskQueue.empty() && !(this->taskQueue.top().second > now)));
					});		
				}
				if(!this->running) {
					return;
				}

				cout<<"Scheduling one task" <<endl;
				cvWorker.notify_one();
				lock.unlock();
				this_thread::sleep_for(2ms);
			}
		});
	}

	~ExecutorService() {
		unique_lock<mutex> lock(mtx);
		running = false;
		lock.unlock();
		cvScheduler.notify_one();
		cvWorker.notify_all();
		if(scheduler.joinable()) {
			scheduler.join();
		}
		for(int i=0; i<workerThreads.size(); i++) {
			if(workerThreads[i].joinable()) {
				workerThreads[i].join();
			}
		}
	}

	void schedule(function<void()> f, chrono::duration<double> initialDelay) {
		cout<< "Adding scheduled task" <<endl;
		unique_lock<mutex> lock(mtx);
		RunnableTaskWithPeriodAndDelays rt(f);
		rt.initialDelay = initialDelay;
		auto now = chrono::system_clock::now();
		pTT p = make_pair(rt, now + initialDelay);
		if(!taskQueue.empty() && p.second < taskQueue.top().second) {
			cvScheduler.notify_one();
		}

		taskQueue.push(p);
	}

	void scheduleWithPeriod(function<void()> f, chrono::duration<double> initialDelay, chrono::duration<double> period) {
		cout<< "Adding scheduled task with period" <<endl;
		unique_lock<mutex> lock(mtx);
		RunnableTaskWithPeriodAndDelays rt(f);
		rt.initialDelay = initialDelay;
		rt.period = period;
		auto now = chrono::system_clock::now();
		pTT p = make_pair(rt, now + initialDelay);
		if(!taskQueue.empty() && p.second < taskQueue.top().second) {
			cvScheduler.notify_one();
		}

		taskQueue.push(p);
	}

	void scheduleWithFixedDelay(function<void()> f, chrono::duration<double> initialDelay, chrono::duration<double> delay) {
		cout<< "Adding scheduled task with fixed delay" <<endl;
		unique_lock<mutex> lock(mtx);
		RunnableTaskWithPeriodAndDelays rt(f);
		rt.initialDelay = initialDelay;
		rt.delay = delay;
		auto now = chrono::system_clock::now();
		pTT p = make_pair(rt, now + initialDelay);
		if(!taskQueue.empty() && p.second < taskQueue.top().second) {
			cvScheduler.notify_one();
		}
		taskQueue.push(p);
	}
};

int main() {

	cout<<"Executing main thread"<<endl;
	ExecutorService e(8);

	for(int i=1; i<=50; i++) {
		e.schedule( [i] {
			cout << "Executing task " << i <<endl;
		}, 10ms);
	}

	for(int i=51; i<=60; i++) {
		e.scheduleWithPeriod( [i] {
			cout << "Executing task repeatedly" << i <<endl;
		}, 10ms, 500ms);
	}

	for(int i=61; i<=70; i++) {
		e.scheduleWithFixedDelay( [i] {
			cout << "Executing delayed task" << i <<endl;
		}, 10ms, 1000ms);
	}

	this_thread::sleep_for(30s);
	return 0;
}
