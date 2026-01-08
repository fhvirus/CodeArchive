#include <bits/stdc++.h>
using namespace std;

const int kC = 1'000'001;
struct P {
  int x, y;
  auto operator <=> (const P&) const = default;
};
using Pts = vector<P>;

void add_ud(Pts& d, Pts& u, P p, int y) {
  if (p.y < y and (empty(d) or d.back().y < p.y))
    d.push_back(p);
  if (p.y > y and (empty(u) or u.back().y > p.y))
    u.push_back(p);
}
int count_bad(Pts& ld, Pts& lu, Pts& rd, Pts& ru, int dir) {
  int delta = 0;
  for (int j = 0, plu = -1, prd = 0, qh = 0, qt = 0; j < size(ld); ++j) {
    while (plu + 1 < size(lu) and lu[plu + 1].x > ld[j].x) ++plu;
    while (prd < size(rd) and rd[prd].y * dir < ld[j].y * dir) ++prd;
    int yb = (plu < 0 ? kC * dir : lu[plu].y);
    int rb = (prd >= size(rd) ? kC : rd[prd].x);
    while (qt < size(ru) and ru[qt].x < rb) ++qt;
    while (qh < qt and ru[qh].y * dir > yb * dir) ++qh;
    delta += qt - qh;
  }
  return delta;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  Pts pts(n);
  for (auto &[x, y] : pts) cin >> x >> y;

  int tot = 0;
  int64_t ans[2] {0, 0};
  for (int i = 0; i < n; ++i) {
    int pos = i;
    for (; pos > 0 and pts[pos - 1] > pts[pos]; --pos)
      swap(pts[pos], pts[pos - 1]);

    Pts ld, lu, rd, ru;
    for (int j = pos - 1; j >= 0; --j) add_ud(ld, lu, pts[j], pts[pos].y);
    for (int j = pos + 1; j <= i; ++j) add_ud(rd, ru, pts[j], pts[pos].y);

    tot += size(ld) + size(lu) + size(rd) + size(ru);
    tot -= count_bad(ld, lu, rd, ru, 1) + count_bad(lu, ld, ru, rd, -1);
    ans[i & 1] += tot;
  }

  cout << ans[0] << ' ' << ans[1] << '\n';

  return 0;
}
