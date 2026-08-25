#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> X(N), V(N);
  for (int i = 0; i < N; ++i)
    cin >> X[i] >> V[i];

  int64_t cnt = (int64_t) N * (N - 1) / 2;
  {
    vector<int> a(101);
    for (int v : V) {
      for (int p = v; p; p -= p & -p) cnt -= a[p];
      for (int p = v; p < 101; p += p & -p) a[p] += 1;
    }
  }
  cout << cnt % 1000000 << '\n';
  cnt = min<int64_t>(cnt, 10000);

  vector<int> pos(N);
  iota(begin(pos), end(pos), 0);
  auto ord = pos;

  const auto cmp = [&](auto u, auto v) {
    auto [ui, uj] = u; auto [vi, vj] = v;
    auto ux = (X[uj] - X[ui]), vx = (X[vj] - X[vi]),
         uv = (V[ui] - V[uj]), vv = (V[vi] - V[vj]);
    auto tu = ux * vv, tv = vx * uv;
    return tu != tv ? tu > tv : pos[ui] > pos[vi];
  };

  priority_queue<pii, vector<pii>, decltype(cmp)> pq(cmp);
  const auto kolla = [&](int i, int j) {
    if (pos[i] < pos[j] and V[i] > V[j])
      pq.emplace(i, j);
  };
  for (int i = 1; i < N; ++i) kolla(i - 1, i);

  for (int t = 0; t < cnt; ) {
    auto [u, v] = pq.top(); pq.pop();
    if (pos[u] + 1 != pos[v]) continue;
    cout << u + 1 << ' ' << v + 1 << '\n';
    t += 1;
    swap(ord[pos[u]], ord[pos[v]]);
    swap(pos[u], pos[v]);
    if (pos[v] > 0)
      kolla(ord[pos[v] - 1], ord[pos[v]]);
    if (pos[u] + 1 < N)
      kolla(ord[pos[u]], ord[pos[u] + 1]);
  }

  return 0;
}
