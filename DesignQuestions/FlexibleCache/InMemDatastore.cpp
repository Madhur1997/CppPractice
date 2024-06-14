#include "InMemDatastore.hpp"

using namespace std;

void InMemDataStore::put(int key, int val) {
    dataMap[key] = val;
}

int InMemDataStore::get(int key) {
    return dataMap[key];
}

void InMemDataStore::remove(int key) {
    dataMap.erase(key);
}