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
// Each machine is a node of a tree and only knows its parent and children. Nodes talk
// by messages, and a send can fail. Compute the size of the tree.
//
// The root sends "count" down. Each node forwards it to its children; a leaf answers
// its parent with "1". A node that has heard from every child answers its parent with
// 1 + their sizes, and the root's answer is the size of the tree.
//
// Two things go wrong over a network, and each has a guard:
//   - a send fails: retry with exponential backoff, and stop at the first success
//   - a retried send arrives twice: count each child once (pending is a set)
struct Node {
    using Send = function<void(int to, int from, const string& message)>; // throws on failure
    using Sleep = function<void(double seconds)>;

    int id, parent;
    vi children;
    Send send;
    Sleep sleep;
    int retries;
    double delay;
    set<int> pending;
    int size = 1;
    int result = -1; // set on the root once the count finishes

    Node(int id, int parent, vi children, Send send,
         Sleep sleep = [](double s) { this_thread::sleep_for(chrono::duration<double>(s)); },
         int retries = 3, double delay = 0.01)
        : id(id), parent(parent), children(children), send(send), sleep(sleep),
          retries(retries), delay(delay), pending(all(children)) {}

    bool sendWithRetry(int to, const string& message) {
        double wait = delay;
        REP(i, retries) {
            try {
                send(to, id, message);
                return true; // delivered: do not send it again
            } catch (const exception&) {
                sleep(wait);
                wait *= 2;
            }
        }
        return false;
    }

    void start() { // called on the root
        receive(parent, "count");
    }

    void receive(int from, const string& message) {
        if (message == "count") { // from the parent: pass it down
            if (children.empty()) reply();
            for (int c : children) sendWithRetry(c, "count");
            return;
        }
        if (!pending.count(from)) return; // a duplicate, or a stranger
        pending.erase(from);
        size += stoi(message);
        if (pending.empty()) reply();
    }

    void reply() {
        if (parent == -1) result = size;
        else sendWithRetry(parent, to_string(size));
    }
};
