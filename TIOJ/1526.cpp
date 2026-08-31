#include <bits/stdc++.h>
using namespace std;

#include <boost/multiprecision/cpp_int.hpp>
using big_int = boost::multiprecision::cpp_int;

int main() {
  cin.tie(0)->sync_with_stdio(0);

  big_int p, q;
  cin >> p >> q;

  big_int val = 0, d;
  while (cin >> d) val = val * p + d;

  vector<big_int> o;
  while (val > 0) {
    d = val / q;
    o.push_back(val - d * q);
    val = d;
  }

  for (auto &i : o | views::reverse) cout << i << ' ';
  cout << '\n';

  return 0;
}
