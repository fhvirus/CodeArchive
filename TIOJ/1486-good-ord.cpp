#include <bits/stdc++.h>
using namespace std;

struct Op { char t; int i; };
bool cmp1(Op a, Op b) {
  if (a.t == 'J' or b.t == 'J') return a.t == 'J';
  if (a.t != b.t) return a.t == 'R';
  return a.i < b.i;
}
bool cmp2(Op a, Op b) {
  if (a.t == 'J' or b.t == 'J') return a.t == 'J';
  if (a.t != b.t) return a.t == 'W';
  return a.i > b.i;
}

auto run(int n, int m, const auto& adj, const auto& action, const auto& cmp) {
  priority_queue<Op, vector<Op>, decltype(&cmp)> pq(cmp);
  vector<int> deg(n + 1);
  for (int i = 0; i <= n; ++i)
    for (int j : adj[i]) deg[j] += 1;
  pq.push({action[n].first, n});

  vector<vector<int>> rw(m);
  vector<int> val(m, -1);
  while (not empty(pq)) {
    auto [_, u] = pq.top(); pq.pop();
    auto [act, var] = action[u];
    if (act == 'R') rw[var].push_back(val[var]);
    if (act == 'W') val[var] = u;
    for (int v : adj[u]) if ((--deg[v]) == 0)
      pq.push({action[v].first, v});
  }
  return rw;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n, m; cin >> n >> m, n != 0 or m != 0; ) {
    map<string, int> var_id, s_id;
    for (int i = 0; i < m; ++i) {
      string s; cin >> s;
      var_id[s] = i;
    }
    s_id["o"] = n;
    vector<vector<int>> adj(n + 1);
    vector<pair<char, int>> action(n + 1);
    for (int i = 0; i < n; ++i) {
      string cmd, a, b, c;
      cin >> cmd >> a >> b >> c;
      int s1 = s_id.at(b), s2 = i;
      s_id[c] = i;
      if (cmd == "J") {
        int s0 = s_id.at(a);
        adj[s0].push_back(s2);
        adj[s1].push_back(s2);
      } else {
        int var = var_id.at(a);
        adj[s1].push_back(s2);
        action[s2] = pair(cmd[0], var);
      }
    }

    bool ans = true;
    if (m > 0) {
      auto r0 = run(n, m, adj, action, cmp1);
      auto r1 = run(n, m, adj, action, cmp2);
      ans = r0 == r1;
    }
    cout << (ans ? "Racing free\n" : "Potential racing condition found\n");
  }

  return 0;
}
