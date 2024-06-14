#include "LRUEvictionPolicy.hpp"

using namespace std;

int LRUEvictionPolicy::getEvictionKey() {
    return keyList.back();
}

void LRUEvictionPolicy::processKeyOnAdd(int key) {
    keyList.push_front(key);
    keyListIteratorMap[key] = keyList.begin();
}

void LRUEvictionPolicy::processKeyOnUpdate(int key) {
    keyList.erase(keyListIteratorMap[key]);
    keyList.push_front(key);
    keyListIteratorMap[key] = keyList.begin();
}

void LRUEvictionPolicy::processKeyOnDelete(int key) {
    keyList.erase(keyListIteratorMap[key]);
    keyListIteratorMap.erase(key);
}