#include <bits/stdc++.h>
using namespace std;

constexpr int64_t INF = std::numeric_limits<int64_t>::max() / 2;
struct Line {
  int64_t a, b;
  int64_t operator() (const int64_t x) const { return a * x + b; }
};
struct LiChao {
  int n;
  vector<Line> line;
  explicit LiChao(const int _n) : n(1 << (__lg(max(_n, 2) - 1) + 1)),
    line(2 * n, {0, -INF}) {}
  void add_line(int u, int lb, int rb, Line l) {
    int mb = (lb + rb) / 2;
    Line& cur = line[u];
    if (l(mb) > cur(mb)) swap(l, cur);
    if (lb + 1 == rb) return;
    if (l(lb) > cur(lb)) add_line(u * 2, lb, mb, l);
    if (l(rb) > cur(rb)) add_line(u * 2 + 1, mb, rb, l);
  }
  void add_line(Line l) { add_line(1, 0, n, l); }
  void add_seg(int l, int r, const Line& seg) {
    l += n, r += n;
    for (int h = 0; l < r; l /= 2, r /= 2, ++h) {
      if (l & 1) { add_line(l, (l << h) - n, ((l + 1) << h) - n, seg); ++l; }
      if (r & 1) { --r; add_line(r, (r << h) - n, ((r + 1) << h) - n, seg); }
    }
  }
  int64_t query(int x) {
    int64_t y = -INF;
    for (int i = x + n; i > 0; i /= 2)
      y = max(y, line[i](x));
    return y;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  const int kN = 100001;

  int n;
  cin >> n;

  LiChao lichao(kN);

  for (int type, a, b, l, r; n --> 0; ) {
    cin >> type >> a;
    if (type == 1) {
      cin >> b >> l >> r;
      lichao.add_seg(l, r + 1, {a, b});
    } else {
      int64_t y = lichao.query(a);
      if (y == -INF) cout << "NO\n";
      else cout << y << '\n';
    }
  }

  return 0;
}
