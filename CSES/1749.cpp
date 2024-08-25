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
  int search(int v) {
    int p = 0;
    for (int l = (1 << __lg(sz(val))); l > 0; l >>= 1)
      if (p + l < sz(val) and v > val[p + l]) v -= val[p += l];
    return p + 1;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vi x(n + 1);
  rep (i, 1, n + 1) cin >> x[i];

  Fenwick fen(n + 1);
  rep (i, 1, n + 1) fen.modify(i, 1);

  for (int p, i = 0; i < n; ++i) {
    cin >> p;
    p = fen.search(p);
    cout << x[p] << " \n"[i + 1 == n];
    fen.modify(p, -1);
  }
}
