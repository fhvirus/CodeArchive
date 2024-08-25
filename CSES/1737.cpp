#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct EizokuSeguki {
  struct Node { ll sum; int lc, rc; };
  vector<Node> nds;
  int newNode(ll sum = 0, int lc = -1, int rc = -1) {
    nds.push_back({sum, lc, rc});
    return sz(nds) - 1;
  }
  int build(int l, int r, vi &v) {
    if (l + 1 == r) return newNode(v[l]);
    int m = (l + r) / 2;
    int lc = build(l, m, v);
    int rc = build(m, r, v);
    return newNode(nds[lc].sum + nds[rc].sum, lc, rc);
  }
  int n;
  vi rts;
  EizokuSeguki(vi &v) : n(sz(v)) { rts.push_back(build(0, n, v)); }
  int set(int i, int l, int r, int p, ll x) {
    if (l + 1 == r) return newNode(x);
    int m = (l + r) / 2;
    int lc = (p < m ? set(nds[i].lc, l, m, p, x) : nds[i].lc);
    int rc = (p >= m ? set(nds[i].rc, m, r, p, x) : nds[i].rc);
    return newNode(nds[lc].sum + nds[rc].sum, lc, rc);
  }
  void set(int k, int p, ll x) { rts[k] = set(rts[k], 0, n, p, x); }
  ll query(int i, int l, int r, int ql, int qr) {
    if (ql <= l and r <= qr) return nds[i].sum;
    int m = (l + r) / 2;
    return (ql < m ? query(nds[i].lc, l, m, ql, qr) : 0) +
      (m < qr ? query(nds[i].rc, m, r, ql, qr) : 0);
  }
  ll query(int k, int l, int r) { return query(rts[k], 0, n, l, r); }
  void copy(int k) { 
    rts.push_back(sz(nds));
    nds.push_back(nds[rts[k]]);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vi x(n);
  for (int &i : x) cin >> i;

  EizokuSeguki esgk(x);
  for (int t, k, a, b; q--; ) {
    cin >> t >> k;
    if (t == 1) {
      cin >> a >> b;
      esgk.set(k - 1, a - 1, b);
    } else if (t == 2) {
      cin >> a >> b;
      cout << esgk.query(k - 1, a - 1, b) << '\n';
    } else esgk.copy(k - 1);
  }
}
