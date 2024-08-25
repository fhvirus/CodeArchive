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
  Seguki(int _n) : n(_n), val(n * 2) {}
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

  vi p(n);
  for (int &i : p) cin >> i;

  Seguki left(n), right(n);
  rep (i, 0, n) left.modify(i, p[i] - i);
  rep (i, 0, n) right.modify(i, p[i] + i);
  for (int t, k, x; q--; ) {
    cin >> t;
    if (t == 1) {
      cin >> k >> x;
      k -= 1;
      p[k] = x;
      left.modify(k, p[k] - k);
      right.modify(k, p[k] + k);
    } else {
      cin >> k;
      k -= 1;
      cout << min(left.query(0, k) + k, right.query(k, n) - k) << '\n';
    }
  }
}
