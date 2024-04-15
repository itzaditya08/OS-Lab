#include <iostream>
#include <unordered_map>
#include <list>

using namespace std;

class LRUCache {
public:
    LRUCache(int capacity) : _capacity(capacity) {}

    // Get the value associated with a key from the cache
    int get(int key) {
        auto it = _cache.find(key);
        if (it == _cache.end()) return -1; // Key not found

        // Move the accessed key to the front of the list (recently used)
        _lru.splice(_lru.begin(), _lru, it->second);

        return it->second->second; // Return the value associated with the key
    }

    // Put a key-value pair into the cache
    void put(int key, int value) {
        auto it = _cache.find(key);
        if (it != _cache.end()) {
            // Update the value and move the key to the front of the list
            it->second->second = value;
            _lru.splice(_lru.begin(), _lru, it->second);
            return;
        }

        if (_cache.size() >= _capacity) {
            // Remove the least recently used key from the cache
            int lruKey = _lru.back().first;
            _cache.erase(lruKey);
            _lru.pop_back();
        }

        // Add the new key-value pair to the cache and the front of the list
        _lru.emplace_front(key, value);
        _cache[key] = _lru.begin();
    }

private:
    int _capacity;
    list<pair<int, int>> _lru; // Doubly linked list to keep track of access order
    unordered_map<int, list<pair<int, int>>::iterator> _cache; // Hash map for O(1) access
};

int main() {
    LRUCache cache(2); // Initialize an LRU cache with capacity 2

    cache.put(1, 10); // Cache: [(1, 10)]
    cache.put(2, 20); // Cache: [(1, 10), (2, 20)]
    cout << cache.get(1) << endl; // Returns 10, Cache: [(2, 20), (1, 10)]
    cache.put(3, 30); // Cache: [(3, 30), (1, 10)]
    cout << cache.get(2) << endl; // Returns -1 (not found)
    cache.put(4, 40); // Cache: [(4, 40), (3, 30)]
    cout << cache.get(1) << endl; // Returns -1 (not found)
    cout << cache.get(3) << endl; // Returns 30
    cout << cache.get(4) << endl; // Returns 40

    return 0;
}
