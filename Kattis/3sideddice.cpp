#include <bits/stdc++.h>
using namespace std;

struct P {
  int64_t x, y;
  P operator - (const P& o) const { return { x - o.x, y - o.y }; }
  bool operator < (const P& o) const { return tie(x, y) < tie(o.x, o.y); }
  int64_t cross(const P& o) const { return x * o.y - y * o.x; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int z;
  vector<P> ps(4);
  while (8e7 /* is strong */) {
    for (auto &[x, y] : ps) {
      cin >> x >> y >> z;
      if (x + y + z == 0) exit(0);
    }
    for (int i = 0; i < 4; ++i) ps[i] = ps[i] - ps[3];

    bool ans = true;
    int64_t area = (ps[1] - ps[0]).cross(ps[2] - ps[0]);
    if (area != 0) {
      if (area < 0) swap(ps[1], ps[2]);
      for (int i = 0; i < 3; ++i)
        ans &= ps[i].cross(ps[(i + 1) % 3]) > 0;
    } else {
      for (int i = 0; i < 3; ++i)
        ans &= ps[i].cross(ps[(i + 1) % 3]) == 0;
      sort(begin(ps), begin(ps) + 3);
      ans &= not ((ps[0] < ps[3]) xor (ps[3] < ps[2]));
    }
    cout << (ans ? "YES\n" : "NO\n"); 
  }

  return 0;
}
