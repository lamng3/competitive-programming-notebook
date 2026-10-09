#pragma once
#include <bits/stdc++.h>

using namespace std;

class CuckooFilter {
private:
    static const int BUCKET_SIZE = 4;
    static const int EMPTY = 0;
    int N, MAX_NUM_KICKS;
    vector<array<int, BUCKET_SIZE>> B;

    static size_t hash(const string& key) {
        size_t h = 0;
        for (char c : key) h = h * 31 + c;
        return h;
    }

    static int fingerprint(const string& x) {
        return ((hash(x) * 11400714819323198485ULL) >> 56) % 255 + 1;
    }

public:
    CuckooFilter(int n, int maxNumKicks) : MAX_NUM_KICKS(maxNumKicks) {
        N = 1;
        while (N < n) N *= 2;
        B.resize(N);
    }

    int find(int i, int v) {
        for (int j = 0; j < BUCKET_SIZE; j++) {
            if (B[i][j] == v) return j;
        }
        return -1;
    }

    bool insert(const string& x) {
        int f = fingerprint(x);
        size_t i1 = hash(x) % N;
        size_t i2 = (i1 ^ hash(to_string(f))) % N;
        // if bucket[i1] or bucket[i2] has an empty entry
        // add f to that bucket
        int p1 = find(i1, EMPTY);
        if (p1 != -1) {
            B[i1][p1] = f;
            return true;
        }
        int p2 = find(i2, EMPTY);
        if (p2 != -1) {
            B[i2][p2] = f;
            return true;
        }
        // must relocate existing items
        size_t i = rand() % 2 ? i1 : i2;
        // remember each swap (bucket, entry) to undo on failure
        vector<pair<size_t, int>> kicks;
        // cap the kicks so a cycle can't loop forever
        for (int n = 0; n < MAX_NUM_KICKS; n++) {
            // randomly select an entry e from bucket[i]
            int e = rand() % BUCKET_SIZE;
            // swap f and the fingerprint stored in entry e
            swap(f, B[i][e]);
            kicks.push_back({i, e});
            i = (i ^ hash(to_string(f))) % N;
            // if bucket[i] has an empty entry
            int p = find(i, EMPTY);
            if (p != -1) {
                B[i][p] = f;
                return true;
            }
        }
        // undo the swaps so no existing fingerprint is lost
        for (int k = kicks.size() - 1; k >= 0; k--) {
            swap(f, B[kicks[k].first][kicks[k].second]);
        }
        return false;
    }

    bool lookup(const string& x) {
        int f = fingerprint(x);
        size_t i1 = hash(x) % N;
        size_t i2 = (i1 ^ hash(to_string(f))) % N;
        // if bucket[i1] or bucket[i2] has f
        return find(i1, f) != -1 || find(i2, f) != -1;
    }

    bool remove(const string& x) {
        int f = fingerprint(x);
        size_t i1 = hash(x) % N;
        size_t i2 = (i1 ^ hash(to_string(f))) % N;
        // if bucket[i1] or bucket[i2] has f
        int p1 = find(i1, f);
        if (p1 != -1) {
            B[i1][p1] = EMPTY;
            return true;
        }
        int p2 = find(i2, f);
        if (p2 != -1) {
            B[i2][p2] = EMPTY;
            return true;
        }
        return false;
    }

    // statistics

    double fill_rate() {
        int used = 0;
        for (auto& bucket : B) {
            for (int v : bucket) used += v != EMPTY;
        }
        return (double)used / (N * BUCKET_SIZE);
    }

    double false_positive_rate() {
        // a lookup compares f with up to 2 buckets, each entry matches with prob 1/255
        double entries = 2 * BUCKET_SIZE * fill_rate();
        return 1 - pow(1 - 1.0 / 255, entries);
    }
};
