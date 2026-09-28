#include <bits/stdc++.h>

#include "eviction_cache.h"
#include "lru.h"
#include "fifo.h"
#include "lru-2q.h"

using namespace std;

using Factory = function<unique_ptr<EvictionCache>(int)>;

static vector<pair<string, Factory>> policies() {
    return {
        {"LRU",  [](int cap) { return make_unique<LRUCache>(cap); }},
        {"FIFO", [](int cap) { return make_unique<FIFOCache>(cap); }},
        {"LRU-2Q", [](int cap) {
            int a1in = max(1, cap / 4);
            return make_unique<LRU2QCache>(cap - a1in, a1in, cap);
        }},
        // {"LRU-K",  [](int cap) { return make_unique<LRUKCache>(cap, 2); }},
        // {"LFU",    [](int cap) { return make_unique<LFUCache>(cap); }},
    };
}

struct Bench {
    string name;
    int capacity;
    vector<int> trace;
};

struct Result {
    long long hits = 0;
    long long cold = 0;
    long long readmit = 0;
    double ms = 0;
};

static vector<int> genZipf(int n, int keyspace, double s, unsigned seed) {
    vector<double> cdf(keyspace);
    double sum = 0;
    for (int i = 0; i < keyspace; i++) { sum += 1.0 / pow(i + 1, s); cdf[i] = sum; }
    for (double& c : cdf) c /= sum;
    mt19937 rng(seed);
    uniform_real_distribution<> u(0, 1);
    vector<int> trace(n);
    for (int& k : trace)
        k = lower_bound(cdf.begin(), cdf.end(), u(rng)) - cdf.begin();
    return trace;
}

static vector<int> genHotScan(int n, int hotSize, double hotShare, unsigned seed) {
    mt19937 rng(seed);
    uniform_real_distribution<> u(0, 1);
    uniform_int_distribution<> hot(0, hotSize - 1);
    int scanKey = hotSize;
    vector<int> trace(n);
    for (int& k : trace)
        k = (u(rng) < hotShare) ? hot(rng) : scanKey++;
    return trace;
}

static Result benchmark(const Factory& make, const Bench& b) {
    auto cache = make(b.capacity);
    unordered_set<int> seen;
    Result r;
    auto t0 = chrono::steady_clock::now();
    for (int k : b.trace) {
        if (cache->get(k).valid) {
            r.hits++;
        } else {
            if (seen.insert(k).second) r.cold++;
            else r.readmit++;
            cache->put(k, k);
        }
    }
    auto t1 = chrono::steady_clock::now();
    r.ms = chrono::duration<double, milli>(t1 - t0).count();
    return r;
}

static vector<Bench> benches() {
    return {
        {"zipf-0.8",  1024, genZipf(200000, 8192, 0.8, 1)},
        {"zipf-1.0",  1024, genZipf(200000, 8192, 1.0, 2)},
        {"scan+hot",  1024, genHotScan(200000, 600, 0.35, 3)},
    };
}

static void header(const Bench& b) {
    cout << "==== " << b.name
         << " (cap=" << b.capacity
         << " accesses=" << b.trace.size() << ") ====\n";
    cout << left << setw(10) << "policy"
         << right << setw(11) << "hits"
         << setw(11) << "cold"
         << setw(11) << "readmit"
         << setw(9) << "hit%"
         << setw(10) << "ops/ms" << "\n";
}

static void row(const string& policy, const Result& r) {
    long long total = r.hits + r.cold + r.readmit;
    double hitRate = total ? 100.0 * r.hits / total : 0.0;
    double thrpt = r.ms > 0 ? total / r.ms : 0.0;
    cout << left << setw(10) << policy
         << right << setw(11) << r.hits
         << setw(11) << r.cold
         << setw(11) << r.readmit
         << setw(9) << fixed << setprecision(2) << hitRate
         << setw(10) << setprecision(0) << thrpt << "\n";
}

int main() {
    auto facs = policies();
    for (const Bench& b : benches()) {
        header(b);
        for (auto& [pname, make] : facs) row(pname, benchmark(make, b));
        cout << "\n";
    }
    return 0;
}
