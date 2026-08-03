// Ref: https://doi.org/10.1016/S0304-3975(02)00438-3
// orZCK

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
template <class T> using min_heap = priority_queue<T, vector<T>, greater<T>>;

const ll INF = LLONG_MAX / 2;

bool relax(vector<ll>& dis, ll d, int v, min_heap<pair<ll, int>>& pq) {
  if (d >= dis[v]) return false;
  pq.emplace(dis[v] = d, v);
  return true;
}

struct Dijkstra {
  vector<int> par;
  vector<ll> dis;
  Dijkstra(const vector<vector<pii>>& adj, int S) :
    par(size(adj), -1), dis(size(adj), INF) {
    min_heap<pair<ll, int>> pq;
    dis[S] = 0;
    pq.emplace(0, S);
    while (not empty(pq)) {
      auto [d, u] = pq.top(); pq.pop();
      if (d != dis[u]) continue;
      for (auto [v, w] : adj[u])
        if (relax(dis, d + w, v, pq))
          par[v] = u;
    }
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m, S, T;
  cin >> n >> m >> S >> T;


  vector<vector<pii>> adj(n + 1);
  for (int a, b, w, i = 0; i < m; ++i) {
    cin >> a >> b >> w;
    adj[a].emplace_back(b, w);
    adj[b].emplace_back(a, w);
  }

  Dijkstra dS(adj, S), dT(adj, T);

  // compute {v_i}, O_i
  vector<int> path, group(n + 1, -1);
  vector<vector<int>> outer(n + 1);
  for (int u = T; u != -1; u = dS.par[u])
    path.push_back(u);
  ranges::reverse(path);
  for (int i = 0; i < int(size(path)); ++i)
    group[path[i]] = i;
  {
    vector<int> cnt(n + 1), ord;
    for (int u = 1; u <= n; ++u)
      if (dS.par[u] != -1) cnt[dS.par[u]] += 1;
    for (int u = 1; u <= n; ++u)
      if (dS.dis[u] != INF and cnt[u] == 0)
        ord.push_back(u);
    for (int i = 0; i < int(size(ord)); ++i) {
      int p = dS.par[ord[i]];
      if (p != -1 and (cnt[p] -= 1) == 0)
        ord.push_back(p);
    }
    for (int u : ord | views::reverse)
      if (group[u] == -1) {
        group[u] = group[dS.par[u]];
        outer[group[u]].push_back(u);
      }
  }

  vector<ll> dis_O(n + 1, INF), dis_D(n + 1, INF), ans(n + 1, -1);
  for (int u = 1; u <= n; ++u)
    if (group[u] != -1 and path[group[u]] != u) ans[u] = dS.dis[T];

  min_heap<pair<ll, int>> pq_O, pq_D;
  for (int i = 1; i < int(size(path)); ++i) {
    // compute d_(G - v_i)
    for (int o : outer[i]) {
      for (auto [u, w] : adj[o]) if (group[u] < i)
        dis_O[o] = min(dis_O[o], dS.dis[u] + w);
      pq_O.emplace(dis_O[o], o);
    }
    while (not empty(pq_O)) { // TODO: dedup this!
      auto [d, u] = pq_O.top(); pq_O.pop();
      if (d != dis_O[u]) continue;
      for (auto [v, w] : adj[u]) if (group[v] == i)
        relax(dis_O, d + w, v, pq_O);
    }

    for (int o : outer[i]) {
      for (auto [d, w] : adj[o]) if (group[d] > i)
        relax(dis_D, dis_O[o] + w + dT.dis[d], d, pq_D);
    }
    outer[i - 1].push_back(path[i - 1]);
    for (int u : outer[i - 1]) {
      for (auto [d, w] : adj[u]) if (group[d] > i)
        relax(dis_D, dS.dis[u] + w + dT.dis[d], d, pq_D);
    }

    while (not empty(pq_D)) {
      auto [dis, v] = pq_D.top();
      if (dis == dis_D[v] and group[v] > i) {
        ans[path[i]] = dis;
        break;
      }
      pq_D.pop();
    }
  }

  int v = int(ranges::max_element(ans) - begin(ans));
  if (ans[v] == -1) cout << -1 << ' ' << dS.dis[T] << endl;
  else cout << v << ' ' << ans[v] << endl;

  return 0;
}
