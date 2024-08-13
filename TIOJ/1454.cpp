#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n >> ws;

  string s;
  map<vector<int>, int> mp1, mp2, mp3;
  int64_t ans = 0;
  for (int i = 0; i < n; ++i) {
    getline(cin, s); s.push_back(' ');
    vector<int> name;
    for (int j = (int) s.find_first_not_of(' '), k = 0;
        j != (int) string::npos; j = (int) s.find_first_not_of(' ', k))
      name.push_back((k = (int) s.find(' ', j)) - j);
    ans += mp1[name] + mp2[name] + mp3[name];
    mp1[name] += 1;
    if (not isalpha(end(s)[-2])) {
      if (name.back() == 1) {
        name.pop_back();
        ans += mp1[name] + mp3[name];
        mp2[name] += 1;
      } else {
        name.back() -= 1;
        ans += mp1[name] + mp2[name];
        mp3[name] += 1;
      }
    }
  }
  cout << ans << '\n';

  return 0;
}
