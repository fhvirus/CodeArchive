#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Fenwick {
  vi val;
  Fenwick(int n) : val(n, 0) {}
  void modify(int p, int v) {
    for (; p < sz(val); p += p & -p)
      val[p] += v;
  }
  int query(int p) {
    int r = 0;
    for (; p > 0; p -= p & -p)
      r += val[p];
    return r;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  map<int, int> mp;
  vi nxt(n + 1), prv(n + 1);
  for (int x, i = 1; i <= n; ++i) {
    cin >> x;
    prv[i] = mp[x];
    nxt[prv[i]] = i;
    mp[x] = i;
  }
  nxt[0] = 0;

  vector<vector<pii>> qs(n + 1);
  for (int l, r, i = 0; i < q; ++i) {
    cin >> l >> r;
    qs[r].emplace_back(l, i);
  }

  Fenwick fen(n + 1);
  vi ans(q);

  for (int r = 1; r <= n; ++r) {
    if (prv[r] != 0) fen.modify(prv[r], -1);
    fen.modify(r, 1);
    for (auto [l, i] : qs[r])
      ans[i] = fen.query(r) - fen.query(l - 1);
  }

  for (int i : ans) cout << i << '\n';
}
