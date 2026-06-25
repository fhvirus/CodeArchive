#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  while (cin >> n, n != 0) {
    vector<int> a(n);
    for (int &i : a) {
      double p;
      cin >> p;
      i = int(round(p * 100));
    }

    int avg = accumulate(begin(a), end(a), 0) / n;
    int less = 0, more = 0;
    for (int i : a) {
      if (i <= avg) less += avg - i;
      else if (i >= avg + 1) more += i - (avg + 1);
    }

    cout << setprecision(2) << fixed;
    cout << '$' << max(less, more) / 100.0 << '\n';
  }

  return 0;
}
