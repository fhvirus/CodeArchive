#include <bits/stdc++.h>
using namespace std;

struct DSU {
  vector<int> a;
  DSU (int n) : a(n, -1) {}
  int find(int u) { return a[u] < 0 ? u : a[u] = find(a[u]); }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (a[u] > a[v]) swap(u, v);
    return a[u] += exchange(a[v], u), true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int m, n; cin >> m >> n; ) {
    vector dsu(2, DSU(m * n));
    string s, t;
    array<int, 2> ans {m * n, m * n};
    for (int i = 0; i < m; ++i) {
      cin >> t;
      for (int j = 0; j < n; ++j) {
        for (int k : {0, 1}) {
          if (t[j] - '0' <= k) { --ans[k]; continue; }
          if (i > 0) for (int dj : {-1, 0, 1})
            if (0 <= j + dj and j + dj < n)
              ans[k] -= (s[j + dj] - '0' > k and dsu[k].join(i * n + j, (i - 1) * n + j + dj));
          if (j > 0)
            ans[k] -= (t[j - 1] - '0' > k and dsu[k].join(i * n + j, i * n + j - 1));
        }
      }
      s.swap(t);
    }
    cout << ans[0] << ' ' << ans[1] << '\n';
  }

  return 0;
}
