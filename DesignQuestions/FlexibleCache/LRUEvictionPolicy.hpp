#include "EvictionPolicyInterface.hpp"
#include <unordered_map>
#include <list>

using namespace std;

class LRUEvictionPolicy : public EvictionPolicyInterface {
    list<int> keyList;
    unordered_map<int, list<int>::iterator> keyListIteratorMap;
public:
    int getEvictionKey();
    void processKeyOnAdd(int key);
    void processKeyOnUpdate(int key);
    void processKeyOnDelete(int key);
};