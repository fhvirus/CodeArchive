#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int N; cin >> N, N != 0; ) {
    map<string, vector<string>> mp;
    for (int i = 0; i < N; ++i) {
      string s;
      cin >> s;
      auto t = s;
      ranges::sort(t);
      mp[t].push_back(s);
    }
    vector<vector<string>> ss;
    for (auto [_, v] : mp) if (size(v) > 1) {
      ranges::sort(v);
      ss.push_back(v);
    }
    ranges::sort(ss);
    for (auto& v : ss) {
      for (int i = 0; i < (int)size(v); ++i)
        cout << v[i] << ",\n"[i + 1 == (int)size(v)];
    }
    if (empty(ss)) cout << "No Answer\n";
  }

  return 0;
}
