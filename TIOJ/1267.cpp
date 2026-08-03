#include <bits/stdc++.h>
using namespace std;

bool solve() {
  int N, M;
  cin >> N >> M;

  map<string, int> mp;
  for (int a, i = 0; i < M; ++i) {
    string s(N, '0');
    cin >> a;
    for (char &j : s) cin >> j;
    mp[s] += a;
  }

  for (auto [p, a] : mp)
    for (int i = 0; i < N; ++i) if (p[0] != p[i]) {
      auto t = p;
      swap(t[0], t[i]);
      if (!mp.count(t) or mp.at(t) != a)
        return false;
    }

  return true;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int K;
  cin >> K;
  while (K --> 0) cout << solve();
  cout << '\n';

  return 0;
}
