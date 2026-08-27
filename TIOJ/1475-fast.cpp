#include <bits/stdc++.h>
using namespace std;

struct BigInt {
  typedef uint64_t ull;
  static const int kD = 17;
  static const ull kL = 1e17;
  vector<ull> a;
  BigInt(int v = 0) : a(1, v) {}
  void add(const BigInt& o) {
    if (size(a) < size(o.a)) a.resize(size(o.a));
    ull carry = 0;
    for (int i = 0; i < (int)size(a); ++i) {
      a[i] = a[i] + carry;
      if (i < (int)size(o.a)) a[i] += o.a[i];
      carry = a[i] / kL;
      a[i] -= carry * kL;
    }
    if (carry > 0) a.push_back(carry);
  }
  void mul(int v) {
    ull carry = 0;
    for (ull &i : a) {
      i = i * v + carry;
      carry = i / kL;
      i -= carry * kL;
    }
    if (carry > 0) a.push_back(carry);
  }
  void print() {
    cout << a.back();
    for (int i = (int)size(a) - 2; i >= 0; --i)
      cout << setw(kD) << setfill('0') << a[i];
  }
  bool is_zero() { return size(a) == 1 and a[0] == 0; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> X(N);
  for (int &i : X) cin >> i;

  int S;
  cin >> S;

  vector<int> most(S + 1, INT_MIN);
  vector<BigInt> cnt(S + 1);
  most[0] = 0, cnt[0] = 1;
  for (int x : X) {
    for (int j = S - x; j >= 0; --j) {
      if (most[j] + 1 > most[j + x]) {
        most[j + x] = most[j] + 1;
        cnt[j + x] = cnt[j];
      } else if (most[j] + 1 == most[j + x])
        cnt[j + x].add(cnt[j]);
    }
  }

  if (most[S] <= 0) { cout << "0 0\n"; exit(0); }

  cout << most[S] << ' ';

  BigInt K = cnt[S];
  for (int i = most[S]; i > 1; --i) K.mul(i);
  K.print(); cout << '\n';

  return 0;
}
