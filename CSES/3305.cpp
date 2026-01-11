#include <bits/stdc++.h>
using namespace std;

int query(int f, int i) {
  if (i < 1) return INT_MAX / 2;
  int res;
  cout << "FS"[f] << ' ' << i << endl;
  cin >> res;
  return res;
}

int main() {

  int n, k;
  cin >> n >> k;

  int p[2]; p[0] = p[1] = max(0, k - n - 1);
  for (int f : {0, 1}) for (int l = 1 << __lg(n); l > 0; l /= 2) {
    int t = p[f] + l;
    if (t > min(n, k)) continue;
    int fv = query(f, t), sv = query(1 - f, k - t);
    if (fv >= sv) p[f] = t;
  }

  for (int f : {0, 1}) p[f] = (p[f] < n ? query(f, p[f] + 1) : INT_MIN);
  cout << "! " << max(p[0], p[1]) << endl;

  return 0;
}
