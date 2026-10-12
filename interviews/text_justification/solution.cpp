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

// 68. Text Justification [Hard]
// Greedy: take words while they fit with one space between them. Then spread
// the leftover spaces: every gap gets the same base, the leftmost gaps one more.
// The last line, and a line with one word, are left-justified instead.
class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        vector<string> ans;
        int i = 0, n = sz(words);
        while (i < n) {
            int j = i + 1, width = sz(words[i]); // line is words[i..j), width counts single spaces
            while (j < n && width + 1 + sz(words[j]) <= maxWidth) {
                width += 1 + sz(words[j]);
                j++;
            }
            int gaps = j - i - 1;
            string line = words[i];
            if (j == n || gaps == 0) {
                for (int k = i + 1; k < j; k++) line += " " + words[k];
                line += string(maxWidth - sz(line), ' ');
            } else {
                int spaces = maxWidth - (width - gaps); // every space on the line
                int base = spaces / gaps, extra = spaces % gaps;
                for (int k = i + 1; k < j; k++) {
                    line += string(base + (k - i - 1 < extra), ' ');
                    line += words[k];
                }
            }
            ans.pb(line);
            i = j;
        }
        return ans;
    }
};
