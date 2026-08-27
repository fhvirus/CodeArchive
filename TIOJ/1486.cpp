#include <bits/stdc++.h>
using namespace std;

const int kN = 1001;
typedef bitset<kN> bs;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n, m; cin >> n >> m, n != 0 or m != 0; ) {
    unordered_map<string, int> var_id, s_id;
    for (int i = 0; i < m; ++i) {
      string s; cin >> s;
      var_id[s] = i;
    }
    s_id["o"] = n;

    vector<bs> pre(n + 1);
    vector<vector<int>> rs(m), ws(m);
    for (int i = 0; i < n; ++i) {
      string cmd, a, b, c;
      cin >> cmd >> a >> b >> c;
      int s1 = s_id.at(b);
      s_id[c] = i;
      pre[i].set(i);
      pre[i] |= pre[s1];
      if (cmd == "J") pre[i] |= pre[s_id.at(a)];
      else (cmd == "R" ? rs : ws)[var_id.at(a)].push_back(i);
    }

    bool ans = true;
    for (int v = 0; v < m and ans; ++v) {
      for (int w : ws[v]) {
        for (int r : rs[v]) ans &= (pre[w][r] or pre[r][w]);
        if (not ans) break;
      }
      for (int r : rs[v]) {
        int last_w = -1;
        for (int w : ws[v]) if (pre[r][w])
          if (last_w == -1 or pre[w][last_w]) last_w = w;
        for (int w : ws[v]) if (pre[r][w])
          ans &= pre[last_w][w];
        if (not ans) break;
      }
    }

    cout << (ans ? "Racing free\n" : "Potential racing condition found\n");
  }

  return 0;
}
