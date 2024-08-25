#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Seguki {
  int n;
  vi val;
  Seguki(vi v) : n(sz(v)), val(2 * n) {
    rep (i, 0, n) val[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      val[i] = min(val[i * 2], val[i * 2 + 1]);
  }
  void modify(int p, int v) {
    for (val[p += n] = v; p >>= 1; )
      val[p] = min(val[p * 2], val[p * 2 + 1]);
  }
  int query(int l, int r) {
    int res = INT_MAX;
    for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
      if (l & 1) res = min(res, val[l++]);
      if (r & 1) res = min(res, val[--r]);
    }
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vi x(n);
  for (int &i : x) cin >> i;

  Seguki sgk(x);
  for (int t, a, b; q--; ) {
    cin >> t >> a >> b;
    if (t == 1) sgk.modify(a - 1, b);
    else cout << sgk.query(a - 1, b) << '\n';
  }
}
