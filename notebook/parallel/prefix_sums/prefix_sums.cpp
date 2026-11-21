// Prefix sums: out[i] = a[0] + ... + a[i]. Check: cppar prefix_sums --check. Time: cppar prefix_sums.
#include <bits/stdc++.h>
#include <parlay/parallel.h>
#include <parlay/primitives.h>
#include <parlay/sequence.h>
#include <parbench.h>
using namespace std;
using ll = long long;

parlay::sequence<ll> scan_loop(const parlay::sequence<ll>& a) {
    parlay::sequence<ll> out(a.size());
    ll sum = 0;
    for (size_t i = 0; i < a.size(); i++) out[i] = sum += a[i];
    return out;
}

parlay::sequence<ll> scan_hillis_steele(const parlay::sequence<ll>& a) {
    long stride = 1;
    parlay::parallel_for(stride, a.size(), );
    return {};
}

parlay::sequence<ll> scan_blelloch(const parlay::sequence<ll>& a) {
    // TODO
    return {};
}

int main() {
    size_t n = parbench::n(1 << 26);
    auto a = parlay::tabulate(n, [](size_t i) { return ll(parlay::hash64(i) % 101) - 50; });

    parbench::run("loop", [&] { return scan_loop(a); });  // the baseline
    parbench::run("hillis-steele", [&] { return scan_hillis_steele(a); });
    parbench::run("blelloch", [&] { return scan_blelloch(a); });
}
