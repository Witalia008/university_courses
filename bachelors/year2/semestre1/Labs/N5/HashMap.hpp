#include "HashTable.hpp"

template <class Type>
class Hash {
private:
    template<class KeyType, class ElType, class HashFunc>
    friend class HashMap;
    template<class ElType, class HashFunc>
    friend class HashTable;
    auto operator()(Type el) -> decltype(el.first) {
        hash<decltype(el.first)> hasher;
        return hasher(el.first);
    }
    Hash() {}
};

template<class KeyType, class ElType, class HashFunc = Hash<pair<KeyType, ElType>>>
class HashMap : public HashTable<pair<KeyType, ElType>, HashFunc> {
public:
    HashMap() {}
    HashMap(HashFunc);
    bool insert(const pair<KeyType, ElType>&);
    bool find(const pair<KeyType, ElType>&) const;
    bool remove(const pair<KeyType, ElType>&);
    bool insert(pair<KeyType, ElType>&&);
    bool find(pair<KeyType, ElType>&&) const;
    bool remove(pair<KeyType, ElType>&&);
};

template<class KeyType, class ElType, class HashFunc>
HashMap<KeyType, ElType, HashFunc>::HashMap(HashFunc func) {
    hash_func = func;
}

template<class KeyType, class ElType, class HashFunc>
bool HashMap<KeyType, ElType, HashFunc>::insert(const pair<KeyType, ElType>& val) {
    return HashTable<pair<KeyType, ElType>, HashFunc>::insert(val);
}

template<class KeyType, class ElType, class HashFunc>
bool HashMap<KeyType, ElType, HashFunc>::find(const pair<KeyType, ElType>& val) const {
    return HashTable<pair<KeyType, ElType>, HashFunc>::find(val);
}

template<class KeyType, class ElType, class HashFunc>
bool HashMap<KeyType, ElType, HashFunc>::remove(const pair<KeyType, ElType>& val) {
    return HashTable<pair<KeyType, ElType>, HashFunc>::remove(val);
}

template<class KeyType, class ElType, class HashFunc>
bool HashMap<KeyType, ElType, HashFunc>::insert( pair<KeyType, ElType>&& val) {
    return HashTable<pair<KeyType, ElType>, HashFunc>::insert(val);
}

template<class KeyType, class ElType, class HashFunc>
bool HashMap<KeyType, ElType, HashFunc>::find( pair<KeyType, ElType>&& val) const {
    return HashTable<pair<KeyType, ElType>, HashFunc>::find(val);
}

template<class KeyType, class ElType, class HashFunc>
bool HashMap<KeyType, ElType, HashFunc>::remove( pair<KeyType, ElType>&& val) {
    return HashTable<pair<KeyType, ElType>, HashFunc>::remove(val);
}
