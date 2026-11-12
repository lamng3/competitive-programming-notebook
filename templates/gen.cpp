// Random test generator for cpdiff. Prints one test to stdout.
// cpdiff runs it as ./gen <seed>, so a failing test can be replayed with the same seed.
// Keep tests small: a 5-element counterexample is easier to debug than a 10^5 one.
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

mt19937_64 rng;

// uniform integer in [l, r]
ll rnd(ll l, ll r) { return uniform_int_distribution<ll>(l, r)(rng); }

// uniform real in [l, r)
double rndf(double l, double r) { return uniform_real_distribution<double>(l, r)(rng); }

// n integers in [l, r]
vector<ll> rnd_vec(int n, ll l, ll r) {
    vector<ll> a(n);
    for (auto& x : a) x = rnd(l, r);
    return a;
}

// a random permutation of 1..n
vector<int> rnd_perm(int n) {
    vector<int> p(n);
    iota(p.begin(), p.end(), 1);
    shuffle(p.begin(), p.end(), rng);
    return p;
}

// string of length n over the characters in alphabet
string rnd_str(int n, const string& alphabet = "ab") {
    string s(n, ' ');
    for (auto& c : s) c = alphabet[rnd(0, (ll)alphabet.size() - 1)];
    return s;
}

// edges of a random tree on vertices 1..n, relabelled so vertex 1 is not always the root
vector<pair<int, int>> rnd_tree(int n) {
    vector<int> id = rnd_perm(n);
    vector<pair<int, int>> e;
    for (int v = 2; v <= n; v++) e.push_back({id[rnd(1, v - 1) - 1], id[v - 1]});
    shuffle(e.begin(), e.end(), rng);
    return e;
}

template<class T>
void print_vec(const vector<T>& a) {
    for (int i = 0; i < (int)a.size(); i++) cout << a[i] << " \n"[i + 1 == (int)a.size()];
    if (a.empty()) cout << '\n';
}

void gen_test() {
    int n = rnd(1, 8);
    cout << n << '\n';
    print_vec(rnd_vec(n, 1, 10));
}

int main(int argc, char** argv) {
    rng.seed(argc > 1 ? stoull(argv[1]) : chrono::steady_clock::now().time_since_epoch().count());
    int tt = 1;  // set tt = rnd(1, 3) and print it when the problem has multiple test cases
    // cout << tt << '\n';
    while (tt--) gen_test();
    return 0;
}
