#pragma once
#include <bits/stdc++.h>
using namespace std;

// TODO (study): Counting iterator
// Section: 1. Numeric
// Status: written and tested, not studied yet
//
// An iterator over the integers lo, lo+1, ..., so the standard library's
// binary searches run over an answer range without building an array:
//   partition_point(counting_iterator(lo), counting_iterator(hi + 1), pred)
// returns the first x in [lo, hi] where pred turns false.

struct counting_iterator {
    using iterator_category = random_access_iterator_tag;
    using value_type = long long;
    using difference_type = long long;
    using pointer = const long long*;
    using reference = long long;

    long long x;
    explicit counting_iterator(long long x = 0) : x(x) {}
    long long operator*() const { return x; }
    long long operator[](long long k) const { return x + k; }
    counting_iterator& operator++() { ++x; return *this; }
    counting_iterator operator++(int) { auto t = *this; ++x; return t; }
    counting_iterator& operator--() { --x; return *this; }
    counting_iterator operator--(int) { auto t = *this; --x; return t; }
    counting_iterator& operator+=(long long k) { x += k; return *this; }
    counting_iterator& operator-=(long long k) { x -= k; return *this; }
    counting_iterator operator+(long long k) const { return counting_iterator(x + k); }
    friend counting_iterator operator+(long long k, counting_iterator it) { return it + k; }
    counting_iterator operator-(long long k) const { return counting_iterator(x - k); }
    long long operator-(const counting_iterator& o) const { return x - o.x; }
    bool operator==(const counting_iterator& o) const { return x == o.x; }
    bool operator!=(const counting_iterator& o) const { return x != o.x; }
    bool operator<(const counting_iterator& o) const { return x < o.x; }
    bool operator>(const counting_iterator& o) const { return x > o.x; }
    bool operator<=(const counting_iterator& o) const { return x <= o.x; }
    bool operator>=(const counting_iterator& o) const { return x >= o.x; }
};
