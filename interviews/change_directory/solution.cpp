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
// cd(pwd, path, links): the absolute directory after `cd path` from pwd, where links
// maps an absolute directory to the absolute directory it points at (a symlink).
//   - path may be absolute ("/a/b") or relative ("../c"); "" stays in pwd
//   - "." stays, ".." goes up (and stays at "/" from the root)
//   - after every step, the path so far is resolved through links, so a link in the
//     middle of the path is followed before the next name is applied
//   - a chain of links that loops throws, like ELOOP from a real shell
struct ChangeDirectory {
    static vector<string> split(const string& path) {
        vector<string> names;
        string run;
        for (char c : path) {
            if (c != '/') run += c;
            else if (!run.empty()) names.pb(run), run.clear();
        }
        if (!run.empty()) names.pb(run);
        return names;
    }

    static string join(const vector<string>& st) {
        string s;
        for (auto& name : st) s += "/" + name;
        return s.empty() ? "/" : s;
    }

    static string resolve(string path, const unordered_map<string, string>& links) {
        unordered_set<string> seen;
        while (links.count(path)) {
            if (!seen.insert(path).se) throw runtime_error("symlink loop at " + path);
            path = links.at(path);
        }
        return path;
    }

    static string cd(const string& pwd, const string& path, const unordered_map<string, string>& links = {}) {
        vector<string> st = (!path.empty() && path[0] == '/') ? vector<string>{} : split(pwd);
        for (auto& name : split(path)) {
            if (name == ".") continue;
            if (name == "..") {
                if (!st.empty()) st.pop_back();
                continue;
            }
            st.pb(name);
            string cur = join(st), target = resolve(cur, links);
            if (target != cur) st = split(target);
        }
        return join(st);
    }
};
