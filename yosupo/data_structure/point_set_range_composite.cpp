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

template <class V, class T> struct SGT {
  int n;
  vector<V> val;
  vector<T> tag;
  static int bc(int u)
  { return u <= 1 ? 1 : (2 << __lg(u-1)); }
  SGT(int n): n(bc(n)), val(n*2), tag(n*2) {}
  SGT(const vector<V>& v): n(bc(sz(v))), val(n*2), tag(n*2) {
    rep (i, 0, sz(v)) val[i+n] = v[i];
    for (int i = n; --i; ) val[i] = val[i*2] + val[i*2+1];
  }
  void upd(int u, T t)
  { val[u] = t(val[u]); if (u < n) tag[u] = tag[u] + t; }
  void pull(int u)
  { while (u /= 2) val[u] = tag[u](val[u * 2] + val[u * 2 + 1]); }
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

const int mod = 998244353;
int modadd(int u, int v)
{ return u + (u + v >= mod ? v - mod : v); }
int modmul(int u, int v)
{ return (int) ((ll) u * v % mod); }

struct Val {
  int a, b;
  Val(int a = 1, int b = 0): a(a), b(b) {}
  Val operator + (const Val& o) const
  { return Val(modmul(a, o.a), modadd(modmul(b, o.a), o.b)); }
  int operator() (const int& x) const
  { return modadd(modmul(a, x), b); }
};
struct Tag {
  Tag() {}
  Tag operator + (const Tag& o) const { return Tag(); }
  Val operator() (Val v) const { return v; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N, Q;
  cin >> N >> Q;

  vector<Val> f(N);
  for (auto& [a, b]: f) cin >> a >> b;

  SGT<Val, Tag> sgt(f);

  for (int t, p, c, d, l, r, x; Q--; ) {
    cin >> t;
    if (t == 0) {
      cin >> p >> c >> d;
      sgt.set(p, Val(c, d));
    } else {
      cin >> l >> r >> x;
      cout << sgt.query(l, r)(x) << '\n';
    }
  }

  return 0;
}
