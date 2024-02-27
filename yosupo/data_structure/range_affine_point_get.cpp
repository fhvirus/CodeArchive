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

const int mod = 998244353;
int modadd(int u, int v)
{ return u + (u + v >= mod ? v - mod : v); }
int modmul(int u, int v)
{ return (int) ((ll) u * v % mod); }

struct Val {
  int val, siz;
  Val(int v = 0, int s = 0): val(v), siz(s) {}
  Val operator + (const Val& o) const
  { return Val(modadd(val, o.val), modadd(siz, o.siz)); }
  friend ostream& operator<< (ostream& os, const Val& v)
  { return os << "(" << v.val << ", " << v.siz << ")"; }
};
struct Tag {
  int b, c;
  Tag(int b = 1, int c = 0): b(b), c(c) {}
  Tag operator + (const Tag& o) const
  { return Tag(modmul(b, o.b), modadd(modmul(c, o.b), o.c)); }
  Val operator() (const Val& v) const
  { return Val(modadd(modmul(v.val, b), modmul(v.siz, c)), v.siz); }
  friend ostream& operator<< (ostream& os, const Tag& t)
  { return os << "(" << t.b << ", " << t.c << ")"; }
};

template <class V, class T>
struct LazySegtree {
  int n;
  vector<V> val;
  vector<T> tag;
  // static int bc(int u)
  // { return u <= 1 ? 1 : (2 << __lg(u-1)); }
  // LazySegtree(int n): n(bc(n)), val(n*2), tag(n*2) {}
  // LazySegtree(const vector<V>& v): n(bc(sz(v))), val(n*2), tag(n*2) {
  LazySegtree(const vector<V>& v): n(sz(v)), val(n*2), tag(n*2) {
    rep (i, 0, sz(v)) val[i+n] = v[i];
    for (int i = n; --i; ) val[i] = val[i*2] + val[i*2+1];
  }
  void upd(int u, T t) {
    val[u] = t(val[u]);
    if (u < n) tag[u] = tag[u] + t;
  }
  void pull(int u) {
    for (u >>= 1; u; u >>= 1)
      val[u] = tag[u](val[u * 2] + val[u * 2 + 1]);
  }
  void push(int u) {
    for (int h = __lg(n)+1, i; --h;) {
      i = u >> h;
      upd(i * 2, tag[i]);
      upd(i * 2 + 1, tag[i]);
      tag[i] = T();
    }
  }
  V query(int l, int r) {
    push(l += n); push((r += n) - 1);
    V rl, rr;
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) rl = rl + val[l++];
      if (r & 1) rr = val[--r] + rr;
    }
    return rl + rr;
  }
  void modify(int l, int r, T t) {
    int tl = (l += n), tr = (r += n) - 1;
    push(tl); push(tr);
    for (; l < r; l >>= 1, r >>= 1) {
      if (l & 1) upd(l++, t);
      if (r & 1) upd(--r, t);
    }
    pull(tl); pull(tr);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q;
  cin >> N >> Q;

  vector<Val> a(N);
  rep (i, 0, N) {
    cin >> a[i].val;
    a[i].siz = 1;
  }

  LazySegtree<Val, Tag> sgt(a);

  for (int t, l, r, b, c; Q--; ) {
    cin >> t;
    if (t == 0) {
      cin >> l >> r >> b >> c;
      sgt.modify(l, r, Tag(b, c));
    } else {
      cin >> l;
      cout << sgt.query(l, l+1).val << '\n';
    }
  }

  return 0;
}
