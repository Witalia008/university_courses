#include <vector>
#include <list>
#include <stdexcept>

using namespace std;

template<class ElType, class HashFunc = hash<ElType>>
class HashTable {
protected:
    static const int DEFAULT_TABLE_SIZE;
    vector<list<ElType>> table;
    mutable HashFunc hash_func;
public:
    HashTable();
    HashTable(HashFunc);
    bool insert(const ElType&);
    bool find(const ElType&) const;
    bool remove(const ElType&);
    bool insert(ElType&&);
    bool find(ElType&&) const;
    bool remove(ElType&&);
};

template<class ElType, class HashFunc>
const int HashTable<ElType, HashFunc>::DEFAULT_TABLE_SIZE = 100207;

template<class ElType, class HashFunc>
HashTable<ElType, HashFunc>::HashTable() {
    table.resize(DEFAULT_TABLE_SIZE);
}

template<class ElType, class HashFunc>
HashTable<ElType, HashFunc>::HashTable(HashFunc func) {
    table.resize(DEFAULF_TABLE_SIZE);
    hash_func = func;
}

template<class ElType, class HashFunc>
bool HashTable<ElType, HashFunc>::insert(const ElType& El) {
    if (find(El))
        return false;
    table[hash_func(El) % table.size()].push_back(El);
    return true;
}

template<class ElType, class HashFunc>
bool HashTable<ElType, HashFunc>::find(const ElType& El) const {
    int pos = hash_func(El) % table.size();
    auto it = table[pos].begin();
    for (int i = 0; i < table[pos].size(); ++i, ++it)
        if (*it == El)
            return true;
    return false;
}

template<class ElType, class HashFunc>
bool HashTable<ElType, HashFunc>::remove(const ElType& El) {
    int pos = hash_func(El) % table.size();
    auto it = table[pos].begin();
    for (int i = 0; i < table[pos].size(); ++i, ++it)
        if (*it == El) {
            table[pos].erase(it);
            return true;
        }
    return false;
}

template<class ElType, class HashFunc>
bool HashTable<ElType, HashFunc>::insert(ElType&& El) {
    if (find(El))
        return false;
    table[hash_func(El) % table.size()].emplace_back(El);
    return true;
}

template<class ElType, class HashFunc>
bool HashTable<ElType, HashFunc>::find(ElType&& El) const {
    return find(El);
}

template<class ElType, class HashFunc>
bool HashTable<ElType, HashFunc>::remove(ElType&& El) {
    return remove(El);
}