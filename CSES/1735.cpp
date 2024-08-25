#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct Val {
  ll sum; int len;
  Val(ll v = 0) : sum(v), len(1) {} // must return identity element   
  Val(ll s, int l) : sum(s), len(l) {}
  Val operator + (const Val& o) const {
    return Val(sum + o.sum, len + o.len); }
  // merge two Vals, order is important
};
struct Tag {
  ll add; int set;
  Tag(ll a = 0, int s = -1) : add(a), set(s) {} // must return identity element
  Tag operator + (const Tag& o) const {
    return o.set != -1 ? o : Tag(add + o.add, set); }
  // compose two Tags, order is important
  Val operator() (Val v) const {
    return Val((set != -1 ? (ll) v.len * set : v.sum) + v.len * add, v.len); }
  // apply the Tag to v
};

int bc(int u) { return u <= 1 ? 1 : (2 << __lg(u-1)); }
template <class V, class T> struct Seguki {
  int n; vector<V> val; vector<T> tag;
  Seguki(int n): n(bc(n)), val(n*2), tag(n*2) {}
  Seguki(const vector<V>& v): n(bc(sz(v))), val(n*2), tag(n*2) {
    rep (i, 0, sz(v)) val[i+n] = v[i];
    for (int i = n; --i; ) val[i] = val[i*2] + val[i*2+1];
  }
  void upd(int u, T t)
  { val[u] = t(val[u]); if (u < n) tag[u] = tag[u] + t; }
  void pull(int u)
  { while (u /= 2) val[u] = tag[u](val[u*2] + val[u*2+1]); }
  void push(int u) {
    for (int h = __lg(n)+1, i; --h;) {
      i = u >> h;
      upd(i * 2, tag[i]);
      upd(i * 2 + 1, tag[i]);
      tag[i] = T();
    }
  }
  void set(int p, V v)
  { push(p += n); val[p] = v; pull(p); }
  V query(int l, int r) {
    V rl, rr;
    for (push(l+=n), push((r+=n)-1); l < r; l /= 2, r /= 2) {
      if (l & 1) rl = rl + val[l++];
      if (r & 1) rr = val[--r] + rr;
    }
    return rl + rr;
  }
  void modify(int l, int r, T t) {
    int tl = (l += n), tr = (r += n) - 1;
    for (push(tl), push(tr); l < r; l >>= 1, r >>= 1) {
      if (l & 1) upd(l++, t);
      if (r & 1) upd(--r, t);
    }
    pull(tl); pull(tr);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, q;
  cin >> n >> q;

  vector<Val> t(n);
  rep (i, 0, n) cin >> t[i].sum;

  Seguki<Val, Tag> sgk(t);
  for (int t, a, b, x; q--; ) {
    cin >> t >> a >> b;
    if (t == 3) cout << sgk.query(a - 1, b).sum << '\n';
    else {
      cin >> x;
      sgk.modify(a - 1, b, t == 1 ? Tag(x, -1) : Tag(0, x));
    }
  }
}
