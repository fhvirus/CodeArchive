#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;
template <class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

struct Kunai { int x, y, d; };
struct RangeCompression : vi {
  void init() { sort(all()); erase(unique(all()), end()); }
  int operator() (int v) { return (int) (lower_bound(all(), v) - begin()); }
};
struct FenwickTree {
  vi val;
  FenwickTree(int n) : val(n, 0) {}
  void update(int p, int v) {
    for (; p < sz(val); p += p & -p)
      val[p] += v;
  }
  int query(int p) {
    int res = 0;
    for (; p > 0; p -= p & -p)
      res += val[p];
    return res;
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int W, H;
  cin >> W >> H;

  int N;
  cin >> N;

  vector<Kunai> kunai(N);
  for (auto &[x, y, d] : kunai)
    cin >> x >> y >> d;

  // Building linked list of possible collision
  // 0/3: diagonal, 1/4: anti-diagonal, 2/5: orthogonal
  // [0, 3) : prev, [3, 6) : next
  vector<array<int, 6>> link(N);
  for (auto &v : link) fill(all(v), -1);

  vi key(N), val(N);
  const auto build_link = [&](vi &id, int dir) -> void {
    sort(all(id), [&](int i, int j) { return tie(key[i], val[i]) < tie(key[j], val[j]); });
    rep (i, 1, sz(id)) if (key[id[i]] == key[id[i - 1]]) {
      link[id[i]][dir] = id[i - 1];
      link[id[i - 1]][dir + 3] = id[i];
    }
    id.clear();
  };
  array<vi, 2> id;
  // diagonal: (0, 1) and (3, 2)
  rep (i, 0, N) key[i] = kunai[i].x - kunai[i].y, val[i] = kunai[i].x;
  rep (i, 0, N) id[kunai[i].d == 0 or kunai[i].d == 1].push_back(i);
  build_link(id[1], 0); build_link(id[0], 0);
  // anti-diagonal: (0, 3) and (1, 2)
  rep (i, 0, N) key[i] = kunai[i].x + kunai[i].y;
  rep (i, 0, N) id[kunai[i].d == 0 or kunai[i].d == 3].push_back(i);
  build_link(id[1], 1); build_link(id[0], 1);
  // horizontal: (0, 2)
  rep (i, 0, N) key[i] = kunai[i].y;
  rep (i, 0, N) id[kunai[i].d == 0 or kunai[i].d == 2].push_back(i);
  build_link(id[1], 2);
  // vertical: (3, 1)
  rep (i, 0, N) key[i] = kunai[i].x, val[i] = kunai[i].y;
  build_link(id[0], 2);

  const int n_or_p[3][4] = {
    {3, 0, 0, 3}, // diagonal
    {3, 3, 0, 0}, // anti-diagonal
    {3, 0, 0, 3}, // orthogonal
  };
  const int dir_xor[3] = {1, 3, 2};

  MinHeap<tuple<int, int, int>> events;
  vi dur(N, INT_MAX);
  const auto crash_time = [&](int i, int j) -> int {
    return abs(kunai[i].x - kunai[j].x) + abs(kunai[i].y - kunai[j].y); };
  const auto update_match = [&](int i) -> void {
    if (dur[i] != INT_MAX) return;
    int ct = INT_MAX;
    rep (d, 0, 3) {
      int j = link[i][d + n_or_p[d][kunai[i].d]];
      if (j != -1 and (kunai[i].d ^ dir_xor[d]) == kunai[j].d)
        ct = min(ct, crash_time(i, j));
    }
    if (ct == INT_MAX) return;
    rep (d, 0, 3) {
      int j = link[i][d + n_or_p[d][kunai[i].d]];
      if (j != -1 and (kunai[i].d ^ dir_xor[d]) == kunai[j].d and crash_time(i, j) == ct)
        events.emplace(ct, i, j);
    }
  };
  rep (i, 0, N) update_match(i);

  while (not events.empty()) {
    int cur_t = get<0>(events.top());
    vi batch;
    while (not events.empty()) {
      auto [t, i, j] = events.top();
      if (t != cur_t) break;
      events.pop();
      if (dur[i] < t or dur[j] < t) continue;
      for (int u : {i, j}) if (dur[u] == INT_MAX)
        dur[u] = t, batch.push_back(u);
    }
    for (int i : batch) rep (d, 0, 6) if (link[i][d] != -1) {
      link[link[i][d]][(d + 3) % 6] = link[i][(d + 3) % 6];
      if (dur[link[i][d]] == INT_MAX) update_match(link[i][d]);
    }
  }

  // Calculate segment from dur.
  const int dx[4] = {1, 0, -1, 0};
  const int dy[4] = {0, -1, 0, 1};
  vector<tuple<int, int, int>> vert_seg, hori_seg;
  rep (i, 0, N) {
    auto [sx, sy, d] = kunai[i];
    int t = dur[i] / 2;
    int ex = clamp(sx + t * dx[d], 1, W);
    int ey = clamp(sy + t * dy[d], 1, H);
    if (d == 1 or d == 2) swap(sx, ex), swap(sy, ey);
    if (d & 1) vert_seg.emplace_back(sx, sy, ey);
    else hori_seg.emplace_back(sy, sx, ex);
  }

  // Remove overlapped segments.
  auto remove_overlapped = [](vector<tuple<int, int, int>> &segs) -> void {
    sort(all(segs));
    vector<tuple<int, int, int>> res;
    int last_y = -1, last_r = -1;
    for (auto [y, l, r] : segs) {
      if (last_y != y) last_r = -1;
      l = max(last_r + 1, l);
      if (l > r) continue;
      if (l == last_r + 1) get<2>(res.back()) = r;
      else res.emplace_back(y, l, r);
      last_y = y, last_r = r;
    }
    segs.swap(res);
  };
  remove_overlapped(vert_seg);
  remove_overlapped(hori_seg);

  // Sweep to calculate answer.
  vector<pii> vert_ends;
  for (auto [x, u, d] : vert_seg) {
    vert_ends.emplace_back(u, x);
    vert_ends.emplace_back(d + 1, -x);
  }
  sort(all(vert_ends));

  int64_t ans = 0;
  RangeCompression xs;
  for (auto [x, u, d] : vert_seg) {
    xs.push_back(x);
    ans += d - u + 1;
  }
  for (auto [y, l, r] : hori_seg) {
    xs.push_back(l);
    xs.push_back(r);
  }
  xs.init();

  FenwickTree ft(sz(xs) + 1);
  for (int i = 0, j = 0; i < sz(vert_ends) or j < sz(hori_seg); ) {
    int cur_y = min(i < sz(vert_ends) ? vert_ends[i].first : H + 1,
        j < sz(hori_seg) ? get<0>(hori_seg[j]) : H + 1);
    for (; i < sz(vert_ends) and vert_ends[i].first == cur_y; ++i) {
      int x = vert_ends[i].second;
      ft.update(xs(abs(x)) + 1, x < 0 ? -1 : 1);
    }
    for (; j < sz(hori_seg); ++j) {
      auto [y, l, r] = hori_seg[j];
      if (y != cur_y) break;
      ans += (r - l + 1) - (ft.query(xs(r) + 1) - ft.query(xs(l)));
    }
  }

  cout << ans << '\n';

  return 0;
}
