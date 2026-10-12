#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using vi = vector<int>;
using pii = pair<int, int>;

#define REP(i, n) for (int i = 0; i < (n); i++)
#define FOR(i, a, b) for (int i = (a); i <= (b); i++)
#define all(x) (x).begin(), (x).end()
#define sz(x) (int)((x).size())
#define fi first
#define se second
#define pb push_back
// Iterate IPv4 addresses, forwards or backwards, either over a range of two
// addresses or over a CIDR block such as "192.168.1.0/30".
// An address is a 32-bit number written as four bytes, so: parse to an int,
// count, and format back. The iterator never stores the addresses it walks.
class IPv4Iterator {
    ll cur, end;
    int step;
    bool done = false;
public:
    static ll toInt(const string& ip) {
        ll x = 0;
        int parts = 0;
        string run;
        auto flush = [&]() {
            if (run.empty() || sz(run) > 3 || stoi(run) > 255) throw runtime_error("bad address " + ip);
            x = x << 8 | stoi(run);
            parts++;
            run.clear();
        };
        for (char c : ip) {
            if (c == '.') flush();
            else if (isdigit(c)) run += c;
            else throw runtime_error("bad address " + ip);
        }
        flush();
        if (parts != 4) throw runtime_error("bad address " + ip);
        return x;
    }

    static string toStr(ll x) {
        return to_string(x >> 24 & 255) + "." + to_string(x >> 16 & 255) + "." + to_string(x >> 8 & 255) + "." + to_string(x & 255);
    }

    // first and last address of a CIDR block: the top `prefix` bits are fixed
    static pair<ll, ll> cidrRange(const string& block) {
        auto slash = block.find('/');
        if (slash == string::npos) throw runtime_error("bad block " + block);
        int host = 32 - stoi(block.substr(slash + 1));
        if (host < 0 || host > 32) throw runtime_error("bad prefix " + block);
        ll lo = toInt(block.substr(0, slash)) >> host << host; // clear the host bits
        return {lo, lo + (1LL << host) - 1};
    }

    // start .. end inclusive; walks backwards when start > end
    IPv4Iterator(const string& start, const string& end) : cur(toInt(start)), end(toInt(end)) {
        step = cur <= this->end ? 1 : -1;
    }

    static IPv4Iterator fromCidr(const string& block, bool increasing = true) {
        auto [lo, hi] = cidrRange(block);
        return increasing ? IPv4Iterator(toStr(lo), toStr(hi)) : IPv4Iterator(toStr(hi), toStr(lo));
    }

    bool hasNext() {
        return !done;
    }

    string next() {
        if (done) throw out_of_range("no more addresses");
        string ip = toStr(cur);
        if (cur == end) done = true;
        else cur += step;
        return ip;
    }
};
