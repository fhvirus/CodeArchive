#include <bits/stdc++.h>
using namespace std;

struct Seguki {
  int n; vector<int> a;
  Seguki(int _n) : n(_n), a(n * 2) {}
  void modify(int p, int v) {
    a[p += n] += v;
    for (p /= 2; p > 0; p /= 2)
      a[p] = min(a[p * 2], a[p * 2 + 1]);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int T;
  cin >> T;
  while (T --> 0) {
    int N;
    cin >> N;

    vector<int> d(N);
    for (int &i : d) cin >> i;

    vector<int> ord(N); iota(begin(ord), end(ord), 0);
    ranges::sort(ord, [&](int u, int v) { return d[u] < d[v]; });

    Seguki sgk(N + 1);
    int64_t ans = LLONG_MAX;
    for (int i = 0, j = 0; i < N; ++i) {
      for (; j < N and sgk.a[1] == 0; ++j) {
        sgk.modify(ord[j], 1);
        sgk.modify(ord[j] + 1, 1);
      }
      if (sgk.a[1] > 0) ans = min(ans, (int64_t) d[ord[j - 1]] - d[ord[i]]);
      sgk.modify(ord[i], -1);
      sgk.modify(ord[i] + 1, -1);
      if (ord[i] == 0 or ord[i] == N - 1) break;
    }

    cout << ans << '\n';
  }

  return 0;
}
