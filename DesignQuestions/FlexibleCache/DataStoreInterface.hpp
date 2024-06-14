using namespace std;

class DataStoreInterface {
    int size;
public:
    virtual void put(int key, int val) = 0;
    virtual int get(int key) = 0;
    virtual void remove(int key) = 0;
    int getSize() {
        return size;
    }
};