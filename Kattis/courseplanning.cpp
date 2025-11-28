#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  map<string, pair<int, int>> mp;
  vector<int64_t> single(1, 0);
  for (int i = 0; i < n; ++i) {
    string s;
    int d;
    cin >> s >> d;
    char t = s.back();
    if (isalpha(t)) single.push_back(d);
    else {
      s.pop_back();
      if (t == '1') mp[s].first = d;
      else mp[s].second = d;
    }
  }

  vector<pair<int, int>> dubble;
  for (auto [key, val] : mp) {
    auto [i, ii] = val;
    if (i <= ii) {
      single.push_back(i);
      single.push_back(ii);
    } else dubble.emplace_back(i + ii, i);
  }

  sort(begin(single), end(single));
  partial_sum(begin(single), end(single), begin(single));

  sort(begin(dubble), end(dubble));
  int m = (int) dubble.size();
  vector<int> min_extra(m, INT_MAX);
  for (int i = m - 1; i >= 0; --i) {
    min_extra[i] = min(min_extra[i], dubble[i].second);
    if (i > 0) min_extra[i - 1] = min_extra[i];
  }
  for (int i = 0, cur_max = 0; i < m; ++i) {
    cur_max = max(cur_max, dubble[i].first - dubble[i].second);
    min_extra[i] = min(min_extra[i], dubble[i].first - cur_max);
  }

  vector<int64_t> cost(m * 2 + 1);
  for (int i = 0; i < m; ++i) {
    cost[1 + i * 2] = cost[i * 2] + min_extra[i];
    cost[1 + i * 2 + 1] = cost[i * 2] + dubble[i].first;
  }

  int64_t ans = LLONG_MAX;
  for (int sl = min(k, (int) single.size() - 1), sr = k - sl;
      sl >= 0 and sr < (int) cost.size(); --sl, ++sr)
    ans = min(ans, single[sl] + cost[sr]);

  cout << ans << '\n';

  return 0;
}
