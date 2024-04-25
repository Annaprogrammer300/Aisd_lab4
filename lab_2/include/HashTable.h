#ifndef LAB2_INCLUDE_HASHTABLE_H
#define LAB2_INCLUDE_HASHTABLE_H

#include <iostream>
#include <vector>
#include <list>
#include <functional>

template <typename Key, typename Value, typename Hash = std::hash<Key>, typename Comp_key = std::equal_to<Key>, typename Comp_value = std::equal_to<Value>>
class HashTable {
    struct Pair {
        Key key;
        Value value;
    };

    std::vector<std::list<Pair>> _data;
    size_t _size;
    Hash hash_func;
    Comp_key comparator_key;
    Comp_value comparator_value;

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
        size_t index = hash_func(key) % _data.size();
        for (auto& pair : _data[index]) {
            if (comparator_key(pair.key, key)) {
                _data[index].push_back({ key, value });  // ��������� ����� ���� ����-�������� � ��������� ������
                _size++;
                return;
            }
        }
        _data[index].push_back({ key, value });  // ���� ���� �� ����������, ��������� ����� ���� ����-�������� � ��������� ������
        _size++;
    }

    void insert_or_assign(const Key& key, const Value& value) {
        size_t index = hash_func(key) % _data.size();
        for (auto& pair : _data[index]) {
            if (comparator_key(pair.key, key)) {
                pair.value = value;
                return;
            }
        }
        _data[index].push_back({ key, value });
        _size++;
    }

    bool contains(const Key& key) const {
        size_t index = hash_func(key) % _data.size();
        for (const auto& pair : _data[index]) {
            if (comparator_key(pair.key, key)) {
                return true;
            }
        }
        return false;
    }

    Value* search(const Key& key) {
        size_t index = hash_func(key) % _data.size();
        for (auto& pair : _data[index]) {
            if (comparator_key(pair.key, key)) {
                return &pair.value;
            }
        }
        return nullptr;
    }

    bool erase(const Key& key) {
        size_t index = hash_func(key) % _data.size();
        auto& bucket = _data[index];
        for (auto it = bucket.begin(); it != bucket.end(); ++it) {
            if (comparator_key(it->key, key)) {
                bucket.erase(it);
                _size--;
                return true;
            }
        }
        return false;
    }

    int count(const Key& key) const {
        size_t index = hash_func(key) % _data.size();
        int count = 0;
        for (const auto& pair : _data[index]) {
            if (comparator_key(pair.key, key)) {
                count++;
            }
        }
        return count;
    }


    int romanToDecimal(const std::string& roman) {
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
