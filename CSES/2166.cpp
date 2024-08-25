#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
struct Val {
  ll val, sum;
  Val(ll v = 0) : val(v), sum(v) {}
  Val(ll v, ll s) : val(v), sum(s) {}
  Val operator + (const Val &o) const {
    return Val(max(val, sum + o.val), sum + o.sum); }
};
struct Seguki {
  int n;
  vector<Val> val;
  Seguki(int _n) : n(_n), val(n * 2) {}
  void modify(int p, Val v) {
    for (val[p += n] = v; p >>= 1; )
      val[p] = val[p * 2] + val[p * 2 + 1];
  }
  Val query(int l, int r) {
    Val vl, vr;
    for (l += n, r += n; l < r; l /= 2, r /= 2) {
      if (l & 1) vl = vl + val[l++];
      if (r & 1) vr = val[--r] + vr;
    }
    return vl + vr;
  }
};
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
  int n, q;
  cin >> n >> q;

  Seguki sgk(n);
  for (int x, i = 0; i < n; ++i) {
    cin >> x;
    sgk.modify(i, Val(x));
  }

  for (int t, a, b; q--; ) {
    cin >> t >> a >> b;
    if (t == 1)
      sgk.modify(a - 1, Val(b));
    else
      cout << sgk.query(a - 1, b).val << '\n';
  }
}
