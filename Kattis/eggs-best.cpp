#include <bits/stdc++.h>
using namespace std;
#ifdef OWO
#define debug(args...) _debug(#args,args)
#define _OO(args...) ostream& operator<<(ostream&O,args)
#define _DEF(S) template<class...T>_OO(S<T...>);
#define _DEC(S,B,E,F) template<class...T>_OO(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
_DEF(vector);_DEF(deque);_DEF(set);_DEF(multiset);_DEF(unordered_set);_DEF(map);_DEF(unordered_map);_DEF(pair);_DEF(tuple);template<class T,size_t N>_OO(array<T,N>);
_DEC(vector,'[',']',i);_DEC(deque,'[',']',i);_DEC(set,'{','}',i);_DEC(multiset,'{','}',i);_DEC(unordered_set,'{','}',i);_DEC(map,'{','}',i.first<<':'<<i.second);_DEC(unordered_map,'{','}',i.first<<':'<<i.second);
template<class...T>_OO(pair<T...>p){return O<<'('<<p.first<<','<<p.second<<')';}template<class...T>_OO(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}template<class T,size_t N>_OO(array<T,N>a){return O<<vector<T>(begin(a),end(a));}
template<class...T>void _debug(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#define debug(...) ((void)0)
#endif

// constant & math tools
const int kC = 100;
int64_t mpow(int64_t x, int64_t e) {
  int64_t r = 1;
  for (; e; x = x * x, e >>= 1)
    if (e & 1) r = r * x;
  return r;
}
map<int, map<int, int>> calc_factors() {
  map<int, map<int, int>> r;
  for (int i = 2; i <= kC; ++i) {
    map<int, int> f;
    int t = i;
    for (int j = 2; j * j <= t; ++j) if (t % j == 0) {
      int c = 0;
      for (; t % j == 0; t /= j) c += 1;
      f[j] = c;
    }
    if (t > 1) f[t] = 1;
    r[i] = f;
  }
  return r;
}
const map<int, map<int, int>> factors = calc_factors();
double diff(double a, double b) { return abs(a - b) / max({1.0, a, b}); }

struct Rep {
  typedef double T;
  const int kLIM_VINT = 18;
  const T kLIM_VFLOAT = 200;

  int type;
  int64_t vint;
  T vfloat;

  Rep (int64_t v = 1) : type(0), vint(v), vfloat(NAN) {}
  Rep (int t, T v) : type(t), vint(-1), vfloat(v) {}
  Rep& operator= (const Rep& o) {
    type = o.type;
    vint = o.vint;
    vfloat = o.vfloat;
    return *this;
  }
  Rep add(int64_t v) const {
    if (type == 0) {
      if (vint * log10(v) <= kLIM_VINT) return Rep(mpow(v, vint));
      Rep r;
      r.type = 1;
      r.vint = -1;
      r.vfloat = vint * log10(v);
      return r;
    }
    if (type == 1) {
      if (vfloat * log10(v) <= kLIM_VFLOAT) return Rep(1, pow(10, vfloat) * log10(v));
      return Rep(2, vfloat + log10(log10(v)));
    }
    assert(type == 2);
    if (vfloat > kLIM_VFLOAT) {
      cerr << "\033[1;31mError! I cannot handle this: \033[0m"
        << vfloat << ".add(" << v << ")" << endl;
      exit(1);
    }
    return Rep(2, pow(10, vfloat) + log10(log10(v)));
  }
  Rep take_log() const { assert(type == 0); return Rep(1, log10(vint)); }
};

const double EPS = 1e-10;
bool check_tower_eq(vector<int> a, vector<int> b) {
  while (not empty(a) and not empty(b) and a.back() == b.back()) {
    a.pop_back();
    b.pop_back();
  }
  if (empty(a) or empty(b)) return empty(a) and empty(b);

  const auto &fa = factors.at(a.back()), &fb = factors.at(b.back());
  if (size(fa) != size(fb)) return false;

  int pa = -1, pb = -1;
  for (const auto& [v, ca] : fa) {
    if (not fb.contains(v)) return false;
    int cb = fb.at(v);
    if (pa == -1) pa = ca, pb = cb;
    if (pa * cb != pb * ca) return false;
  }

  Rep ra, rb;
  for (size_t i = 0; i + 1 < size(a); ++i) ra = ra.add(a[i]);
  for (size_t i = 0; i + 1 < size(b); ++i) rb = rb.add(b[i]);

  if (ra.type != rb.type) return false;
  assert(ra.type != 2);

  if (ra.type == 0) return __int128(pa) * ra.vint == __int128(pb) * rb.vint;
  if (ra.type == 1) {
    double la = double(pa) + ra.vfloat;
    double lb = double(pb) + rb.vfloat;
    double md = diff(la, lb);
    if (md <= EPS) {
      cerr << "\033[1;33mWarning! Small diff: \033[0m";
      for (auto i : a | views::reverse) cerr << i << "^";
      cerr << "(" << pa << "*1e" << ra.vfloat << ")" << "  |  ";
      for (auto i : b | views::reverse) cerr << i << "^";
      cerr << "(" << pb << "*1e" << rb.vfloat << ")" << "     ";
      cerr << md << endl;
    }
    return md <= EPS;
  }
  return false;
}

bool check_tower_lt(vector<int> a, vector<int> b) {
  if (check_tower_eq(a, b)) return false;
  while (not empty(a) and not empty(b) and a.back() == b.back()) {
    a.pop_back();
    b.pop_back();
  }
  if (empty(a) or empty(b)) return empty(a);

  Rep ra, rb;
  for (size_t i = 0; i < size(a) - 1; ++i) ra = ra.add(a[i]);
  for (size_t i = 0; i < size(b) - 1; ++i) rb = rb.add(b[i]);
  assert(ra.type != 2); assert(rb.type != 2);

  if (ra.type == 0 and rb.type == 0) {
    long double la = ra.vint * log10((long double) a.back());
    long double lb = rb.vint * log10((long double) b.back());
    return la - lb < -EPS;
  }

  if (ra.type == 0) ra = ra.take_log();
  if (rb.type == 0) rb = rb.take_log();
  double va = ra.vfloat, vb = rb.vfloat;

  if (abs(va - vb) >= abs(log10(log10(100)) - log10(log10(2))))
    return va < vb;

  if (diff(va, vb) <= EPS) {
    // cerr << "\033[1;33m testing lt \033[0m" << va << ' ' << a.back() << ' '
    //   << vb << ' ' << b.back() << " => " << (a.back() < b.back()) << endl;
    return a.back() < b.back();
  }

  double la = log10(log10(a.back())), lb = log10(log10(b.back()));
  // if (diff((va + la), (vb + lb)) <= EPS) {
  //   cerr << "\033[1;33m testing lt \033[0m" << va << ' ' << la << ' '
  //     << vb << ' ' << lb << " => " << va + la << ' '
  //     << vb + lb << " => " << ((va + la) - (vb + lb) < -EPS) << endl;
  // }

  return (va + la) - (vb + lb) < -EPS;
}

bool check_tower_far(vector<int> a, vector<int> b) {
  if (not check_tower_lt(a, b)) return false;

  Rep ra, rb;
  for (size_t i = 0; i < size(a) - 1; ++i) ra = ra.add(a[i]);
  for (size_t i = 0; i < size(b) - 1; ++i) rb = rb.add(b[i]);
  assert(ra.type != 2); assert(rb.type != 2);

  if (ra.type == 0 and rb.type == 0) {
    long double la = ra.vint * log10((long double) a.back());
    long double lb = rb.vint * log10((long double) b.back());
    return (la + 1) - lb < -EPS;
  }

  if (ra.type == 0) ra = ra.take_log();
  if (rb.type == 0) rb = rb.take_log();
  double va = ra.vfloat, vb = rb.vfloat;
  assert(ra.type == 1 and rb.type == 1);

  if (diff(va, vb) <= EPS and va >= log10(230))
    return a.back() < b.back();

  if ((va + 1 - vb) < -EPS) return true;

  bool ans = false;
  if (diff(va, vb) <= EPS) ans = (a.back() != b.back());
  else {
    double la = va + log10(log10(a.back()));
    double lb = vb + log10(log10(b.back()));
    ans = la + log10(pow(10, lb - la) - 1) >= log10(log10(10));
  }

  if (ans == false) {
    cerr << "\033[1;33m testing far \033[0m ";
    for (int i = int(size(a)) - 1; i >= 0; --i) cerr << a[i] << "^ "[i == 0];
    cerr << va << ' ';
    for (int i = int(size(b)) - 1; i >= 0; --i) cerr << b[i] << "^ "[i == 0];
    cerr << vb << ' ';
    cerr << " => " << ans << endl;
  }
  return ans;
}

struct Number {
  vector<int> tower;
  Number (int v = 1) : tower(1, v) {}
  Number add(int v) const {
    Number r = *this;
    r.tower.insert(begin(r.tower), v);
    return r;
  }
  bool operator < (const Number& o) const { return check_tower_lt(tower, o.tower); }
  bool check(const Number& o) const { return check_tower_eq(tower, o.tower); }
  friend ostream& operator<< (ostream& O, const Number& p) {
    for (int i = int(size(p.tower)) - 1; i >= 0; --i)
      O << p.tower[i] << "^ "[i == 0];
    return O;
  }
};

void proof() {
  vector<Number> pts;
  for (int i = 2; i <= kC; ++i)
    pts.emplace_back(i);

  const auto remove_lone = [](vector<Number>& pts) -> void {
    bool far = true;
    vector<Number> npts;
    for (size_t i = 0; i + 1 < size(pts); ++i) {
      if (check_tower_far(pts[i].tower, pts[i + 1].tower)) far = true;
      else {
        if (far) npts.push_back(pts[i]);
        npts.push_back(pts[i + 1]);
        far = false;
      }
    }
    pts.swap(npts);
  };

  // while (true) {
  for (int _ = 0; _ < 3; ++_) {
    size_t o_size = size(pts);

    // expand
    for (size_t i = 0; i < o_size; ++i) {
      for (int j = 2; j <= kC; ++j)
        pts.push_back(pts[i].add(j));
    }
    stable_sort(begin(pts), end(pts));

    // remove values too far away
    remove_lone(pts);
    cout << size(pts) << endl;

    // remove duplicates using only integer arithmetics
    // check method requires value not to be too large,
    // which is experimented to be true after we remove_lone
    size_t k = 0;
    cerr << "start check" << endl;
    for (size_t i = 0, j = 0; i < size(pts); i = j) {
      for (; j < size(pts) and pts[i].check(pts[j]); ++j);
      assert(k <= i);
      pts[k++] = pts[i];
    }
    cerr << "end check" << endl;
    pts.resize(k);
    pts.shrink_to_fit();
    cout << size(pts) << endl;

    // clean up again
    remove_lone(pts);

    cout << size(pts) << ' '
      << pts[size(pts) - 2] << ' ' << pts.back() << endl;
    if (size(pts) == o_size) break;
  }

  assert(not check_tower_far(pts[size(pts) - 2].tower, pts.back().tower));
  cout << pts.back() << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  cout << setprecision(16) << fixed;
  cerr << setprecision(16) << fixed;

  proof(); // max: 55^92^3 ~= 10^1355200

  // cerr << check_tower_far({100, 32, 3}, {83, 64, 81}) << endl;

  return 0;
}
