#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int64_t n, t, px, py; cin >> n >> t >> px >> py, n != 0; ) {
    bool hit = false;
    for (int64_t x, y, vx, vy, i = 0; i < n; ++i) {
      cin >> x >> y >> vx >> vy;
      int64_t ax = px - x, ay = py - y,
              bx = vx * t, by = vy * t;
      if (ax * by - bx * ay == 0 and -ax * (bx - ax) + -ay * (by - ay) <= 0)
        hit = true;
    }
    cout << boolalpha << hit << '\n';
  }

  return 0;
}
