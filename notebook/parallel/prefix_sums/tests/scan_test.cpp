// Build & run from tests/, once ParlayLib is in third_party/ (see notebook/parallel/README.md):
//   g++ -std=c++17 -fsanitize=address,undefined -Wall -I../../../../third_party/parlaylib/include scan_test.cpp -o /tmp/t && /tmp/t
// For data races, build with -fsanitize=thread instead.
#include "../HillisSteeleScan.h"
#include "../BlellochScan.h"
#include "../BlockedScan.h"

using ll = long long;
const ll UNTOUCHED = LLONG_MIN + 7;

// "" if the scan is right on this input, "not written yet" if it left out
// as it was, or else the first wrong element.
string check(const function<void(const ll*, ll*, size_t)>& scan, size_t n, uint64_t seed) {
    mt19937_64 rng(seed);
    vector<ll> in(n), out(n, UNTOUCHED), want(n);
    for (ll& x : in) x = ll(rng() % 101) - 50;
    partial_sum(in.begin(), in.end(), want.begin());
    scan(in.data(), out.data(), n);
    if (n > 0 && all_of(out.begin(), out.end(), [](ll x) { return x == UNTOUCHED; })) return "not written yet";
    for (size_t i = 0; i < n; i++)
        if (out[i] != want[i])
            return "n = " + to_string(n) + ": out[" + to_string(i) + "] is " + to_string(out[i]) +
                   ", expected " + to_string(want[i]);
    return "";
}

int main() {
    // Small sizes first, odd ones included; 0 last, since an empty output
    // can't show whether the scan was written.
    vector<size_t> sizes = {1, 2, 3, 4, 5, 7, 8, 9, 16, 17, 100, 1000, 1023, 1024, 4097, 65536, 100003, 1 << 20, 0};
    struct Scan { const char* name; function<void(const ll*, ll*, size_t)> run; };
    vector<Scan> scans = {
        {"scan_hillis_steele", [](const ll* in, ll* out, size_t n) { vector<ll> tmp(n); scan_hillis_steele(in, out, tmp.data(), n); }},
        {"scan_blelloch", [](const ll* in, ll* out, size_t n) { scan_blelloch(in, out, n); }},
        {"scan_blocked", [](const ll* in, ll* out, size_t n) { scan_blocked(in, out, n); }},
    };

    int failed = 0, not_written = 0;
    for (auto& s : scans) {
        string problem;
        for (size_t n : sizes) {
            for (uint64_t seed = 0; seed < 3 && problem.empty(); seed++) problem = check(s.run, n, seed);
            if (!problem.empty()) break;
        }
        if (problem.empty()) printf("%-20s pass\n", s.name);
        else if (problem == "not written yet") printf("%-20s not written yet\n", s.name), not_written++;
        else printf("%-20s FAIL  %s\n", s.name, problem.c_str()), failed++;
    }
    printf("\n%d failed, %d not written yet.\n", failed, not_written);
    return failed || not_written ? 1 : 0;
}
