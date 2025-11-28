#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<string> s(n);
  for (auto &i : s) cin >> i;

  sort(begin(s), end(s));

  const string INF(30, '~');
  string ans = INF;

  set<vector<string>> vis;

  const auto better = [](const string& u, const string& v) {
    if (u.size() != v.size()) return u.size() < v.size();
    return u < v;
  };

  const auto search = [&vis, &better, &ans](const auto& search, vector<string> s) -> void {
    sort(begin(s), end(s));
    if (vis.count(s)) return;
    vis.insert(s);
    if (s.size() == 1) {
      if (better(s[0], ans)) ans = s[0];
      return;
    }
    int m = (int) s.size();
    for (int i = 1; i < m; ++i) {
      for (int j = 0; j < i; ++j) {
        auto t = s;
        string u = s[i];
        string v = s[j];
        t.erase(begin(t) + i);
        t.erase(begin(t) + j);
        for (int l = 0; l < 2; ++l) {
          for (int len = 1; len <= (int) u.size() and len <= (int) v.size(); ++len) {
            if (u.substr((int) u.size() - len) != v.substr(0, len)) continue;
            t.push_back(u + v.substr(len));
            search(search, t);
            t.pop_back();
          }
          swap(u, v);
        }
      }
    }
    return;
  };

  do search(search, s);
  while (next_permutation(begin(s), end(s)));

  cout << (ans == INF ? "-1" : ans) << '\n';


  return 0;
}
