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

  Fenwick fa(n + 1), fb(n + 1), fc(n + 1);
  for (int x, i = 1; i <= n; ++i) {
    cin >> x;
    fa.modify(i, x * 2);
  }

  auto query = [&](int p) { return fa.query(p) + fb.query(p) * p + fc.query(p) * p * p; };
  auto modify = [&](int p, ll v, ll t) {
    fa.modify(p, t * (2 * v - p) * (1 - p));
    fb.modify(p, t * (1 + 2 * v - 2 * p));
    fc.modify(p, t);
  };
  for (int t, a, b; q--; ) {
    cin >> t >> a >> b;
    if (t == 1) {
      modify(a, 1, 1);
      modify(b + 1, b + 2 - a, -1);
    } else cout << (query(b) - query(a - 1)) / 2 << '\n';
  }
}
