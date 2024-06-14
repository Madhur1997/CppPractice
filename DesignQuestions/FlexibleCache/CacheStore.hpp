#include "DataStoreInterface.hpp"
#include "InMemDataStore.hpp"
#include "EvictionPolicyInterface.hpp"
#include "LFUEvictionPolicy.hpp"
#include "LRUEvictionPolicy.hpp"

class FlexibleCache {
    DataStoreInterface* dataStore;
    EvictionPolicyInterface* evictionPolicy;
    int capacity;

public:
    FlexibleCache(int capacity, DataStoreInterface* dataStore, EvictionPolicyInterface* evictionPolicy) : capacity(capacity), dataStore(dataStore), evictionPolicy(evictionPolicy) {}

    void put(int key, int val) {
        if (dataStore->get(key) != -1) {
            dataStore->put(key, val);
            evictionPolicy->processKeyOnUpdate(key);
        } else {
            if (dataStore->getSize() == capacity) {
                int key = evictionPolicy->getEvictionKey();
                evictionPolicy->processKeyOnDelete(key);
                dataStore->remove(key);
            }
            dataStore->put(key, val);
            evictionPolicy->processkeyOnAdd(key);
        }
    }

    int get(int key) {
        int val = dataStore->get(key);
        if (val != -1) {
            evictionPolicy->processKeyOnUpdate(key);
        }
        return val;
    }
};
