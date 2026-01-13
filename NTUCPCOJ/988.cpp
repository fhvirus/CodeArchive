#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  int n, q;
  cin >> n >> q;

  vector<int> a(n);
  for (int &i : a) cin >> i;

  vector<vector<pair<int, int>>> qs(q);
  for (auto &v : qs) {
    int j = 0, k;
    cin >> k;
    v.resize(k);
    for (auto &[l, r] : v) cin >> l >> r;
    ranges::sort(v);
    for (int i = 0; i < k; ++i) {
      if (v[i].first > v[j].second + 1) v[++j] = v[i];
      else v[j].second = max(v[j].second, v[i].second);
    }
    v.resize(j + 1);
  }

  vector<int> ans(q);
  for (int i = 0; i < q; ++i)
    for (auto &[l, r] : qs[i]) {
      l -= 1;
      ans[i] += (r - l);
    }

  const int kL = 1 << 12;
  vector<bitset<kL>> pre(n + 1);

  for (int bl = 1; bl <= n; bl += kL) {
    for (int i = 0; i < n; ++i) {
      pre[i + 1] = pre[i];
      if (bl <= a[i] and a[i] < bl + kL)
        pre[i + 1].flip(a[i] - bl);
    }
    for (int i = 0; i < q; ++i) {
      bitset<kL> cur;
      for (auto [l, r] : qs[i])
        cur ^= pre[r] ^ pre[l];
      ans[i] -= int(cur.count());
    }
  }

  for (int i : ans) cout << i / 2 << '\n';

  return 0;
}
