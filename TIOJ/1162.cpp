#include <bits/stdc++.h>
using namespace std;

struct Road { string name; int u, v, len; };
struct DSU {
  vector<int> f;
  DSU (int n) : f(n, -1) {}
  int find(int u) { return f[u] < 0 ? u : f[u] = find(f[u]); }
  bool merge(int u, int v) {
    if ((u = find(u)) == (v = find(v))) return false;
    if (f[u] > f[v]) swap(u, v);
    return f[u] += exchange(f[v], u), true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  while (cin >> n, n) {
    vector<string> spot(n);
    for (auto &s : spot) cin >> s;

    int m;
    cin >> m;

    vector<Road> road(m);
    for (auto &[name, u, v, len] : road)
      cin >> name >> u >> v >> len;
    { string s; cin >> s; }

    vector<int> id(m);
    iota(begin(id), end(id), 0);
    ranges::sort(id, [&road](int i, int j) { return road[i].len < road[j].len; });

    DSU dsu(n);
    vector<bool> need(m);
    for (int i : id) need[i] = dsu.merge(road[i].u, road[i].v);

    int sum = 0;
    for (int cnt = 0, i = 0; i < m; ++i) if (need[i]) {
      auto [name, u, v, len] = road[i];
      if (u > v) swap(u, v);
      cnt += 1, sum += len;
      printf("#%d Road is named %s, connect %s and %s,length=%d\n",
          cnt, name.c_str(), spot[u].c_str(), spot[v].c_str(), len);
    }
    printf("Jiang will spend %d00 TMTdollars.\n", sum);
  }
  
  return 0;
}
