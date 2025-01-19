#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct AhoCorasick {
  enum { start = 'a', sigma = 26 };
  struct Node {
    array<int, sigma> d;
    int fail;
    Node (int v) { fill(all(d), v); }
  };
  vector<Node> nd;
  vi ord, es;
  AhoCorasick(const vector<string>& pat) : nd(1, -1) {
    for (const string& s : pat) {
      int u = 0;
      for (char c : s) {
        int &v = nd[u].d[c - start];
        if (v == -1) { u = v = sz(nd); nd.emplace_back(-1); }
        else u = v;
      }
      es.push_back(u);
    }
    nd[0].fail = -1;
    ord.push_back(0);
    rep (i, 0, sz(ord)) {
      int u = ord[i], p = nd[u].fail;
      rep (c, 0, sigma) {
        int &v = nd[u].d[c];
        int pv = (p == -1 ? 0 : nd[p].d[c]);
        if (v == -1) v = pv;
        else {
          nd[v].fail = pv;
          ord.push_back(v);
        }
      }
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  int k;
  cin >> k;

  vector<string> pat(k);
  for (string &s : pat) cin >> s;

  AhoCorasick ac(pat);
  vi pos(sz(ac.nd), INT_MAX);
  for (int i = 0, u = 0; i < sz(s); ++i) {
    u = ac.nd[u].d[s[i] - 'a'];
    pos[u] = min(pos[u], i);
  }
  for (int u : ac.ord | views::reverse) if (u) {
    int p = ac.nd[u].fail;
    pos[p] = min(pos[p], pos[u]);
  }

  rep (i, 0, k) {
    int u = ac.es[i];
    cout << (pos[u] == INT_MAX ? -1 : pos[u] - sz(pat[i]) + 2) << '\n';
  }

  return 0;
}
