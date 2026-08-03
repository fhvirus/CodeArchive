#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> pii;

struct RollbackDSU {
	vector<int> f; vector<pii> st;
	RollbackDSU(int n) : f(n, -1) {}
	int size(int x) { return -f[find(x)]; }
	int find(int x) { return f[x] < 0 ? x : find(f[x]); }
	int time() { return (int)st.size(); }
	void rollback(int t) {
		for (int i = time(); i --> t;)
			f[st[i].first] = st[i].second;
		st.resize(t);
	}
	bool join(int a, int b) {
		a = find(a), b = find(b);
		if (a == b) return false;
		if (f[a] > f[b]) swap(a, b);
		st.emplace_back(a, f[a]);
		st.emplace_back(b, f[b]);
		f[a] += f[b]; f[b] = a;
		return true;
	}
};

struct Frac {
  int64_t a, b;
  Frac(int64_t _a = 0, int64_t _b = 1) {
    int64_t g = gcd(_a, _b);
    a = _a / g, b = _b / g;
  }
  auto operator <=> (const Frac& o) const {
    return a * o.b <=> o.a * b; }
  auto operator == (const Frac& o) const {
    return ((*this) <=> o) == 0; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n;
  cin >> n;

  vector<int> m(n);
  for (int &i : m) cin >> i;

  vector<Frac> ts;
  vector<tuple<int, int, Frac, Frac>> es;
  vector<pii> bff;
  for (int i = 0; i < n; ++i) {
    for (int j = i + 1; j < n; ++j) {
      int L, U;
      cin >> L >> U;
      if (L == -1) continue;
      int d = abs(m[i] - m[j]);
      if (d == 0) {
        if (L <= 0) bff.emplace_back(i, j);
        continue;
      }
      // L <= d * t <= U
      Frac lb(L, d), rb(U, d);
      ts.push_back(lb);
      ts.push_back(rb);
      es.emplace_back(i, j, lb, rb);
    }
  }

  ranges::sort(ts);
  ts.erase(ranges::unique(ts).begin(), end(ts));
  const auto get_t = [&](Frac a) { return (int) (ranges::lower_bound(ts, a) - begin(ts)); };

  int len = 1 << bit_width((unsigned)max(1, (int)size(ts)));
  vector tes(2 * len, vector<pii>());
  const auto add = [&](pii p, int lb, int rb) {
    for (lb += len, rb += len + 1; lb < rb; lb /= 2, rb /= 2) {
      if (lb & 1) tes[lb++].push_back(p);
      if (rb & 1) tes[--rb].push_back(p);
    }
  };
  for (auto p : bff) add(p, 0, len - 1);
  for (auto [i, j, lb, rb] : es)
    add(pii(i, j), get_t(lb), get_t(rb));

  int ans = 1;
  RollbackDSU dsu(n);
  const auto solve = [&](const auto& self, int id, int lb, int rb) -> void {
    int t = dsu.time();
    for (auto [a, b] : tes[id]) 
      if (dsu.join(a, b)) ans = max(ans, dsu.size(a));
    if (lb + 1 < rb) {
      int mb = (lb + rb) / 2;
      self(self, id * 2, lb, mb);
      self(self, id * 2 + 1, mb, rb);
    }
    dsu.rollback(t);
    return;
  };
  solve(solve, 1, 0, len);

  cout << ans << '\n';

  return 0;
}
