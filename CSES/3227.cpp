#include <bits/stdc++.h>
using namespace std;

struct Line {
  int64_t a, b;
  int64_t operator() (const int64_t x) const { return a * x + b; }
};
struct LiChao {
  int n;
  vector<Line> line;
  explicit LiChao(const int _n) : n(1 << (__lg(max(_n, 2) - 1) + 1)),
  line(2 * n, {0, 0}) {}
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
    l = max(0, l) + n, r = min(r, n) + n;
    for (int h = 0; l < r; l /= 2, r /= 2, ++h) {
      if (l & 1) { add_line(l, (l << h) - n, ((l + 1) << h) - n, seg); ++l; }
      if (r & 1) { --r; add_line(r, (r << h) - n, ((r + 1) << h) - n, seg); }
    }
  }
  int64_t query(int x) {
    int64_t y = 0;
    for (int i = x + n; i > 0; i /= 2)
      y = max(y, line[i](x));
    return y;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  vector<int> lb(n), rb(n), stk;
  for (int i = 0; i < n; ++i) {
    while (not empty(stk) and x[stk.back()] >= x[i]) {
      rb[stk.back()] = i - 1;
      stk.pop_back();
    }
    lb[i] = (empty(stk) ? 0 : stk.back() + 1);
    stk.push_back(i);
  }
  for (int i : stk) rb[i] = n - 1;

  LiChao lichao(n);

  for (int i = 0; i < n; ++i) {
    int l = i - k + 1, r = i;
    int m1 = max(l, lb[i]), m2 = min(r, rb[i] - k + 1);
    if (m1 > m2) swap(m1, m2);
    int64_t u = int64_t(x[i]) * min(rb[i] - lb[i] + 1, k);
    lichao.add_seg(l, m1, {x[i], u - m1 * int64_t(x[i])});
    lichao.add_seg(m1, m2, {0, u});
    lichao.add_seg(m2, r + 1, {-x[i], u - m2 * int64_t(-x[i])});
  }

  for (int i = 0; i <= n - k; ++i)
    cout << lichao.query(i) << " \n"[i == n - k];

  return 0;
}
