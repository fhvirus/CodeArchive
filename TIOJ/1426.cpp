#include <bits/stdc++.h>
#include <cassert>
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
  int size(int u) { return -a[find(u)]; }
};

const int mod = 10007;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int M, N;
  cin >> M >> N;

  assert(1 <= M and M <= 1000);
  assert(1 <= N and N <= 1000);

  int max_id = 0;
  vector a(M, vector<int>(2 * N));
  for (auto &i : a) for (int &j : i) {
    cin >> j;
    assert(1 <= j and j <= 10000);
    max_id = max(max_id, j);
  }

  for (int j = 0; j < 2 * N; ++j) {
    vector<int> t(M);
    for (int i = 0; i < M; ++i)
      t[i] = a[i][j];
    ranges::sort(t);
    assert(ranges::unique(t).begin() == end(t));
  }

  int ans = 1;

  DSU dsu(max_id + 1);
  vector<int> deg(max_id + 1);
  for (int j = 0; j < 2 * N; j += 2) {
    for (int i = 0; i < M; ++i) {
      int u = a[i][j], v = a[i][j + 1];
      ++deg[u], ++deg[v];
      if (not dsu.join(u, v)) ans = ans * (u == v ? 1 : 2) % mod;
    }
    for (int i = 0; i < M; ++i) for (int k : {0, 1}) {
      int u = a[i][j + k];
      if (deg[u] != 1) continue;
      int pu = dsu.find(u);
      if (deg[pu] != -1) {
        ans = ans * dsu.size(pu) % mod;
        deg[pu] = -1;
      }
    }
    for (int i = 0; i < M; ++i) {
      int u = a[i][j], v = a[i][j + 1];
      deg[u] = deg[v] = 0;
      dsu.a[u] = dsu.a[v] = -1;
    }
  }

  cout << ans << '\n';

  return 0;
}
