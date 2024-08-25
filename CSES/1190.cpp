#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int bc(int u) { return u <= 1 ? 1 : (2 << __lg(u-1)); }
struct Val {
  ll val, pre, suf, sum;
  Val(ll v = 0) : val(v), pre(v), suf(v), sum(v) {}
  Val(ll v, ll p, ll s, ll t) : val(v), pre(p), suf(s), sum(t) {}
  Val operator + (const Val &o) const {
    return Val(max({val, o.val, suf + o.pre}),
        max(pre, sum + o.pre), max(o.suf, suf + o.sum), sum + o.sum); }
};
struct Seguki {
  int n;
  vector<Val> val;
  Seguki(int _n) : n(bc(_n)), val(n * 2) {}
  void modify(int p, Val v) {
    for (val[p += n] = v; p >>= 1; )
      val[p] = val[p * 2] + val[p * 2 + 1];
  }
};
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
  int n, m;
  cin >> n >> m;

  Seguki sgk(n);
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    sgk.modify(i, Val(x));
  }

  for (int k, x; m--; ) {
    cin >> k >> x;
    sgk.modify(k - 1, Val(x));
    cout << max(sgk.val[1].val, 0ll) << '\n';
  }
}
