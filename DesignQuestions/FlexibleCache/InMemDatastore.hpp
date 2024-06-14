#include "DataStoreInterface.hpp"
#include <unordered_map>

using namespace std;

class InMemDataStore : public DataStoreInterface {
    unordered_map<int, int> dataMap;
public:
    void put(int key, int val);
    int get(int key);
    void remove(int key);
};