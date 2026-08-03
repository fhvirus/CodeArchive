#pragma GCC optimize("Ofast")
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
  int64_t za = a.dist2(), zb = b.dist2(), zc = c.dist2();
  int64_t t = za * b.cross(c) -
    zb * a.cross(c) + zc * a.cross(b); // C^4
  return sign(t);
}

typedef Point<int64_t> P;
const int64_t kC = 10001;

struct Delaunay {
  struct Tri {
    array<int, 3> v;
    array<pair<Tri*, int>, 3> adj;
    vector<int> ps;
    Tri(int a = 0, int b = 0, int c = 0) : v({a, b, c}) {
      ranges::fill(adj, pair(nullptr, -1)); }
  };
  vector<P> ps;
  vector<Tri*> pos;
  vector<Tri> ts;
  Tri* new_tri(int a, int b, int c) {
    ts.emplace_back(a, b, c);
    return &ts.back();
  }
  bool in_tri(Tri* t, int p) const {
    for (int i : {0, 1, 2})
      if (ps[p].cross(ps[t->v[i]], ps[t->v[(i+1)%3]]) < 0)
        return false;
    return true;
  }
  bool in_cc(Tri* t, int p) const {
    auto [a, b, c] = t->v;
    return inCircumcircle(ps[p], ps[a], ps[b], ps[c]) > 0;
  }
  void link(pair<Tri*, int> a, pair<Tri*, int> b) {
    auto [u, i] = a; auto [v, j] = b;
    if (u) u->adj[i] = b;
    if (v) v->adj[j] = a;
  }
  void put(Tri* t, int p) { t->ps.push_back(p), pos[p] = t; }
  void check_and_flip(Tri* t, int s) {
    auto [ot, os] = t->adj[s];
    if (not ot or not in_cc(t, ot->v[os])) return;
    array<pair<Tri*, int>, 4> adjs = {
      t->adj[(s+2)%3], ot->adj[(os+1)%3],
      ot->adj[(os+2)%3], t->adj[(s+1)%3],
    };
    link({t, 1}, {ot, 1});
    link({t, 2}, adjs[0]);
    link({t, 0}, adjs[1]);
    link({ot, 2}, adjs[2]);
    link({ot, 0}, adjs[3]);
    ranges::rotate(t->v, begin(t->v) + s);
    ranges::rotate(ot->v, begin(ot->v) + os);
    t->v[2] = ot->v[0], ot->v[2] = t->v[0];
    vector<int> tps, otps;
    tps.swap(t->ps), otps.swap(ot->ps);
    for (auto& r : {tps, otps}) for (int tp : r)
      put(in_tri(t, tp) ? t : ot, tp);
    for (auto i : {t, ot}) for (int j : {2, 0})
      check_and_flip(i, j);
  }
  void insert(int p) {
    Tri t = *pos[p]; pos[p]->ps.assign(0, 0);
    array<Tri*, 3> nt; nt[0] = pos[p]; *nt[0] = Tri(p, t.v[0], t.v[1]);
    for (int i : {1, 2}) nt[i] = new_tri(p, t.v[i], t.v[(i+1)%3]);
    for (int i : {0, 1, 2}) {
      link({nt[i], 0}, t.adj[(i+2)%3]);
      link({nt[i], 1}, {nt[(i+1)%3], 2});
    }
    for (int tp : t.ps) for (int i : {0, 1, 2})
      if (in_tri(nt[i], tp)) { put(nt[i], tp); break; }
    for (Tri* i : nt) check_and_flip(i, 0);
  }
  Delaunay(const vector<P>& _ps) : ps(size(_ps) + 3) {
    int n = (int)size(_ps);
    ts.reserve(2 * n + 1);
    ranges::copy(_ps, begin(ps));
    ps[n] = P(0,3*kC), ps[n+1] = P(-2*kC,-kC), ps[n+2] = P(2*kC,-kC);
    pos.assign(n, new_tri(n, n + 1, n + 2));
    vector<int> ord(n);
    iota(begin(ord), end(ord), 0);
    ts[0].ps = ord;
    ranges::shuffle(ord, mt19937(334));
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

  vector<P> ps;
  map<pair<int, int>, int> id;
  vector<int> ord;
  for (int x, y, i = 0; i < N; ++i) {
    cin >> x >> y;
    if (id.count({x, y})) {
      cout << id.at({x, y}) << ' ' << i << '\n';
      continue;
    }
    id[pair(x, y)] = i;
    ord.push_back(i);
    ps.emplace_back(x, y);
  }

  Delaunay delaunay(ps);

  vector<tuple<int, int, int>> es;
  for (auto t : delaunay.ts) for (int i : {0, 1, 2}) {
    int u = t.v[i], v = t.v[(i+1)%3];
    if (u < (int)size(ps) and v < (int)size(ps) and u < v)
      es.emplace_back((ps[u]-ps[v]).dist2(), u, v);
  }

  ranges::sort(es);
  DSU dsu((int)size(ps));
  for (auto [_, u, v] : es) {
    if (dsu.join(u, v))
      cout << ord[u] << ' ' << ord[v] << '\n';
  }

  return 0;
}
