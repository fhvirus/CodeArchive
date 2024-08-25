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

  vector<vi> x(1, vi(n));
  for (int &i : x[0]) cin >> i;
  for (int p = 1, k = 1; p * 2 <= sz(x[0]); p *= 2, ++k) {
    x.emplace_back(sz(x[0]) - p * 2 + 1);
    rep (j, 0, sz(x[k]))
      x[k][j] = min(x[k - 1][j], x[k - 1][j + p]);
  }

  for (int a, b; q--; ) {
    cin >> a >> b;
    int d = __lg(b - a + 1);
    cout << min(x[d][a - 1], x[d][b - (1 << d)]) << '\n';
  }
}
