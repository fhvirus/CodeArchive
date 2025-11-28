#include <bits/stdc++.h>
using namespace std;

int mad(int u, int v) {
  static const int mod = 1e9 + 7;
  u += v - mod;
  return u + (u >> 31 & mod);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, L;
  cin >> N >> L;

  string S;
  cin >> S;

  vector<string> ss;
  for (int len = 1; len <= N; ++len)
    for (int i = 0; i + len <= N; ++i)
      ss.push_back(S.substr(i, len));

  sort(begin(ss), end(ss));
  ss.erase(unique(begin(ss), end(ss)), end(ss));
  int m = (int) ss.size();

  vector<vector<int>> ch(m);
  for (int i = 0; i < m; ++i) {
    const string &s = ss[i];
    for (int len = 1; len <= (int) s.size(); ++len)
      for (int j = 0; j + len <= (int) s.size(); ++j) {
        string t = s.substr(j, len);
        ch[i].push_back((int) (lower_bound(begin(ss), end(ss), t) - begin(ss)));
      }
    sort(begin(ch[i]), end(ch[i]));
    ch[i].erase(unique(begin(ch[i]), end(ch[i])), end(ch[i]));
  }

  vector<int> dp(m), sc(m);
  sc[(int) (lower_bound(begin(ss), end(ss), S) - begin(ss))] = 1;

  for (int l = 0; l < L; ++l) {
    fill(begin(dp), end(dp), 0);
    for (int i = 0; i < m; ++i)
      for (int j : ch[i])
        dp[j] = mad(dp[j], sc[i]);
    swap(dp, sc);
  }

  cout << reduce(begin(sc), end(sc), 0, mad) << '\n';

  return 0;
}
