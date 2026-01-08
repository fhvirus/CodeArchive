#include <bits/stdc++.h>
using namespace std;

const char conn[5][14] = {
  "0",
  "0111011011100",
  "1000000000100",
  "1011111101000",
  "0111011100000"
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  map<int, bool> mp;
  const auto solve = [&](const auto& solve, int t) {
    if (t == 0) return true;
    if (mp.count(t)) return mp.at(t);
    bool can = false;
    for (int i = 0; i < 13; ++i) if (t >> i & 1) {
      can |= not solve(solve, t ^ (1 << i));
      for (int j = 1; j < 5 and i + j < 13; ++j)
        if ((t >> (i + j) & 1) and conn[j][i] == '1')
          can |= not solve(solve, t ^ (1 << i) ^ (1 << (i + j)));
    }
    return mp[t] = can;
  };

  while (n --> 0) {
    int t;
    cin >> t;
    cout << solve(solve, t) << " \n"[n == 0];
  }

  return 0;
}
