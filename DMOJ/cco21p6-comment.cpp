#include <bits/stdc++.h>
using namespace std;

template <class T>
struct FenwickTree {
  int n;
  vector<T> a;
  FenwickTree(int _n) : n(_n), a(n) {}
  void modify(int p, T d) { for (; p < n; p |= (p + 1)) a[p] += d; }
  T query(int p) {
    T r = 0;
    for (; p > 0; p &= (p - 1)) r += a[p-1];
    return r;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, L;
  cin >> N >> L;

  vector<pair<int, int>> ps(N);
  vector<int> bs;
  for (auto &[a, b] : ps) {
    cin >> a >> b;
    bs.push_back(b);
  }

  ranges::sort(ps);
  ranges::sort(bs);

  vector<int> x(N);
  for (int i = 0; i < N; ++i) {
    auto &[_, b] = ps[i];
    b = (int) (ranges::lower_bound(bs, b) - begin(bs));
    x[i] = b - i;
    if (x[i] > 0) x[i] -= N;
  }

  // reduce to Thm 3.9 from https://doi.org/10.1016/0304-3975(85)90047-7
  //
  // Let p be a permutation, we want to reverse-sort p in to I = [0...N-1]
  // by moving number i x[i] moves (negative means to the left).
  //
  // We have i + x[i] = p[i], and for a fixed sum of x, 
  // thm 3.9 states that x* is optimal <=> max(x*) - min(x*) <= N.
  // Besides, x[i] is either p[i] - i, or p[i] - i +- N (whichever is in (-N, N))
  //
  // But the problem allow to sort p in to any rotation of I,
  // which means instead of sum(x) = 0, we can have sum(x) = k * N for some k's.
  // (rigorous proof needed)
  //
  // So, we iterate from the minimum k (all pick smallest x[i]),
  // and for each turn, add N to x[i] for some i.
  // This always yields a feasible solution.
  // By Thm 3.9, max(x*) - min(x*) must <= N,
  // so flipping anyone whose not max nor min violates it.
  //
  // By some more reasoning, one can see that
  // x* only flips some prefix of i sorted by non-decreasing order of x[i]

  FenwickTree<int> ft(N * 3);
  int64_t no_x = 0; // no_cross is too long
  for (int i = 0; i < N; ++i) {
    no_x += ft.query(i + x[i] + N);
    if (i + x[i] >= 0) no_x -= ft.query((i + x[i] + N) - N);
    ft.modify(i + x[i] + N, 1);
  }

  vector<int> ord(N); iota(begin(ord), end(ord), 0);
  ranges::sort(ord, [&](int u, int v) { return x[u] < x[v]; });

  int64_t max_no_x = no_x;
  for (int i : ord) {
    ft.modify(i + x[i] + N, -1);
    // because we're flipping in order of x[i] (most negative first),
    // through careful analysis we can find that:
    // (1) for unflipped j < i, x[j] > x[i], so j can never wrap around and cross i;
    // (2) for flipped j < i, abs(N + x[j]) < abs(x[i]), so j can never cross i twice;
    int64_t l_no_x = ft.query(i + x[i] + N);
    // (3) for unflipped j > i, similar to (1), i cross j only if i's path include j's;
    // (4) for flipped j > i, maybe obvious
    int64_t r_no_x = (N - i - 1) - (ft.query(N * 3 - 1) - ft.query((i + x[i] + N) + N));
    int64_t no_x_i = l_no_x + r_no_x;
    // small lemma: when flipping, cross <-> no cross switches.
    no_x = no_x - no_x_i + (N - 1 - no_x_i);
    max_no_x = max(max_no_x, no_x);

    ft.modify((i + x[i] + N) + N, 1);
  }

  cout << (int64_t) N * (N - 1) / 2 - max_no_x << '\n';

  return 0;
}
