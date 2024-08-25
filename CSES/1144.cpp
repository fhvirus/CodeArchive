#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Zaatsu : vi {
  void init() { sort(all()); erase(unique(all()), end()); }
  int operator () (int v) { return int(lower_bound(all(), v) - begin()); }
};

struct Fenwick {
  vi val;
  Fenwick(int n) : val(n, 0) {}
  void modify(int p, int v) {
    for (; p < sz(val); p += p & -p)
      val[p] += v;
  }
  int query(int p) {
    int v = 0;
    for (; p > 0; p -= p & -p)
      v += val[p];
    return v;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vi p(n + 1);
  rep (i, 1, n + 1) cin >> p[i];

  Zaatsu za;
  vector<tuple<char, int, int>> qs(q);
  rep (i, 0, n + 1) za.push_back(p[i]);
  for (auto &[t, a, b] : qs) {
    cin >> t >> a >> b;
    if (t == '!') za.push_back(b);
  }
  
  za.init();
  Fenwick fen(sz(za) + 1);
  rep (i, 1, n + 1) fen.modify(za(p[i]), 1);

  for (auto &[t, a, b] : qs) {
    if (t == '!') {
      fen.modify(za(p[a]), -1);
      p[a] = b;
      fen.modify(za(p[a]), 1);
    } else cout << fen.query(za(b + 1) - 1) - fen.query(za(a) - 1) << '\n';
  }
}
