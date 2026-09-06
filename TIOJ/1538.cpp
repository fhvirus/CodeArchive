#include <bits/stdc++.h>
#include <boost/multiprecision/cpp_int.hpp>
using namespace std;

using big_int = boost::multiprecision::cpp_int;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  big_int q, p;
  cin >> q >> p;

  cout << q << '/' << p << " = ";

  bool f = false;
  while (q != 0) {
    big_int g = gcd(q, p);
    q /= g, p /= g;

    big_int d = (p + q - 1) / q;

    if (f) cout << '+';
    cout << "(1/" << d << ')';
    f = true;

    tie(q, p) = pair(q * d - p, p * d);
  }
  cout << '\n';

  return 0;
}
