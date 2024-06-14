#include "LFUEvictionPolicy.hpp"

using namespace std;

int LFUEvictionPolicy::getEvictionKey() {
    return frequencyKeySet.begin()->second;
}

void LFUEvictionPolicy::processKeyOnAdd(int key) {
    keyFrequencyMap[key] = 1;
    frequencyKeySet.insert({1, key});
}

void LFUEvictionPolicy::processKeyOnUpdate(int key) {
    frequencyKeySet.erase({keyFrequencyMap[key], key});
    keyFrequencyMap[key]++;
    frequencyKeySet.insert({keyFrequencyMap[key], key});
}

void LFUEvictionPolicy::processKeyOnDelete(int key) {
    frequencyKeySet.erase({keyFrequencyMap[key], key});
    keyFrequencyMap.erase(key);
}