#include <bits/stdc++.h>
using namespace std;

template<class T> int sign(T x) { return (x > 0) - (x < 0); }
template<class T>
struct Point {
  typedef Point P;
  T x, y;
  explicit Point(T _x = 0, T _y = 0) : x(_x), y(_y) {}
  auto operator <=> (const P& p) const = default;
  P operator+(P p) const { return P(x+p.x, y+p.y); }
  P operator-(P p) const { return P(x-p.x, y-p.y); }
  P operator*(T d) const { return P(x*d, y*d); }
  P operator/(T d) const { return P(x/d, y/d); }
  T dot(P p) const { return x*p.x + y*p.y; }
  T cross(P p) const { return x*p.y - y*p.x; }
  T cross(P a, P b) const { return (a-*this).cross(b-*this); }
  T dist2() const { return x*x + y*y; }
  friend ostream& operator<<(ostream& os, P p) {
    return os << "(" << p.x << "," << p.y << ")"; }
};

template <class P> // in/on/out : >/=/< 0
int inCircumcircle(P o, P a, P b, P c) {
  a = a - o, b = b - o, c = c - o;
  if (a.cross(b, c) < 0) swap(b, c);
  __int128 za = a.dist2(), zb = b.dist2(), zc = c.dist2();
  __int128 t = za * b.cross(c) -
    zb * a.cross(c) + zc * a.cross(b); // C^4
  return sign(t);
}

typedef Point<int64_t> P;
const int64_t kC = 10001;

struct Delaunay {
  struct Tri {
    array<int, 3> v, ch;
    array<pair<int, int>, 3> adj;
    Tri(int a = 0, int b = 0, int c = 0) : v({a, b, c}) {
      ranges::fill(ch, -1); ranges::fill(adj, pair(-1, -1)); }
  };
  vector<P> ps;
  vector<Tri> ts;
  vector<array<int, 3>> res;
  bool in_tri(int t, int p) const {
    for (int i : {0, 1, 2})
      if (ps[p].cross(ps[ts[t].v[i]], ps[ts[t].v[(i+1)%3]]) < 0)
        return false;
    return true;
  }
  bool in_cc(int t, int p) const {
    auto [a, b, c] = ts[t].v;
    return inCircumcircle(ps[p], ps[a], ps[b], ps[c]) > 0;
  }
  void link(pair<int, int> a, pair<int, int> b) {
    auto [u, i] = a; auto [v, j] = b;
    if (u != -1) ts[u].adj[i] = b;
    if (v != -1) ts[v].adj[j] = a;
  }
  void check_and_flip(int t, int s, int depth=0) {
    auto [ot, os] = ts[t].adj[s];
    if (ot == -1 or not in_cc(t, ts[ot].v[os])) return;

    int n = (int)size(ts);
    ts.emplace_back(ts[t].v[s], ts[t].v[(s+1)%3], ts[ot].v[os]);
    ts.emplace_back(ts[ot].v[os], ts[t].v[(s+2)%3], ts[t].v[s]);
    link({n, 1}, {n + 1, 1});
    link({n, 2}, ts[t].adj[(s+2)%3]);
    link({n, 0}, ts[ot].adj[(os+1)%3]);
    link({n + 1, 2}, ts[ot].adj[(os+2)%3]);
    link({n + 1, 0}, ts[t].adj[(s+1)%3]);
    ts[t].ch = ts[ot].ch = {n, n + 1, -1};
    for (int i : {n, n + 1}) for (int j : {2, 0})
      check_and_flip(i, j, depth+1);
  }
  void insert(int p) {
    int t = 0;
    while (ts[t].ch[0] != -1) for (int c : ts[t].ch)
      if (c != -1 and in_tri(c, p)) { t = c; break; }

    int n = (int)size(ts);
    for (int i : {0, 1, 2})
      ts.emplace_back(p, ts[t].v[i], ts[t].v[(i+1)%3]);
    ts[t].ch = {n, n + 1, n + 2};

    for (int i : {0, 1, 2}) {
      link({n + i, 0}, ts[t].adj[(i+2)%3]);
      link({n + i, 1}, {n + (i+1)%3, 2});
    }

    for (int i : {n, n + 1, n + 2})
      check_and_flip(i, 0);
  }
  Delaunay(const vector<P>& _ps) : ps(size(_ps) + 3) {
    int n = (int)size(_ps);
    ts.reserve(9 * n);
    ranges::copy(_ps, begin(ps));
    ps[n]     = P(      0, 3 * kC);
    ps[n + 1] = P(-2 * kC,    -kC);
    ps[n + 2] = P( 2 * kC,    -kC);
    ts.emplace_back(n, n + 1, n + 2);

    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    ranges::shuffle(ord, mt19937(7122));
    for (int i : ord) insert(i);
  }
};

struct DSU {
  vector<int> a;
  DSU (int n) : a(n, -1) {}
  int find(int u) { return a[u] < 0 ? u : a[u] = find(a[u]); }
  bool join(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return false;
    if (a[u] > a[v]) swap(u, v);
    return a[u] += exchange(a[v], u), true;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<P> ps(N);
  for (auto &[x, y] : ps) cin >> x >> y;
  ranges::sort(ps);
  ps.erase(ranges::unique(ps).begin(), end(ps));
  N = (int)size(ps);

  Delaunay delaunay(ps);

  vector<tuple<int, int, int>> es;
  es.reserve(6 * N);
  for (auto &t : delaunay.ts) if (t.ch[0] == -1) for (int i : {0, 1, 2}) {
    int u = t.v[i], v = t.v[(i+1)%3];
    if (u < N and v < N)
      es.emplace_back((ps[u]-ps[v]).dist2(), u, v);
  }
  ranges::sort(es);

  double ans = 0;
  DSU dsu(N);
  for (auto [w, u, v] : es) {
    if (dsu.join(u, v))
      ans += sqrt(w);
  }

  cout << setprecision(2) << fixed << ans << '\n';

  return 0;
}
