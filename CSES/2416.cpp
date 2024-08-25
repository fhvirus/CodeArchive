#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Fenwick {
  vector<ll> val;
  Fenwick(int n) : val(n, 0) {}
  void modify(int p, ll v) {
    for (; p < sz(val); p += p & -p)
      val[p] += v;
  }
  ll query(int p) {
    ll v = 0;
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

  vector<ll> x(n + 2);
  rep (i, 1, n + 1) cin >> x[i];
  x[n + 1] = INT_MAX;

  vector<ll> pre(all(x));
  partial_sum(all(pre), begin(pre));

  vector<vector<pii>> qs(n + 1);
  for (int l, r, i = 0; i < q; ++i) {
    cin >> l >> r;
    qs[l].emplace_back(r, i);
  }

  Fenwick fen(n + 1);
  vector<ll> ans(q);
  vi stk(1, n + 1);

  for (int i = n; i >= 1; --i) {
    while (x[i] >= x[stk.back()]) {
      int j = stk.back(); stk.pop_back();
      fen.modify(j, -x[j] * (stk.back() - j));
    }
    fen.modify(i, x[i] * (stk.back() - i));
    stk.push_back(i);
    for (auto [r, id] : qs[i]) {
      int p = int(lower_bound(all(stk), r, greater<int>()) - begin(stk));
      ans[id] = (fen.query(stk[p] - 1) + x[stk[p]] * (r - stk[p] + 1)) - (pre[r] - pre[i - 1]);
    }
  }

  for (ll i : ans) cout << i << '\n';
}
