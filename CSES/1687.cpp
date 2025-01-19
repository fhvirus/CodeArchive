#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  int l = __lg(n) + 1;

  vector<vi> e(l, vi(n + 1));
  rep (i, 2, n + 1) cin >> e[0][i];
  rep (i, 1, l) rep(j, 1, n + 1)
    e[i][j] = e[i - 1][e[i - 1][j]];

  for (int x, k; q--; ) {
    cin >> x >> k;
    rep (i, 0, l) if (k >> i & 1)
      x = e[i][x];
    cout << (x == 0 ? -1 : x) << '\n';
  }
}
