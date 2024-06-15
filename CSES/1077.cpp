#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  vector<int> x(n);
  for (int &i : x) cin >> i;

  multiset<int> lo, hi;
  int64_t sum_lo = 0, sum_hi = 0;

  auto balance = [&]() -> void {
    if (lo.size() > hi.size() + 1) {
      int val = *rbegin(lo);
      hi.insert(val);
      lo.erase(lo.find(val));
      sum_hi += val;
      sum_lo -= val;
    }
    if (hi.size() > lo.size()) {
      int val = *begin(hi);
      lo.insert(val);
      hi.erase(begin(hi));
      sum_lo += val;
      sum_hi -= val;
    }
  };
  auto insert = [&](int x) -> void {
    if (lo.empty() or x <= *rbegin(lo)) {
      lo.insert(x);
      sum_lo += x;
    } else {
      hi.insert(x);
      sum_hi += x;
    }
    balance();
  };
  auto remove = [&](int x) -> void {
    auto it = lo.find(x);
    if (it != end(lo)) {
      lo.erase(it);
      sum_lo -= x;
    } else {
      hi.erase(hi.find(x));
      sum_hi -= x;
    }
    balance();
  };

  for (int i = 0; i < k - 1; ++i)
    insert(x[i]);

  for (int i = k - 1; i < n; ++i) {
    insert(x[i]);
    int64_t med = *rbegin(lo);
    cout << (sum_hi - med * hi.size()) + (med * lo.size() - sum_lo) << " \n"[i == n - 1];
    remove(x[i - k + 1]);
  }

  return 0;
}
