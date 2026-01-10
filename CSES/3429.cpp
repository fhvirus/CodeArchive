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

  for (int type, a, b; n --> 0; ) {
    cin >> type >> a;
    if (type == 1) {
      cin >> b;
      lichao.add_line({a, b});
    } else cout << lichao.query(a) << '\n';
  }

  return 0;
}
