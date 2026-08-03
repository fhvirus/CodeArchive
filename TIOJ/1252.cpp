#include <bits/stdc++.h>
using namespace std;

pair<int64_t, int> merge_sort(vector<int>& a, int lb, int rb) {
  if (lb + 1 == rb) return {0, 0};
  int m = (lb + rb) / 2;
  auto [cnt, mxv] = merge_sort(a, lb, m);
  {
    auto p = merge_sort(a, m, rb);
    cnt += p.first, mxv = max(mxv, p.second);
  }
  mxv = max(mxv, a[rb - 1] - a[lb]);
  for (int i = lb, j = m; j < rb; ++j) {
    while (i < m and a[i] < a[j]) ++i;
    cnt += (i - lb);
  }
  inplace_merge(begin(a) + lb, begin(a) + m, begin(a) + rb);
  return {cnt, mxv};
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int N; cin >> N, N != 0; ) {
    vector<int> a(N + 1);
    for (int i = 1; i <= N; ++i) {
      char c; cin >> c >> a[i];
      if (c == 'w') a[i] *= -1;
    }
    partial_sum(begin(a), end(a), begin(a));

    auto [cnt, mxv] = merge_sort(a, 0, N + 1);
    cout << cnt << ' ' << mxv << '\n';
  }

  return 0;
}
