#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;


vi z_func(const string &s) {
  vi z(sz(s));
  int l = 0, r = 0;
  rep (i, 1, sz(s)) {
    if (i < r) z[i] = min(r - i, z[i - l]);
    while (i + z[i] < sz(s) and s[z[i]] == s[i + z[i]]) ++z[i];
    if (i + z[i] > r) l = i, r = i + z[i];
  }
  return z;
}
vi fail_func(const string &s) {
  vi p(sz(s));
  rep (i, 1, sz(s)) {
    int j = p[i - 1];
    while (j > 0 and s[j] != s[i]) j = p[j - 1];
    p[i] = j + (s[j] == s[i]);
  }
  return p;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string s;
  cin >> s;

  vi z = z_func(s);
  vi p = fail_func(s);

  rep (i, 0, sz(s)) cout << z[i] << " \n"[i == sz(s) - 1];
  rep (i, 0, sz(s)) cout << p[i] << " \n"[i == sz(s) - 1];

  return 0;
}
