#include <bits/stdc++.h>
using namespace std;

int query(int l, int r) {
  cout << l << ' ' << r << endl;
  cin >> r;
  if (r == 0) exit(0);
  return r;
}

int main() {

  int n;
  cin >> n;

  vector<int> cnt(n + 1);
  for (int i = 1; i <= n; ++i) {
    cnt[i] = query(1, i);
    cnt[0] = query(1, i);
  }

  for (int i = 1; i <= n; ++i) {
    int r = (cnt[i] - cnt[i - 1] + (i - 1)) / 2;
    if (r + 1 < i) {
      query(r + 1, i);
      query(r + 2, i);
    }
  }

  return 0;
}
