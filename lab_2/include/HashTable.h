#ifndef LAB2_INCLUDE_HASHTABLE_H
#define LAB2_INCLUDE_HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <functional>

template <typename Key, typename Value>
class HashTable {
    struct Pair {
        Key key;
        Value value;
        /*
        Pair() : key(0), value(0){}
        Pair(const Key& key, const Value& value) : key(key), value(value){}*/

    };

    std::vector<std::list<Pair>> _data;
    size_t _size;

    size_t divisionHash(const Key& key) const {
        if constexpr (std::is_arithmetic_v<Key>) {
            return key % _data.size();
        }
        else {
            float hashedValue = 0;
            for (char c : static_cast<std::string>(key))
                hashedValue += static_cast<float>(c);
            return size_t(hashedValue) % _data.size();
        }
    }


public:
    HashTable(size_t capacity) : _size(0), _data(capacity) {}

    HashTable(const HashTable& other) : _data(other._data), _size(other._size) {}

    HashTable& operator=(const HashTable& other) {
        if (this == &other)
            return *this;
        _data = other._data;
        _size = other._size;
        return *this;
    }

    ~HashTable() {
        _data.clear();
        _size = 0;
    }

    size_t size() const {
        return _size;
    }

    size_t capacity() const {
        return _data.size();
    }

    void print() const {
        for (size_t i = 0; i < _data.size(); ++i) {
            std::cout << "Level " << i << ": ";
            for (const auto& pair : _data[i]) {
                std::cout << "{" << pair.key << " : " << pair.value << "} ";
            }
            std::cout << std::endl;
        }
    }

    void insert(const Key& key, const Value& value) {
        size_t index = divisionHash(key);
        _data[index].push_back({ key, value });
        _size++;
    }


    //будет обновлять только первое найденное значение, связанное с ключом key, при коллизии

    void insert_or_assign(const Key& key, const Value& value) {
        size_t index = divisionHash(key);
        for (auto& pair : _data[index]) {
            if (pair.key == key) {
                pair.value = value;
                return;
            }
        }
        _data[index].push_back({ key, value });
        _size++;
    }



    bool contains(const Value& value) const {
        for (const auto& list : _data) {
            for (const auto& pair : list) {
                if (pair.value == value) {
                    return true;
                }
            }
        }
        return false;
    }

    Value* search(const Key& key) {
        size_t index = divisionHash(key);
        for (auto& pair : _data[index]) {
            if (pair.key == key) {
                return &pair.value;
            }
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        size_t index = divisionHash(key);
        auto& bucket = _data[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (it->key== key) {
                bucket.erase(it);
                _size--;
                return true;
            }
        }
        return false;
    }

    size_t count(const Key& key) const {
        size_t index = divisionHash(key);
        size_t count = 0;
        for (const auto& pair : _data[index]) {
            if (pair.key == key) {
                count++;
            }
        }
        return count;
    }


    size_t romanToDecimal(const std::string& roman) {
        HashTable<char, int> _nums(1);
        _nums.insert('I', 1);
        _nums.insert('V', 5);
        _nums.insert('X', 10);
        _nums.insert('L', 50);
        _nums.insert('C', 100);
        _nums.insert('D', 500);
        _nums.insert('M', 1000);

        int result = 0;
        int prevValue = 0;

        for (int i = roman.size() - 1; i >= 0; --i) {
            int curValue = *_nums.search(roman[i]);
            if (curValue < prevValue) {
                result -= curValue;
            }
            else {
                result += curValue;
            }
            prevValue = curValue;
        }

        return result;
        }


};

#endif
