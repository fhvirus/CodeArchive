#include <bits/stdc++.h>
using namespace std;


int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<vector<int>> adj(N + 1);
  vector<int> cnt(N + 1);
  for (int u, v, i = 0; i < N; ++i) {
    cin >> u >> v;
    adj[u].push_back(v);
    adj[v].push_back(u);
    cnt[u] += 1, cnt[v] += 1;
  }

  queue<int> q;
  for (int u = 1; u <= N; ++u)
    if (cnt[u] <= 1) q.push(u);
  while (not empty(q)) {
    int u = q.front(); q.pop();
    for (int v : adj[u])
      if (cnt[v] > 0 and (cnt[v] -= 1) == 1)
        q.push(v);
  }

  int Q;
  cin >> Q;

  for (int s, t, i = 0; i < Q; ++i) {
    cin >> s >> t;
    cout << 1 + (cnt[s] == 2 and cnt[t] == 2) << endl;
  }

  return 0;
}
