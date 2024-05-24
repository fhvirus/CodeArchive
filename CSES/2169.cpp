#include <bits/stdc++.h>
using namespace std;

void solve(vector<pair<int, int>> &a, int lb, int rb, vector<int> &cnt_in, vector<int> &cnt_out) {
  if (rb - lb <= 1) return;
  int mid = (lb + rb) / 2;
  solve(a, lb, mid, cnt_in, cnt_out);
  solve(a, mid, rb, cnt_in, cnt_out);
  for (int lp = lb, rp = mid; lp < mid or rp < rb; ) {
    if (rp == rb or (lp < mid and a[lp].first < a[rp].first)) {
      cnt_in[a[lp].second] += rp - mid;
      lp += 1;
    } else {
      cnt_out[a[rp].second] += mid - lp;
      rp += 1;
    }
  }
  inplace_merge(begin(a) + lb, begin(a) + mid, begin(a) + rb);
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> xs(n);
  vector<pair<int, int>> a;
  for (int y, i = 0; i < n; ++i) {
    cin >> xs[i] >> y;
    a.emplace_back(y, i);
  }
  sort(begin(a), end(a), [&xs](pair<int, int> u, pair<int, int> v) {
    return (xs[u.second] != xs[v.second]) ? (xs[u.second] < xs[v.second]) : u.first > v.first;
  });

  vector<int> cnt_in(n), cnt_out(n);

  solve(a, 0, n, cnt_in, cnt_out);

  for (int i = 0; i < n; ++i)
    cout << cnt_in[i] << " \n"[i == n - 1];

  for (int i = 0; i < n; ++i)
    cout << cnt_out[i] << " \n"[i == n - 1];

  return 0;
}
