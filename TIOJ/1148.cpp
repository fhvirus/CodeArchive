#include <bits/stdc++.h>
using namespace std;

struct Fraction {
  int64_t a, b;
  Fraction (int64_t u, int64_t v) {
    if (v < 0) u = -u, v = -v;
    int64_t g = gcd(u % v, v);
    a = u / g, b = v / g;
  }
  Fraction (int x) : a(x), b(1) {}
  bool operator < (const Fraction& o) const {
    return a * o.b < o.a * b; };
  bool operator == (const Fraction& o) const {
    return a * o.b == o.a * b; }
};
struct Line { int ax, ay, bx, by; };

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<Line> line(n);
  for (auto &[ax, ay, bx, by] : line) {
    cin >> ax >> ay >> bx >> by;
    if (ax > bx) swap(ax, bx), swap(ay, by);
  }

  vector<tuple<Fraction, int, int>> event;
  for (int i = 0; i < n; ++i) {
    event.emplace_back(Fraction(line[i].ax), INT_MAX, i);
    event.emplace_back(Fraction(line[i].bx), INT_MIN, i);
    for (int j = 0; j < i; ++j) {
      Line u = line[i], v = line[j];
      int64_t a123 = (u.bx - u.ax) * (v.ay - u.ay) - (u.by - u.ay) * (v.ax - u.ax); // u.a.cross(u.b, v.a)
      int64_t a124 = (u.bx - u.ax) * (v.by - u.ay) - (u.by - u.ay) * (v.bx - u.ax); // u.a.cross(u.b, v.b)
      if (a123 == a124) continue;
      Fraction xx(a123 * v.bx - a124 * v.ax, a123 - a124);
      if (not (Fraction(u.ax) < xx) or not (xx < Fraction(u.bx)) or
          not (Fraction(v.ax) < xx) or not (xx < Fraction(v.bx))) continue;
      event.emplace_back(xx, j, i);
    }
  }

  sort(begin(event), end(event));

  vector<int> prv(n + 1, -1), nxt(n + 1, -1);
  prv[n] = nxt[n] = n;

  vector<int> to_swap, need_swap(n + 1);
  const auto reverse = [&](int l, int r) {
    while (l != r) {
      int nl = nxt[l];
      need_swap[l] = 0;
      nxt[prv[l]] = nxt[l], prv[nxt[l]] = prv[l];
      prv[l] = r, nxt[l] = nxt[r];
      nxt[r] = l, prv[nxt[l]] = l;
      l = nl;
    }
    need_swap[r] = 0;
  };
  const auto handle_swap = [&]() {
    for (int i : to_swap) if (need_swap[i]) {
      int l = i, r = i;
      while (need_swap[prv[l]]) l = prv[l];
      while (need_swap[r]) r = nxt[r];
      while (l != r) {
        int nl = l;
        for (int j = 0; j < need_swap[l]; ++j)
          nl = nxt[nl];
        reverse(l, nl);
        l = nxt[l];
      }
    }
    to_swap.clear();
  };
  const auto handle = [&](tuple<Fraction, int, int> ev) {
    auto [xx, i, j] = ev;
    if (i == INT_MIN) {
      prv[nxt[j]] = prv[j];
      nxt[prv[j]] = nxt[j];
      prv[j] = nxt[j] = -1;
    } else if (i == INT_MAX) {
      handle_swap();
      Line a = line[j];
      int p = nxt[n];
      for (; p != n; p = nxt[p]) {
        Line b = line[p];
        int v = (b.bx - b.ax) * (a.ay - b.ay) - (a.ax - b.ax) * (b.by - b.ay);
        if (v < 0) break;
        if (v == 0) {
          int ax = a.bx - a.ax, ay = a.by - a.ay;
          int bx = b.bx - b.ax, by = b.by - b.ay;
          if (ax * by - bx * ay > 0) break;
        }
      }
      nxt[j] = p, prv[j] = prv[p];
      prv[p] = j, nxt[prv[j]] = j;
    } else {
      if (not need_swap[i]) to_swap.push_back(i);
      if (not need_swap[j]) to_swap.push_back(j);
      need_swap[i] += 1;
      need_swap[j] += 1;
    }
  };

  int last_low = n, ans = 0;
  for (int i = 0, j = 0; i < (int) event.size(); i = j) {
    while (j < (int) event.size() and get<0>(event[i]) == get<0>(event[j]))
      handle(event[j++]);
    handle_swap();
    int low = nxt[n];
    if (last_low != low and low != n) ans += 1;
    last_low = low;
  }

  cout << ans << '\n';

  return 0;
}
