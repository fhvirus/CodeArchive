#include <bits/stdc++.h>
using namespace std;

bool isPrime(int n) {
  if (n <= 1) return false;
  if (n % 2 == 0) return n == 2;
  for (int i = 3; i * i <= n; i += 2)
    if (n % i == 0) return false;
  return true;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  int l = 1 + (n % 2), m = min(l + 1, n);
  if (isPrime(l + n)) m = n;
  else while (not isPrime(l + m) or not isPrime(m + 1 + n))
    m += 2;

  for (int i = 1; i <= n; ++i) cout << i << " \n"[i == n];
  
  if (l == 2) cout << 1 << " \n"[1 == n];
  for (int i = l; i <= m; ++i) cout << (l + m - i) << " \n"[i == n];
  for (int i = m + 1; i <= n; ++i) cout << (m + 1 + n - i) << " \n"[i == n];

  return 0;
}
