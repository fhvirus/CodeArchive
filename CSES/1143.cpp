#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
 
int bc(int u) { return u <= 1 ? 1 : (2 << __lg(u-1)); }
struct Seguki {
  int n;
  vi val;
  Seguki(vi v) : n(bc(sz(v))), val(2 * n) {
    rep (i, 0, n) val[i + n] = v[i];
    for (int i = n - 1; i > 0; --i)
      val[i] = max(val[i * 2], val[i * 2 + 1]);
  }
  void modify(int p, int v) {
    for (val[p += n] += v; p >>= 1; )
      val[p] = max(val[p * 2], val[p * 2 + 1]);
  }
  int search(int v) {
    if (val[1] < v) return -1;
    int p = 1;
    for (; p < n; p = p * 2 + (val[p * 2] < v));
    return p - n;
  }
};
 
int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
 
  int n, m;
  cin >> n >> m;
 
  vi x(n);
  for (int &i : x) cin >> i;
 
  Seguki sgk(x);
  for (int r, i = 0; i < m; ++i) {
    cin >> r;
    int p = sgk.search(r);
    if (p >= n) p = -1;
    cout << p + 1 << " \n"[i + 1 == m];
    if (p >= 0) sgk.modify(p, -r);
  }
}
