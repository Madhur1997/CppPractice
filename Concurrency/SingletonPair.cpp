#include <iostream>
#include <mutex>
#include <atomic>

using namespace std;

class SP {
    static SP *instance1, *instance2;
    static atomic<int> call;
    mutex mtx;

    SP() = default;

public:
    SP(const SP& sp) = delete;
    SP operator=(const SP& sp) = delete;
    SP* getInstance() {
        int callValue = call.fetch_add(1);
        SP* instance = nullptr;
        if(callValue %2 == 0) {
            if(instance1 == nullptr) {
                unique_lock<mutex> lock(mtx);
                if(instance1 == nullptr) {
                    instance1 = new SP();
                }
            }
            instance = instance1;
        } else {
            if(instance2 == nullptr) {
                unique_lock<mutex> lock(mtx);
                if(instance2 == nullptr) {
                    instance2 = new SP();
                }
            }
            instance = instance2;
        }

        return instance;
    }
};

atomic<int> SP::call(0);
SP* SP::instance1 = nullptr;
SP* SP::instance2 = nullptr;


int main() {

    return 0;
}