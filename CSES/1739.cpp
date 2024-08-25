#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Fenwick2D {
  vector<vi> val;
  Fenwick2D(int n) : val(n, vi(n, 0)) {}
  void modify(int x, int y, int v) {
    for (; x < sz(val); x += x & -x)
      for (int p = y; p < sz(val); p += p & -p)
        val[x][p] += v;
  }
  int query(int x, int y) {
    int v = 0;
    for (; x > 0; x -= x & -x)
      for (int p = y; p > 0; p -= p & -p)
        v += val[x][p];
    return v;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  Fenwick2D fen(n + 1);

  vector<string> a(n + 1);
  rep (i, 1, n + 1) {
    cin >> a[i];
    a[i] = ' ' + a[i];
    rep (j, 1, n + 1)
      if (a[i][j] == '*') fen.modify(i, j, 1);
  }

  for (int t, y1, x1, y2, x2; q--; ) {
    cin >> t;
    if (t == 1) {
      cin >> y1 >> x1;
      fen.modify(y1, x1, a[y1][x1] == '*' ? -1 : 1);
      a[y1][x1] = "*."[a[y1][x1] == '*'];
    } else {
      cin >> y1 >> x1 >> y2 >> x2;
      cout << fen.query(y2, x2) - fen.query(y2, x1 - 1)
         - fen.query(y1 - 1, x2) + fen.query(y1 - 1, x1 - 1) << '\n';
    }
  }
}
