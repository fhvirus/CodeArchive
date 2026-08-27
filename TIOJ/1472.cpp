#include <bits/stdc++.h>
using namespace std;

// https://codeforces.com/blog/entry/57496
int ChromaticNumber(int n, const vector<int>& g) {
  const int mod = 998244353, s = 1 << n;
  vector<int> ind(s), t(s); ind[0] = 1;
  for (int i = 1; i < s; ++i) {
    int l = countr_zero((unsigned)i);
    ind[i] = ind[i - (1 << l)] + ind[(i - (1 << l)) & ~g[l]];
    if (ind[i] >= mod) ind[i] -= mod;
  }
  for (int i = 0; i < s; ++i) t[i] = ((n - popcount((unsigned)i)) & 1 ? -1 : 1);
  for (int k = 1; k < n; ++k) {
    int64_t sum = 0;
    for (int i = 0; i < s; ++i) {
      t[i] = (int) ((int64_t)t[i] * ind[i] % mod);
      sum += t[i];
    }
    if (sum % mod != 0) return k;
  }
  return n;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<int> A(N), B(N);
  for (int i = 0; i < N; ++i)
    cin >> A[i] >> B[i];

  vector<int> g(N);
  for (int i = 0; i < N; ++i)
    for (int j = 0; j < N; ++j) if (i != j)
      if ((A[i] < A[j] and A[j] < B[i]) xor
          (A[i] < B[j] and B[j] < B[i]))
        g[i] |= 1 << j;

  cout << ChromaticNumber(N, g) << '\n';

  return 0;
}
