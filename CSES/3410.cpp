#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int INF = INT_MAX / 2;

  int n;
  cin >> n;

  int64_t lb = INF, rb = -INF, db = INF, ub = -INF;
  for (int64_t x, y; n --> 0; ) {
    cin >> x >> y;
    tie(x, y) = make_pair(x + y, x - y);
    lb = min(lb, x), rb = max(rb, x);
    db = min(db, y), ub = max(ub, y);
    cout << max(rb - lb, ub - db) << '\n';
  }

  return 0;
}
