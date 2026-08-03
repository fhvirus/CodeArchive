#include <bits/stdc++.h>
using namespace std;

typedef int64_t ll;
typedef array<array<ll, 2>, 2> mat;

mat mat_mul(mat a, mat b, ll mod) {
  mat r { {{0, 0}, {0, 0}} };
  for (int i : {0, 1}) for (int j : {0, 1}) for (int k : {0, 1})
    r[i][k] += a[i][j] * b[j][k];
  for (int i : {0, 1}) for (int j : {0, 1})
    r[i][j] %= mod;
  return r;
}
mat mat_pow(mat a, ll e, ll mod) {
  mat r { {{1, 0}, {0, 1}} };
  for (; e > 0; e /= 2, a = mat_mul(a, a, mod))
    if (e & 1) r = mat_mul(r, a, mod);
  return r;
}
ll mod_pow(ll a, ll e, ll mod) {
  ll r = 1;
  for (; e > 0; e /= 2, a = a * a % mod)
    if (e & 1) r = r * a % mod;
  return r;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  ll b, c, n, p, q;
  cin >> b >> c >> n >> p >> q;

  mat m_1 { {{c, b}, {1, 0}} };
  mat m_n_p = mat_pow(m_1, n, p), m_n_q = mat_pow(m_1, n, q);
  ll u = (m_n_p[0][0] + m_n_p[0][1]) % p, v = (m_n_q[1][0] + m_n_q[1][1]) % q;

  cout << (u == 0 ? -1 : mod_pow(u, p - 2, p) * v % q) << endl;

  return 0;
}
