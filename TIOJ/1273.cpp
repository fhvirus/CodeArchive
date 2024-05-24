#ifdef OWO
#include <cstdio>
int DistanceSum(int, int[], int[]);
int main() {
  const int kN = 100001;
  int N, X[kN], Y[kN];
  scanf("%d", &N);
  for (int i = 0; i < N; ++i)
    scanf("%d%d", X + i, Y + i);
  printf("%d\n", DistanceSum(N, X, Y));
}
#else
#include "lib1273.h"
#endif

#include <algorithm>
#include <numeric>
#include <utility>

const int kN = 100001;
const int kMod = 1'000'000'000;
std::pair<int, int> ps[kN];
int id[kN];

int f[kN];
int find(int u) { return f[u] < 0 ? u : f[u] = find(f[u]); }

long long dfs(int u, int p, int N, std::vector<std::vector<int>> &adj) {
  long long res = 0;
  std::sort(adj[u].begin(), adj[u].end());
  adj[u].erase(std::unique(adj[u].begin(), adj[u].end()), adj[u].end());
  for (int v : adj[u]) if (v != p) {
    res += dfs(v, u, N, adj);
    f[u] += f[v];
  }
  return res + 1ll * (N + f[u]) * -f[u];
}

int DistanceSum(int N, int X[], int Y[]) {
  int ans = 0;
  for (int _ = 0; _ < 2; ++_) {
    for (int i = 0; i < N; ++i)
      ps[i].first = X[i], ps[i].second = Y[i];
    std::sort(ps, ps + N);

    std::fill(f, f + N, -1);
    for (int i = 1; i < N; ++i) {
      if (ps[i - 1].first == ps[i].first and ps[i - 1].second == ps[i].second - 1) {
        int u = find(i - 1), v = find(i);
        if (u != v) {
          f[u] += f[v];
          f[v] = u;
        }
      }
    }

    std::iota(id, id + N, 0);
    std::sort(id, id + N, [](int a, int b) {
      return ps[a].second == ps[b].second ? ps[a].first < ps[b].first : ps[a].second < ps[b].second; });

    std::vector<std::vector<int>> adj(N);

    for (int i = 1; i < N; ++i) {
      int u = id[i - 1], v = id[i];
      if (ps[u].second == ps[v].second and ps[u].first == ps[v].first - 1) {
        u = find(u), v = find(v);
        adj[u].push_back(v);
        adj[v].push_back(u);
      }
    }

    ans = (int) ((ans + dfs(find(0), find(0), N, adj)) % kMod);

    std::swap(X, Y);
  }

  return ans;
}
