#include <bits/stdc++.h>
using namespace std;

const int mod = 53;
int modinv[mod];

auto laesa() {
  string s;
  vector<int> res;
  while (cin >> s and s[0] != '=') for (char c : s)
    res.push_back(c == '_' ? 0 : (isupper(c) ? 1 + c - 'A' : 27 + c - 'a'));
  return res;
}

auto decrypt(const auto& ct, const auto& key) {
  int n = (int)size(key), m = (int)size(ct);
  vector<int> res;
  for (int i = 0; i < m; i += n) {
    for (int j = 0; j < n; ++j) {
      int c = 0;
      for (int k = 0; k < n; ++k)
        c += ct[i + k] * key[k][j];
      c %= mod;
      res.push_back(c);
    }
  }
  return res;
}

optional<vector<vector<int>>>
    crack(int n, const auto& pt, const auto& ct) {
  if (size(pt) != size(ct) or size(pt) < n * n) return {};
  vector a(n, vector<int>(2 * n));
  for (int i = 0; i < n; ++i) {
    a[i][n + i] = 1;
    for (int j = 0; j < n; ++j)
      a[i][j] = ct[i * n + j];
  }
  for (int i = 0; i < n; ++i) {
    int r = -1;
    for (int j = i; j < n; ++j)
      if (a[j][i] != 0) { r = j; break; }
    if (r == -1) return {};
    if (r != i) swap(a[r], a[i]);
    int inv = modinv[a[i][i]];
    for (int &v : a[i]) v = v * inv % mod;
    for (int j = i + 1; j < n; ++j) if (a[j][i] != 0) {
      int mul = a[j][i];
      for (int k = 0; k < 2 * n; ++k)
        a[j][k] = (a[j][k] - a[i][k] * mul % mod + mod) % mod;
    }
  }
  for (int i = n - 1; i >= 0; --i) {
    for (int j = i - 1; j >= 0; --j) if (a[j][i] != 0) {
      int mul = a[j][i];
      for (int k = 0; k < 2 * n; ++k)
        a[j][k] = (a[j][k] - a[i][k] * mul % mod + mod) % mod;
    }
  }
  for (int i = 0; i < n; ++i) for (int j = 0; j < n; ++j) {
    a[i][j] = 0;
    for (int k = 0; k < n; ++k)
      a[i][j] += a[i][n + k] * pt[k * n + j];
    a[i][j] %= mod;
  }
  for (int i = 0; i < n; ++i) a[i].resize(n);
  if (decrypt(ct, a) != pt) return {};
  return a;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  for (int i = 1; i < mod; ++i)
    for (int j = 1; j < mod; ++j)
      if (i * j % mod == 1)
        modinv[i] = j;

  int T;
  cin >> T;

  while (T --> 0) {
    int n;
    cin >> n;

    laesa();
    auto pt = laesa();
    auto ct = laesa();
    auto secret = laesa();

    auto key = crack(n, pt, ct);
    if (not key.has_value()) {
      cout << "Unable to crack the Matrix\n";
      continue;
    }
    auto ans = decrypt(secret, *key);
    for (int c : ans)
      cout << (c == 0 ? '_' : (c <= 26 ? char('A' + c - 1) : char('a' + c - 27)));
    cout << '\n';
  }

  return 0;
}
