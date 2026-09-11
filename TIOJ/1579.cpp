#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  
  const int64_t mod = 1000000007;

  int N;
  cin >> N;

  vector<int64_t> c(N);
  for (auto &i : c) cin >> i;

  vector<int64_t> val(1, 1);
  for (int i = 1; i < N; ++i)
    val.push_back(val.back() * (i % 2 ? 5 : 2));
  
  int64_t lb = 0, sum = 0, ans = 1;
  for (int i = 0; i < N; ++i) {
    if (sum < val[i]) {
      if (sum > 0) ans = ans * (sum / val[lb] + 1) % mod;
      lb = i, sum = 0;
    }
    sum += c[i] * val[i];
  }
  ans = ans * (sum / val[lb] + 1) % mod;

  cout << (ans + mod - 1) % mod << '\n';

  return 0;
}
