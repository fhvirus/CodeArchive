#include <bits/stdc++.h>
using namespace std;

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

struct Number {
  vector<int> tower;
  double val;
  Number (int v = 1) : tower(1, v), val(log(log(v))) {}
  Number add(int v) const {
    Number r = *this;
    r.tower.insert(begin(r.tower), v);
    r.val = exp(r.val) + log(log(v));
    return r;
  }
  bool operator < (const Number& o) const { return val < o.val; }
  bool check(const Number& o) const {
    const auto &f = factors.at(tower[0]),
          &of = factors.at(o.tower[0]);
    int a = -1, b = -1;
    for (const auto& [v, c] : f) {
      if (not of.contains(v)) return false;
      int oc = of.at(v);
      if (a == -1) a = c, b = oc;
      if (a * oc != c * b) return false;
    }
    int64_t u = 1, v = 1;
    for (size_t i = size(tower) - 1; i > 0; --i) u = mpow(tower[i], u);
    for (size_t i = size(o.tower) - 1; i > 0; --i) v = mpow(o.tower[i], v);
    return u * a == v * b;
  }
  friend ostream& operator<< (ostream& O, const Number& p) {
    for (size_t i = 0; i < size(p.tower); ++i)
      O << p.tower[i] << "^ "[i == size(p.tower) - 1];
    return O;
  }
};

void proof() {
  vector<Number> pts;
  for (int i = 2; i <= kC; ++i)
    pts.emplace_back(i);

  const auto remove_lone = [](vector<Number>& pts) -> void {
    bool far = true;
    size_t k = 0;
    for (size_t i = 0; i + 1 < size(pts); ++i) {
      double a = pts[i].val, b = pts[i + 1].val;
      if (b - a > 1 or a + log(exp(b - a) - 1) > log(log(10))) far = true;
      else {
        if (far) pts[k++] = pts[i];
        pts[k++] = pts[i + 1];
        far = false;
      }
    }
    pts.resize(k);
  };

  while (true) {
    size_t o_size = size(pts);

    // expand
    for (size_t i = 0; i < o_size; ++i) {
      for (int j = 2; j <= kC; ++j)
        pts.push_back(pts[i].add(j));
    }
    stable_sort(begin(pts), end(pts));

    // remove values too far away
    remove_lone(pts);

    // remove duplicates using only integer arithmetics
    // check method requires value not to be too large,
    // which is experimented to be true after we remove_lone
    size_t k = 0;
    for (size_t i = 0, j = 0; i < size(pts); i = j) {
      while (j < size(pts) and pts[i].check(pts[j])) ++j;
      pts[k++] = pts[i];
    }
    pts.resize(k);

    // clean up again
    remove_lone(pts);

    cout << size(pts) << endl;
    if (size(pts) == o_size) break;
  }

  cout << pts.back() << endl;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  proof(); // max: 55^92^3 ~= 10^1355200

  return 0;
}
