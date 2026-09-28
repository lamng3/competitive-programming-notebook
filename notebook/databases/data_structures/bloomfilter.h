#pragma once
#include <bits/stdc++.h>

using namespace std;

using HashFunction = function<size_t(const string&)>;

class BloomFilter {
private:
    int bit_size;
    vector<bool> bits;
    vector<HashFunction> hash_funcs;

    // polynomial rolling hash, base 31
    static size_t hash1(const string& key) {
        size_t h = 0;
        for (char c : key) h = h * 31 + c;
        return h;
    }

    // DJB2
    static size_t hash2(const string& key) {
        size_t h = 5381;
        for (char c : key) h = h * 33 + c;
        return h;
    }

public:
    BloomFilter(int m) {
        bit_size = m;
        bits.resize(bit_size, false);
        hash_funcs = {hash1, hash2};
    }

    void add(const string& key) {
        for (auto& hash_func : hash_funcs) {
            bits[hash_func(key)%bit_size] = true;
        }
    }

    bool contains(const string& key) {
        for (auto& hash_func : hash_funcs) {
            if (!bits[hash_func(key)%bit_size]) return false;
        }
        return true;
    }

    void clear() {
        fill(bits.begin(), bits.end(), false);
    }
};
