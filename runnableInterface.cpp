#include<thread>
#include<iostream>
#include<functional>
#include<vector>
#include<chrono>
#include<condition_variable>
#include<queue>

using namespace std;
using namespace std::literals;

#define pTT pair<RunnableTask, chrono::time_point<chrono::system_clock, chrono::duration<double>>>

class IRunnable { 

public:
	virtual void run() = 0;
};

class RunnableTask : public IRunnable { 

	function<void()> taskFn;
public:
	RunnableTask() {}
	RunnableTask(function<void()> f) : taskFn(f) {}

	void run() {
		cout<<"Executing inside run method" <<endl;
		taskFn();
	}
};

class Executor {

	class comparator { 

		public:
			bool operator() (const pTT & p1, const pTT & p2) {
				return p1.second > p2.second;
			}
	};

	int numThreads_;
	atomic<bool> running;
	chrono::time_point<chrono::system_clock, chrono::duration<double>> fst;
	vector<thread> workerThreads;
	thread poller;
	mutex mtx;
	condition_variable cv;
	priority_queue<pTT, vector<pTT>, comparator> runnableTaskQueue;

public:
	Executor(int numThreads) : numThreads_(numThreads), running(true) {
		fst = chrono::system_clock::now();
		for(int i=0; i<numThreads; i++) {
			workerThreads.emplace_back([this] {
				while(running) {
					cout<<"Executing thread "<<this_thread::get_id() << endl;
					pTT p;	
					{
						unique_lock<mutex> lock(mtx);
						auto nowTime = chrono::system_clock::now();
						cv.wait(lock, [this, nowTime] { cout<< "Checking condition" <<endl; auto nowTime = chrono::system_clock::now(); return ((!this->runnableTaskQueue.empty() && this->runnableTaskQueue.top().second < nowTime)|| !this->running);}); 

						if(!running) {
							return;
						}
						
						p = std::move(runnableTaskQueue.top());
						runnableTaskQueue.pop();
					}
					p.first.run();
				}
			});
		}

		poller = thread([this] {
				while(this->running) {
					unique_lock<mutex> lock(this->mtx);
					cout<<"Poller checking" <<endl;
					if(this->runnableTaskQueue.empty()) {
						lock.unlock();
						this_thread::sleep_for(1s);
					} else {
						auto taskTimePair = this->runnableTaskQueue.top();
						auto now = chrono::system_clock::now();
						cout<<"Time from beginning to now: " << (now-fst).count()<<endl;
						cout<<"Time from beginning to task time: " << (taskTimePair.second-fst).count()<<endl;
						if(taskTimePair.second < now) {
							cout<<"Scheduling one thread" << endl;
							this->cv.notify_one();
							lock.unlock();
							this_thread::sleep_for(10ms);
						} else {
							auto sleepUntil = (taskTimePair.second - fst).count();
							cout<< "Sleeping till " << sleepUntil<<endl;
							lock.unlock();
							this_thread::sleep_until(taskTimePair.second);
						}
					}
				}
			}
		);
	}

	~Executor() {
		{
			cout<<"Destructor called" <<endl;
			unique_lock<mutex> lock(mtx);
			running = false;
			cv.notify_all();
			lock.unlock();
			poller.join();
			for(int i=0; i<workerThreads.size(); i++) {
				workerThreads[i].join();
			}
		}
	}

	void addRunnable(RunnableTask & t, chrono::duration<double> waitTime) {
		chrono::time_point<chrono::system_clock, chrono::duration<double>> nowTime = chrono::system_clock::now();
		chrono::time_point<chrono::system_clock, chrono::duration<double>> endTime = nowTime + waitTime;
		{
			cout<<"Adding a runnable task " <<endl;
			unique_lock<mutex> lock(mtx);
			pTT p = make_pair(t, endTime);
			runnableTaskQueue.push(p);
			cv.notify_one();
		}
	}
};

int main() {

	cout<<"Executing in the main thread" << endl;
	Executor e(8);

	// Create runnable tasks and add to the queue
	for(int i=1; i< 500; i++) {
		RunnableTask rt([i] {cout<<"Task " << i <<endl;}); 
		e.addRunnable(rt, 50ms);
		this_thread::sleep_for(10ms);
	}


	this_thread::sleep_for(20s);
	return 0;
}
