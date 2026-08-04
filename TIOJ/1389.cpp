#include <bits/stdc++.h>
using namespace std;

struct BigInt {
  typedef uint64_t ull;
  static const ull kL = 1e17;
  bool neg;
  vector<ull> a;
  BigInt(int v = 0) : neg(v < 0), a(1, abs(v)) {}
  void mul(int v) {
    if (v < 0) neg ^= 1, v = abs(v);
    if (v == 0) { neg = false; a.assign(1, 0); return; }
    if (v == 1) return;
    ull carry = 0;
    for (ull &i : a) {
      i = i * v + carry;
      carry = i / kL;
      i -= carry * kL;
    }
    if (carry > 0) a.push_back(carry);
  }
  bool operator < (const BigInt& o) const {
    if (neg xor o.neg) return neg;
    int n = (int)size(a), m = (int)size(o.a);
    if (n != m) return neg ? n > m : n < m;
    for (int i = n - 1; i >= 0; --i)
      if (a[i] != o.a[i])
        return neg ? a[i] > o.a[i] : a[i] < o.a[i];
    return false;
  }
  void print() {
    if (neg) cout << '-';
    cout << a.back();
    for (int i = (int)size(a) - 2; i >= 0; --i)
      cout << setw(17) << setfill('0') << a[i];
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);

  for (int n; cin >> n; ) {
    BigInt mx(1), mn(1), ans(-20);
    for (int a, i = 0; i < n; ++i) {
      cin >> a;
      BigInt cur(a);
      mx.mul(a); mn.mul(a);
      if (mx < mn) swap(mx, mn);
      if (mx < cur) mx = cur;
      if (cur < mn) mn = cur;
      if (ans < mx) ans = mx;
    }
    ans.print(); cout << '\n';
  }

  return 0;
}
