#include <bits/stdc++.h>
using namespace std;

struct QuadRoot {
  int64_t a, b, c;
  double val() const { return ((double)b + (c < 0 ? -sqrt(-c) : sqrt(c))) / (double)a; }
};
template <class T> int sign(T x) { return (x > 0) - (x < 0); }
auto operator <=> (QuadRoot l, QuadRoot r) {
  // (a, b, c) = (2C, C, 5C^2)
  if (l.a < 0) l = {-l.a, -l.b, -l.c};
  if (r.a < 0) r = {-r.a, -r.b, -r.c};
  // (i, q) = (2C^2, 20C^4)
  int64_t li = r.a * l.b, lq2 = r.a * r.a * l.c;
  int64_t ri = l.a * r.b, rq2 = l.a * l.a * r.c;
  // compare li + +-sqrt(lq2) <=> ri + +-sqrt(rq2)
  //      => li - ri <=> +-sqrt(rq2) - +-sqrt(lq2)
  bool flipped = false;
  {
    auto sl = sign(li - ri), sr = sign(rq2 - lq2);
    if (sl != sr) return sl <=> sr;
    if (sl < 0) flipped = not flipped;
  }
  // x in [-40C^4, 16C^4], y in 1600C^8
  __int128 x = (li - ri) * (li - ri) - abs(lq2) - abs(rq2);
  __int128 y = -4 * (__int128)lq2 * (__int128)rq2;
  {
    int sx = sign(x), sy = sign(y);
    if (sx != sy) return flipped ? sy <=> sx : sx <=> sy;
    if (sx < 0) flipped = not flipped;
  }
  x = x * x, y = (y < 0 ? -y : y);
  return flipped ? y <=> x : x <=> y;
}
auto operator == (QuadRoot l, QuadRoot r) { return (l <=> r) == 0; }

struct QuadFormula {
  int64_t a, b, c;
  vector<QuadRoot> sol() const {
    if (a == 0) // if formula = 0, then equivalent to no sol
      return b == 0 ? vector<QuadRoot>() : vector<QuadRoot>{ {b, -c, 0} };
    int64_t d = b * b - 4 * a * c;
    if (d <= 0) return {};
    return { {2 * a, -b, -d}, {2 * a, -b, d} };
  }
  int64_t eval(int64_t t, int64_t s) const { return a * s * s + b * s * t + c * t * t; }
  QuadFormula operator + (const QuadFormula& o) const
  { return { a + o.a, b + o.b, c + o.c }; }
  QuadFormula operator - (const QuadFormula& o) const
  { return { a - o.a, b - o.b, c - o.c }; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q;
  cin >> N >> Q;

  vector<QuadFormula> fs(N);
  for (auto &[a, b, c] : fs)
    cin >> a >> b >> c;
  ranges::sort(fs, [](const auto& a, const auto& b){
    return make_tuple(a.a, -a.b, a.c) > make_tuple(b.a, -b.b, b.c); });

  vector<int> ord(N), pos(N);
  iota(begin(ord), end(ord), 0);
  iota(begin(pos), end(pos), 0);

  vector<tuple<QuadRoot, int, int>> es;
  for (int y, z, k, i = 0; i < Q; ++i) {
    cin >> y >> z >> k;
    es.push_back({{z, y, 0}, ~k, i});
  }
  for (int i = 0; i < N; ++i) for (int j = i + 1; j < N; ++j) {
    auto sols = (fs[ord[i]] - fs[ord[j]]).sol();
    if (empty(sols)) continue;
    es.emplace_back(sols[0], ord[i], ord[j]);
    if (size(sols) > 1)
      es.emplace_back(sols[1], ord[i], ord[j]);
  }

  vector<QuadFormula> sum(N);
  for (int i = 0; i < N; ++i) sum[i] = fs[ord[i]];
  for (int i = 1; i < N; ++i) sum[i] = sum[i] + sum[i - 1];

  const auto swap_ord = [&](int a, int b) {
    sum[pos[a]] = sum[pos[a]] - fs[a] + fs[b];
    swap(ord[pos[a]], ord[pos[b]]);
    swap(pos[a], pos[b]);
  };

  ranges::sort(es);
  vector<pair<int64_t, int64_t>> ans(Q);
  for (int i = 0, j = 0; i < (int)size(es); i = j) {
    j = i;
    if (get<1>(es[i]) < 0) {
      auto [x, a, b] = es[i];
      ans[b] = make_pair(sum[(~a) - 1].eval(x.a, x.b), x.a * x.a);
      j += 1;
    } else {
      vector<pair<int, int>> sw, stk;
      for (; j < (int)size(es) and get<0>(es[j]) == get<0>(es[i]); ++j) {
        auto [jx, ja, jb] = es[j];
        if (pos[ja] > pos[jb]) swap(ja, jb);
        sw.emplace_back(ja, jb);
      }
      ranges::sort(sw, [&](auto a, auto b) {
        return a.first == b.first ?
          pos[a.second] > pos[b.second] : pos[a.first] < pos[b.first]; });
      for (auto p : sw) {
        stk.push_back(p);
        while (not empty(stk)) {
          auto [a, b] = stk.back();
          if (pos[a] + 1 != pos[b]) break;
          stk.pop_back();
          swap_ord(a, b);
        }
      }
    }
  }

  for (auto [s, t] : ans) {
    int64_t g = gcd(abs(s), t);
    cout << s / g << ' ' << t / g << '\n';
  }

  return 0;
}
