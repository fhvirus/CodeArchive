#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  typedef int64_t ll;

  const ll kMax = 8e9;
  const int kLim = 34; // ceil(log2(8e9)) + 1

  int N, Q;
  cin >> N >> Q;

  vector<ll> one;
  vector<pair<ll, ll>> two;
  for (int a, b, i = 0; i < N; ++i) {
    cin >> a >> b;
    if (a == 1) one.push_back(b);
    else two.emplace_back(a, b);
  }

  sort(begin(one), end(one), greater<>());
  partial_sum(begin(one), end(one), begin(one));
  one.insert(begin(one), 0l);
  while (one.back() > kMax) one.pop_back();

  sort(begin(two), end(two), [](auto u, auto v) {
      return u.second * v.first + v.second > v.second * u.first + u.second; });

  const auto calc = [&](auto& dp) {
    for (auto [u, v] : two)
      for (int i = (int) dp.size() - 1; i > 0; --i)
        dp[i] = min(max(dp[i], dp[i - 1] * u + v), kMax);
  };
  const auto answer = [&](const auto& a) {
    ll k;
    while (Q --> 0) {
      cin >> k;
      auto it = lower_bound(begin(a), end(a), k);
      cout << (it == end(a) ? -1 : (int) (it - begin(a))) << " \n"[Q == 0];
    }
  };

  int n = (int) one.size(), m = (int) two.size();
  if (m >= kLim) {
    vector<ll> dp(kLim + 1);
    for (int i = 0; i <= kLim and i < n; ++i) dp[i] = one[i];
    calc(dp);
    answer(dp);
  } else {
    one.resize(n + m);
    for (int i = n - 1; i >= 0; --i) {
      vector<ll> dp(m + 1);
      dp[0] = one[i];
      calc(dp);
      for (int j = 0; j <= m; ++j)
        one[i + j] = max(one[i + j], dp[j]);
    }
    for (int i = 1; i < n; ++i) one[i] = max(one[i], one[i - 1]);
    answer(one);
  }

  return 0;
}
