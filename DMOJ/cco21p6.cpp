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
    x[i] = b < i ? b - i : b - i - N;
  }

  FenwickTree<int> ft(N * 3);
  int64_t no_x = 0;
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
    int64_t l_no_x = ft.query(i + x[i] + N);
    int64_t r_no_x = (N - i - 1) - (ft.query(N * 3 - 1) - ft.query((i + x[i] + N) + N));
    int64_t no_x_i = l_no_x + r_no_x;
    no_x = no_x - no_x_i + (N - 1 - no_x_i);
    max_no_x = max(max_no_x, no_x);

    ft.modify((i + x[i] + N) + N, 1);
  }

  cout << (int64_t) N * (N - 1) / 2 - max_no_x << '\n';

  return 0;
}
