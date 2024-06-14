#include "EvictionPolicyInterface.hpp"
#include <unordered_map>
#include <set>

using namespace std;

class LFUEvictionPolicy : public EvictionPolicyInterface {
    set<pair<int, int>> frequencyKeySet;
    unordered_map<int, int> keyFrequencyMap;
public:
    int getEvictionKey();
    void processKeyOnAdd(int key);
    void processKeyOnUpdate(int key);
    void processKeyOnDelete(int key);
};