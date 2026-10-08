#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
using HashFunction = function<int(const T&)>;

// SplitMix64. Folding a seed in makes each row an independent hash.
inline uint64_t mix64(uint64_t x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

// Bucket in [0, width). The same key and seed always map to the same column.
template<typename T>
int hashWithSeed(const T& key, uint64_t seed, int width) {
    uint64_t h = mix64((uint64_t)hash<T>{}(key) ^ (seed + 0x9e3779b97f4a7c15ULL));
    if (width <= 0) return 0;
    return (int)(h % (uint64_t)width);
}

template<typename T>
class CountMinSketch {
private:
    int width, depth;
    vector<uint64_t> seeds;
    vector<vector<int>> hashMatrix;
    vector<HashFunction<T>> hashFunctions;

    static vector<uint64_t> randomSeeds(int d) {
        random_device rd;
        mt19937_64 rng(((uint64_t)rd() << 32) ^ rd());
        vector<uint64_t> s(max(d, 0));
        for (int i = 0; i < d; i++) s[i] = rng();
        return s;
    }

public:
    CountMinSketch(int w, int d) : width(w), depth(d), seeds(randomSeeds(d)) {
        initHashFunctions();
        hashMatrix.assign(depth, vector<int>(width, 0));
    }

    // Pass one seed per row. merge() is valid only when both sketches share these seeds.
    CountMinSketch(int w, int d, vector<uint64_t> hashSeeds)
        : width(w), depth(d), seeds(std::move(hashSeeds)) {
        seeds.resize(depth);
        initHashFunctions();
        hashMatrix.assign(depth, vector<int>(width, 0));
    }

    void initHashFunctions() {
        hashFunctions.clear();
        hashFunctions.reserve(depth);
        for (int r = 0; r < depth; r++) {
            uint64_t seed = seeds[r];
            int w = width;
            hashFunctions.push_back([seed, w](const T& x) {
                return hashWithSeed(x, seed, w);
            });
        }
    }

    void insert(const T& x) {
        for (int r = 0; r < depth; r++) {
            int c = hashFunctions[r](x);
            hashMatrix[r][c] += 1;
        }
    }

    // Estimate is always >= the true frequency (until a counter overflows).
    int count(const T& x) const {
        if (depth == 0) return 0;
        int res = INT_MAX;
        for (int r = 0; r < depth; r++) {
            int c = hashFunctions[r](x);
            res = min(res, hashMatrix[r][c]);
        }
        return res;
    }

    void clear() {
        for (auto& row : hashMatrix) fill(row.begin(), row.end(), 0);
    }

    vector<vector<int>> getMatrix() const { return hashMatrix; }

    // Caller deletes the result. Returns nullptr unless width, depth, and seeds match.
    CountMinSketch* merge(const CountMinSketch* other) const {
        if (!other || other->width != width || other->depth != depth || other->seeds != seeds)
            return nullptr;
        auto* res = new CountMinSketch(width, depth, seeds);
        for (int r = 0; r < depth; r++) {
            for (int c = 0; c < width; c++) {
                res->hashMatrix[r][c] = hashMatrix[r][c] + other->hashMatrix[r][c];
            }
        }
        return res;
    }

    // k candidates with the largest estimates, most frequent first.
    vector<T> topK(int k, const vector<T>& candidates) const {
        priority_queue<pair<int, T>, vector<pair<int, T>>, greater<pair<int, T>>> pq;
        for (auto& x : candidates) {
            pq.push({count(x), x});
            if ((int)pq.size() > k) pq.pop();
        }
        vector<T> res;
        while (!pq.empty()) {
            res.push_back(pq.top().second);
            pq.pop();
        }
        reverse(res.begin(), res.end());
        return res;
    }
};
