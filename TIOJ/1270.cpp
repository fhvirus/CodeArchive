#include "lib1270.h"

#include <bits/stdc++.h>
using namespace std;

struct DSU {
  vector<int> a, d, e;
  int cyc_comp, max_deg;
  DSU (int n) : a(n, -1), d(n, 0), e(n, 0), cyc_comp(0), max_deg(0) {}
  int find(int u) { return a[u] < 0 ? u : a[u] = find(a[u]); }
  bool join(int u, int v) {
    d[u] += 1, d[v] += 1;
    max_deg = max({max_deg, d[u], d[v]});
    u = find(u), v = find(v);
    if (u == v) {
      e[u] += 1;
      if (e[u] == -a[u]) cyc_comp += 1;
      return true;
    }
    if (a[u] > a[v]) swap(u, v);
    e[u] += e[v] + 1;
    a[u] += exchange(a[v], u);
    return false;
  }
  int size(int u) { return -a[find(u)]; }
  bool ok() { return cyc_comp == 0 and max_deg <= 2; }
};

struct Solver {
  int N, ans;
  vector<DSU> dsu;
  vector<int> cand;
  vector<pair<int, int>> es;
  Solver(int _N = 0) : N(_N), ans(N), dsu(1, DSU(N)) {}
  void link(int u, int v) {
    if (ans == 0) return;
    if (not empty(cand)) {
      for (int i : {0, 1, 2, 3})
        if (dsu[i].ok() and u != cand[i] and v != cand[i]) {
          dsu[i].join(u, v);
          if (not dsu[i].ok()) ans -= 1;
        }
      return;
    }

    es.emplace_back(u, v);
    bool cyc = dsu[0].join(u, v);

    if (dsu[0].d[u] < dsu[0].d[v]) swap(u, v);
    if (dsu[0].max_deg > 2) {
      cand.push_back(u);
      for (auto [a, b] : es) {
        if (a == u) cand.push_back(b);
        if (b == u) cand.push_back(a);
      }
      dsu = vector(size(cand), DSU(N));
      ans = 4;
      for (int i : {0, 1, 2, 3})
        for (auto [a, b] : es) {
          if (a != cand[i] and b != cand[i])
            dsu[i].join(a, b);
          if (not dsu[i].ok()) {
            ans -= 1;
            break;
          }
        }
      return;
    }

    if (not cyc) return;
    if (dsu[0].cyc_comp == 1) ans = dsu[0].size(u);
    if (dsu[0].cyc_comp > 1) ans = 0;
  }
};

Solver solver;
void Init(int N) { solver = Solver(N); }

void Link(int A, int B) { solver.link(A, B); }

int CountCritical() { return solver.ans; }
