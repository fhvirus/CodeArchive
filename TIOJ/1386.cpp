#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n; cin >> n; ) {
    if (n == 1) { cout << "1\n"; continue;; }

    const int kL = 100'000'000;
    vector<int> a(1, 1), b(1, 2), c;
    for (int i = 2; i < n; ++i) {
      c = b;
      c[0] += 1;
      for (int j = 0; j < (int)size(a); ++j)
        c[j] += 2 * a[j];
      int carry = 0;
      for (int j = 0; j < (int)size(c); ++j) {
        c[j] += carry;
        carry = c[j] / kL;
        c[j] -= carry * kL;
      }
      if (carry > 0) c.push_back(carry);
      a = b; b = c;
    }

    cout << b.back();
    b.pop_back();
    for (int v : b | views::reverse)
      cout << setw(8) << setfill('0') << v;
    cout << '\n';
  }

  return 0;
}
