#include <bits/stdc++.h>
using namespace std;

int query(int p, int q) {
  static map<pair<int, int>, int> mp;
  if (mp.count({p, q})) return mp.at({p, q});
  cout << "? " << p << ' ' << q << endl;
  int s; cin >> s;
  return mp[{p, q}] = s;
}

int GoldenSectionSearch(double a, double b, const auto& f) {
  const double r = (sqrt(5)-1)/2;
  double m1 = b - r*(b-a), m2 = a + r*(b-a);
  auto f1 = f((int)floor(m1)), f2 = f((int)floor(m2));
  while (m2 - m1 > 1)
    if (f1 < f2) {
      b = m2; m2 = m1; f2 = f1;
      m1 = b - r*(b-a); f1 = f((int)floor(m1));
    } else {
      a = m1; m1 = m2; f1 = f2;
      m2 = a + r*(b-a); f2 = f((int)floor(m2));
    }
  int res = (int)floor(a);
  for (int i = res + 1; i <= (int)floor(b); ++i)
    if (f(res) > f(i)) res = i;
  return res;
}

int main() {
  int R, C, K;
  cin >> R >> C >> K;

  const auto fr = [&](int p) { return query(p, 1); };
  int p = GoldenSectionSearch(1, R, fr);

  const auto fc = [&](int q) { return query(p, q); };
  int q = GoldenSectionSearch(1, C, fc);

  int s = query(p, q);
  cout << "! " << s << endl;

  return 0;
}
