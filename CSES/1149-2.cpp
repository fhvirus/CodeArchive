#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  const int mod = 1e9 + 7;

  vi dp(26, 0);
  int sum = 0;
  for (char c : s) {
    int t = c - 'a', u = (sum - dp[t] + 1 + mod) % mod;
    dp[t] = (dp[t] + u) % mod;
    sum = (sum + u) % mod;
  }

  cout << sum << '\n';

  return 0;
}
