#include <bits/stdc++.h>
using namespace std;

template <class T>
tuple<T,T,T> extgcd(T a, T b) {
  if (b == 0) return {1, 0, a};
  auto [x, y, g] = extgcd(b, a % b);
  return {y, x - a/b * y, g};
}

template <class T>
T crt(T a, T m, T b, T n) {
  if (n > m) swap(a, b), swap(m, n);
  auto [x, y, g] = extgcd(m, n);
  x = (b - a) % n * x % n / g * m + a;
  return x < 0 ? x + m*n/g : x;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int n; cin >> n, n != 0; ) {
    array<int, 3> v {0, 0, 0}, mod {1, 1, 1};
    for (int f, w, i = 0; i < n; ++i) {
      cin >> f >> w;
      if (v[0] == -1) continue;
      for (int p : {2, 3}) {
        int mi = 1;
        while (w % p == 0) mi *= p, w /= p;
        int vi = f % mi;
        if (mi > mod[p - 1]) swap(vi, v[p - 1]), swap(mi, mod[p - 1]);
        if (v[p - 1] % mi != vi) v[0] = -1;
      }
      int g = gcd(mod[0], w);
      if (v[0] % g != f % g) v[0] = -1;
      if (v[0] == -1) continue;
      w /= g; f %= w;
      v[0] = crt(v[0], mod[0], f, w);
      mod[0] *= w;
    }
    if (v[0] == -1) cout << "Starvation\n";
    else {
      for (int i : {1, 2}) {
        v[0] = crt(v[0], mod[0], v[i], mod[i]);
        mod[0] *= mod[i];
      }
      int t = (v[0] / 60) % 12;
      cout << (t == 0 ? 12 : t) << ':'
        << setw(2) << setfill('0') << v[0] % 60 << '\n';
    }
  }

  return 0;
}
