#include <cstdio>
#include <algorithm>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

struct Blossom
{
  std::vector<std::vector<int>> adj;
  std::vector<int> match, dis, par, f, vis;
  std::queue<int> q;
  Blossom(int N) : adj(N), match(N, -1), dis(N), par(N), f(N), vis(N) {}
  void addEdge(int u, int v)
  {
    adj[u].push_back(v);
    adj[v].push_back(u);
  }
  int find(int u) { return u == f[u] ? u : f[u] = find(f[u]); }
  int lca(int u, int v)
  {
    static int t = 0; ++t;
    u = find(u), v = find(v);
    while (vis[u] != t)
    {
      vis[u] = t;
      if (match[u] != -1) u = find(par[match[u]]);
      std::swap(u, v);
    }
    return u;
  }
  void shrink(int u, int v, int l)
  {
    // printf("shrink %d %d %d\n", u, v, l);
    // printf("%d %d %d\n", u, par[u], match[u]);
    while (find(u) != l)
    {
      par[u] = v;
      v = match[u];
      if (dis[v] == 1) dis[v] = 0, q.push(v);
      f[u] = l, f[v] = l;
      u = par[v];
    }
  }
  int bfs(int s)
  {
    // printf("\nBFS %d\n", s);
    std::fill(dis.begin(), dis.end(), -1);
    std::iota(f.begin(), f.end(), 0);
    q = std::queue<int>();

    par[s] = s;
    dis[s] = 0;
    q.push(s);

    while (!q.empty())
    {
      int u = q.front(); q.pop();
      for (int v : adj[u])
      {
        if (dis[v] == -1)
        {
          par[v] = u;
          dis[v] = 1;
          if (match[v] == -1)
          {
            while (v != -1)
            {
              u = par[v];
              int t = match[u];
              match[u] = v;
              match[v] = u;
              // printf("Match %d %d\n", u, v);
              v = t;
            }
            return 1;
          }
          dis[match[v]] = 0;
          q.push(match[v]);
          // printf("edge %d %d--%d\n", u, v, match[v]);
        }
        else if (dis[v] == 0 and find(u) != find(v))
        {
          int l = lca(u, v);
          shrink(u, v, l);
          shrink(v, u, l);
        }
      }
    }

    return 0;
  }
  int solve()
  {
    int ans = 0;
    for (int i = 0; i < (int) adj.size(); ++i)
      if (match[i] == -1) ans += bfs(i);
    return ans;
  }
};

// LittleCube is very strong and he breaks lines before {
// so I gotta try it now
int main()
{

  int T;
  scanf("%d", &T);

  while (T --> 0)
  {
    int N, M;
    scanf("%d%d", &N, &M);

    Blossom b(N + 1);
    for (int u, v; M--; )
    {
      scanf("%d%d", &u, &v);
      b.addEdge(u, v);
    }

    printf("%d\n", b.solve());
  }

  return 0;
}
