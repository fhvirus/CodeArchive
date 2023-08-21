#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
#ifdef NONTOI
#define debug(args...) LKJ("\033[1;32m["#args"]\033[0m", args)
template<class I> void LKJ(I&&x){ cerr << x << '\n'; }
template<class I, class...T> void LKJ(I&&x, T&&...t)
{ cerr << x << ", ", LKJ(t...); }
template<class I> void print(I a, I b)
{ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define print(...) 0
#endif

struct BIT {
  int n; vi val;
  BIT(int n) : n(n), val(n + 1, 1) {
    for (int i = 1; i <= n; ++i)
      if (int p = i + (i & -i); p <= n)
        val[p] += val[i];
  }
  void rem(int p) {
    for (; p <= n; p += p & -p)
      val[p] -= 1;
  }
  int query(int p) {
    int r = 0;
    for (; p > 0; p -= p & -p)
      r += val[p];
    return r;
  }
  int search(int v) {
    int p = 0, s = 0;
    for (int l = 1 << __lg(n); l > 0; l >>= 1)
      if (p + l <= n and s + val[p + l] < v)
        p += l, s += val[p];
    return p + 1;
  }
};

int main() {
	cin.tie(0)->sync_with_stdio(0);
	cin.exceptions(cin.failbit);

  int n, k;
  cin >> n >> k;

  BIT bit(n);

  for (int p = n, c; n > 0; --n) {
    c = (bit.query(p) + k) % n;
    p = bit.search(c + 1);
    cout << p << " \n"[n == 1];
    bit.rem(p);
  }

	return 0;
}
