#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

struct DSU {
  vector<int> a;
  DSU (int n) : a(n, -1) {}
  int find(int u) { return a[u] < 0 ? u : a[u] = find(a[u]); }
  void join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (a[u] > a[v]) swap(u, v);
    a[u] += exchange(a[v], u);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<pii> pos(N);
  for (auto &[x, y] : pos) cin >> x >> y;

  int W;
  cin >> W;

  DSU dsu(4 * N);
  vector<int> wall(N);
  vector<pii> side(W);

  for (int A, B, i = 0; i < W; ++i) {
    cin >> A >> B; A -= 1, B -= 1;
    if (pos[A] > pos[B]) swap(A, B);
    if (pos[A].second == pos[B].second) {
      dsu.join(A * 4 + 0, B * 4 + 1);
      dsu.join(A * 4 + 3, B * 4 + 2);
      wall[A] |= 0b0001, wall[B] |= 0b0100;
      side[i] = pii(A * 4 + 0, A * 4 + 3);
    } else {
      dsu.join(A * 4 + 0, B * 4 + 3);
      dsu.join(A * 4 + 1, B * 4 + 2);
      wall[A] |= 0b0010, wall[B] |= 0b1000;
      side[i] = pii(A * 4 + 0, A * 4 + 1);
    }
  }

  for (int i = 0; i < N; ++i)
    for (int d = 0; d < 4; ++d) if ((wall[i] >> d & 1) == 0)
      dsu.join(i * 4 + d, i * 4 + (d == 0 ? 3 : d - 1));

  vector<vector<int>> adj(4 * N);
  for (auto &[u, v] : side) {
    u = dsu.find(u), v = dsu.find(v);
    adj[u].push_back(v);
    adj[v].push_back(u);
  }

  queue<int> q;
  vector<int> dis(4 * N, -1);

  vector<int> ord(N);
  iota(begin(ord), end(ord), 0);
  ranges::sort(ord, [&](int u, int v) { return pos[u] < pos[v]; });

  for (int i : ord) {
    int s = dsu.find(i * 4 + 2);
    if (dis[s] != -1) continue;
    dis[s] = 0, q.push(s);
    while (not empty(q)) {
      int u = q.front(); q.pop();
      for (int v : adj[u]) if (dis[v] == -1)
        dis[v] = dis[u] + 1, q.push(v);
    }
  }

  vector<int> ans;
  for (int i = 0; i < W; ++i) {
    auto [u, v] = side[i];
    if (dis[u] == dis[v])
      ans.push_back(i + 1);
  }

  cout << size(ans) << '\n';
  for (int &i : ans) cout << i << '\n';

  return 0;
}
