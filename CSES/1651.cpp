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

  vi x(n + 1);
  rep (i, 1, n + 1) cin >> x[i];

  Fenwick fen(n + 1);
  rep (i, 1, n + 1) fen.modify(i, x[i] - x[i - 1]);

  for (int t, a, b, u, k; q--; ) {
    cin >> t;
    if (t == 1) {
      cin >> a >> b >> u;
      fen.modify(a, u);
      if (b < n) fen.modify(b + 1, -u);
    } else {
      cin >> k;
      cout << fen.query(k) << '\n';
    }
  }
}