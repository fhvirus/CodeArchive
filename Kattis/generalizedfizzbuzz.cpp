#include <bits/stdc++.h>
using namespace std;

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int64_t n, a, b;
  cin >> n >> a >> b;

  int64_t lcm = a * b / gcd(a, b);
  int64_t fb = n / lcm;

  cout << n / a - fb << ' ' << n / b - fb << ' ' << fb << '\n';

  return 0;
}

