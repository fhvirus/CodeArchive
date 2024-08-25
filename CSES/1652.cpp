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

  vector<vi> a(n + 1, vi(n + 1, 0));
  rep (i, 1, n + 1) {
    string s; cin >> s;
    rep (j, 1, n + 1)
      a[i][j] = a[i - 1][j] + (s[j - 1] == '*');
  }
  rep (i, 1, n + 1) partial_sum(all(a[i]), begin(a[i]));

  for (int y1, x1, y2, x2; q--; ) {
    cin >> y1 >> x1 >> y2 >> x2;
    cout << a[y2][x2] - a[y2][x1 - 1] - a[y1 - 1][x2] + a[y1 - 1][x1 - 1] << '\n';
  }
}
