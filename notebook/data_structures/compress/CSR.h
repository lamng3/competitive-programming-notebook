#pragma once
#include <bits/stdc++.h>
using namespace std;

using vi = vector<int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)

#define sz(x) (int)((x).size())

#define pb push_back

template<typename T>
struct CSR {
    int n;
    bool built = false;
    vi offset;
    vi row;
    vector<T> data;

    CSR(int n = 0) : n(n) {}

    // stage entry x into row i; any order, any number of times
    void add(int i, const T& x) {
        assert(0 <= i && i < n && !built);
        row.pb(i);
        data.pb(x);
    }

    // group everything by row in one O(n + nnz) counting sort
    // nnz = number of non zero elements
    void build() {
        assert(!built);
        built = true;
        int m = sz(data);

        offset.assign(n+1, 0);
        for (int i : row) offset[i+1]++; // count entries per row
        FOR(i, 1, n) offset[i] += offset[i-1]; // prefix sums = row starts

        // scatter into each slice
        vi cur = offset;
        vector<T> tmp(m);
        REP(k, m) tmp[cur[row[k]]++] = data[k];
        
        swap(data, tmp);
        row.clear();
    }

    struct range {
        T *first, *last;
        T* begin() const { return first; }
        T* end() const { return last; }
        int size() const { return int(last - first); }
        bool empty() const { return first == last; }
    };

    range operator[](int i) {
        assert(built);
        return range{data.data() + offset[i], data.data() + offset[i+1]};
    }
};
