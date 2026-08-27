#include <bits/stdc++.h>
using namespace std;

struct AhoCorasick {
  enum { kC = 4, kA = 'a' };
  struct Node {
    int f, cnt, len, to[kC];
    Node(int v) : cnt(0), len(0) { ranges::fill(to, v); }
  };
  vector<Node> nd;
  vector<int> ord;
  void insert(const string& s) {
    int u = 0;
    for (char c : s) {
      int &v = nd[u].to[c - kA];
      if (v == -1) { u = v = (int)size(nd); nd.emplace_back(-1); }
      else u = v;
    }
    nd[u].cnt += 1;
  }
  AhoCorasick(const vector<string>& pats) : nd(1, -1) {
    for (const auto& s : pats) insert(s);
    nd[0].f = (int)size(nd);
    nd.emplace_back(0);
    ord.push_back(0);
    for (int i = 0; i < (int)size(ord); ++i) {
      int u = ord[i], pre = nd[u].f;
      for (int c = 0; c < kC; ++c) {
        int &v = nd[u].to[c], y = nd[pre].to[c];
        if (v == -1) v = y;
        else nd[v].f = y, nd[v].len = nd[u].len + 1, ord.push_back(v);
      }
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int mod = 10007;
  const auto mad = [&](int &u, int v) {
    u += v;
    if (u >= mod) u -= mod;
  };

  string start;
  cin >> start;

  int p, n;
  cin >> p >> n;

  vector<string> bad(n);
  for (auto &i : bad) cin >> i;
  AhoCorasick ac(bad);

  const int s = (int)size(ac.nd), max_l = min(100, (int)size(start) + p);

  vector<bool> is_bad(s);
  for (int i : ac.ord)
    if (is_bad[ac.nd[i].f] or ac.nd[i].cnt != 0)
      is_bad[i] = true;

  int su = 0;
  for (char c : start) {
    su = ac.nd[su].to[c - 'a'];
    if (is_bad[su]) {
      cout << "0 1\n";
      exit(0);
    }
  }

  int dead = 0, sjuk = 0;
  vector sc(s, vector(max_l + 1, 0)), dp = sc;
  sc[su][size(start)] = 1;
  for (int t = 0; t < p; ++t) {
    for (auto &i : dp) ranges::fill(i, 0);
    for (int i = 0; i < s; ++i) if (ac.nd[i].cnt == 0) {
      for (int j = 1; j <= max_l; ++j) if (sc[i][j] != 0) {
        for (int c : {0, 1, 2, 3}) {
          int v = ac.nd[i].to[c];
          mad(is_bad[v] ? sjuk : dp[v][j + 1], sc[i][j]);
        }
        int v = (j == ac.nd[i].len ? ac.nd[i].f : i);
        mad(j == 1 ? dead : dp[v][j - 1], sc[i][j]);
      }
    }
    swap(dp, sc);
  }

  cout << dead << ' ' << sjuk << '\n';

  return 0;
}
