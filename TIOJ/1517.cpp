#include <bits/stdc++.h>
using namespace std;

// https://web.archive.org/web/20220701084331/https://users.monash.edu/~lloyd/tildeStrings/Alignment/86.IPL.html
template <char kA, int kS>
int FastLCS(const string& s, const string& t) {
  const int n = (int)size(s), m = (int)size(t);
  const int kW = 64, l = (n + kW - 1) / kW;
  vector mask(kS, vector<uint64_t>(l));
  for (int i = 0; i < n; ++i)
    mask[s[i] - kA][i / kW] |= (1ul << (i % kW));
  vector<uint64_t> dp(l);
  for (int i = 0; i < m; ++i) {
    uint64_t carry = 1;
    for (int j = 0; j < l; ++j) {
      uint64_t x = dp[j] | mask[t[i] - kA][j];
      uint64_t y = x - (dp[j] << 1 | carry);
      carry = (dp[j] >> (kW - 1) & 1) + (y > x);
      dp[j] = x & ~y;
    }
  }
  int res = 0;
  for (auto &i : dp) res += popcount(i);
  return res;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s, t;
  getline(cin, s);
  getline(cin, t);

  cout << FastLCS<' ', '~' - ' ' + 1>(s, t) << '\n';

  return 0;
}
