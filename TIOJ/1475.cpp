#include <bits/stdc++.h>
using namespace std;

struct BigInt {
  typedef uint64_t ull;
  static const int kD = 16;
  static const ull kL = 1e16;
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

  vector dp(N + 1, vector<BigInt>(S + 1, 0));
  dp[0][0] = 1;
  for (int i = 0; i < N; ++i) {
    for (int j = i; j >= 0; --j)
      for (int k = X[i]; k <= S; ++k)
        dp[j + 1][k].add(dp[j][k - X[i]]);
  }

  int L = 0;
  BigInt K(0);
  for (int i = N; i >= 1; --i) if (not dp[i][S].is_zero()) {
    L = i;
    K = dp[i][S];
    for (int j = i; j > 1; --j) K.mul(j);
    break;
  }

  cout << L << ' ';
  K.print(); cout << '\n';

  return 0;
}
