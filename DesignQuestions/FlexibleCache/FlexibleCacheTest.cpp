#include <catch2/catch_test_macros.hpp>
#include "CacheStore.hpp"
#include "InMemDataStore.hpp"
#include "LRUEvictionPolicy.hpp"
#include "LFUEvictionPolicy.hpp"

using namespace std;

TEST_CASE("LRUEvictionPolicy") {
    CacheStore cacheStore(2, make_shared<InMemDataStore>(), make_shared<LRUEvictionPolicy>());
    cacheStore.put(1, 1);
    cacheStore.put(2, 2);
    cacheStore.put(3, 3);
    REQUIRE(cacheStore.get(1) == 1);
    cacheStore.put(4, 4);
    REQUIRE(cacheStore.get(2) == -1);
}

TEST_CASE("LFUEvictionPolicy") {
    CacheStore cacheStore(2, make_shared<InMemDataStore>(), make_shared<LFUEvictionPolicy>());
    cacheStore.put(1, 1);
    cacheStore.put(2, 2);
    REQUIRE(cacheStore.get(1) == 1);
    cacheStore.put(3, 3);
    REQUIRE(cacheStore.get(2) == -1);
}