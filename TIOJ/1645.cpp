// keyword: minimum manhattan spanning tree
// reference: https://github.com/brianbbsu/8BQube/blob/master/codebook/9_Else/ManhattanMST.cpp
// reference: Hai Zhou, N. Shenoy and W. Nicholls, "Efficient minimum spanning tree construction without Delaunay triangulation [VLSI CAD],"
//            doi: 10.1109/ASPDAC.2001.913303
// reference: https://shininglionking.blogspot.com/2014/08/c-efficient-minimum-spanning-tree.html
//
// There are eight cases,
// but we only consider the case
// R1: {x <= x_i, y - x >= y_i - x_i} for point i,
// find the point with min x + y for each i,
// then rotate / flip to solve the others.
// We sweep by x + y and maintain a set of active points
// whose R1 is currently empty.
// For each point, if it is in any active point's R1,
// add an edge (since it must be the min x + y)
// and remove that point from the active set.
// If the active points are ordered by x,
// then they must also (weakly) ordered by x - y
// (draw out some points to see it).
// We then get the active points one by one,
// from right to left (in order of -x)
#include <cstdio>
#include <algorithm>
#include <map>

struct Point { int x, y; };
struct Edge {
  int w, u, v;
  bool operator < (const Edge &o) const { return w < o.w; }
};

const int kF = 200000;
int N, M, F;
Point ps[kF];
int id[kF];

Edge es[kF * 4];
int tot = 0;

void solve() {
  std::sort(id, id + F, [](int a, int b)
      { return ps[a].x + ps[a].y < ps[b].x + ps[b].y; });
  std::map<int, int> mp;
  for (int i = 0; i < F; ++i) {
    int u = id[i];
    for (auto it = mp.lower_bound(-ps[u].x);
        it != mp.end(); it = mp.erase(it)) {
      int v = it->second;
      if (ps[v].x - ps[v].y < ps[u].x - ps[u].y) break;
      es[tot++] = {ps[u].x + ps[u].y - ps[v].x - ps[v].y, u, v};
    }
    mp[-ps[u].x] = u;
  }
}

int find(int u)
{ return id[u] == u ? u : id[u] = find(id[u]); }

int main() {
  scanf("%d %d %d", &N, &M, &F);
  for (int i = 0; i < F; ++i)
    scanf("%d %d", &ps[i].x, &ps[i].y);

  for (int i = 0; i < F; ++i) id[i] = i;
  for (int r : {0, 1}) {
    solve();
    for (int i = 0; i < F; ++i) std::swap(ps[i].x, ps[i].y);
    solve();
    if (r == 0) for (int i = 0; i < F; ++i) ps[i].x *= -1;
  }

  std::sort(es, es + tot);

  for (int i = 0; i < F; ++i) id[i] = i;

  long long ans = 0;
  for (int i = 0; i < tot; ++i) {
    auto [w, u, v] = es[i];
    u = find(u); v = find(v);
    if (u == v) continue;
    ans += w;
    id[v] = u;
  }

  printf("%lld\n", ans);

  return 0;
}
