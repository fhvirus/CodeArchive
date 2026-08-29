#include <bits/stdc++.h>
using namespace std;

template <class T>
struct RangeCompression : vector<T> {
  typedef vector<T> V; using V::begin, V::end;
  bool good = false;
  int init() {
    sort(begin(), end());
    this->erase(unique(begin(), end()), end());
    good = true;
    return (int)this->size();
  }
  int operator () (T x) {
    if (not good) exit(-1);
    return (int) (lower_bound(begin(), end(), x) - begin());
  }
};

struct Rectangle {
  int l, d, r, u;
  array<int, 3> rgb;
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int N;
  cin >> N;

  vector<Rectangle> rec(N);
  RangeCompression<int> comp_x, comp_y;
  for (auto &[l, d, r, u, rgb] : rec) {
    cin >> l >> d >> r >> u;
    if (l > r) swap(l, r);
    if (d > u) swap(d, u);
    for (int c : {0, 1, 2}) cin >> rgb[c];
    comp_x.push_back(l); comp_x.push_back(r);
    comp_y.push_back(d); comp_y.push_back(u);
  }

  int w = comp_x.init(), h = comp_y.init();
  for (auto &[l, d, r, u, _] : rec) {
    l = comp_x(l); r = comp_x(r);
    d = comp_y(d); u = comp_y(u);
  }

  vector<vector<int>> cnt;
  for (int c : {-1, 0, 1, 2}) {
    vector a(h, vector(w, 0));
    for (const auto &[l, d, r, u, rgb] : rec) {
      int v = (c == -1 ? 1 : rgb[c]);
      a[d][l] += v;
      a[d][r] -= v;
      a[u][l] -= v;
      a[u][r] += v;
    }

    for (int i = 1; i < h; ++i)
      for (int j = 0; j < w; ++j)
        a[i][j] += a[i-1][j];
    for (int i = 0; i < h; ++i)
      for (int j = 1; j < w; ++j)
        a[i][j] += a[i][j-1];

    if (c == -1) { swap(cnt, a); continue; }
    vector<int> stat(256);
    for (int i = 0; i + 1 < h; ++i) {
      for (int j = 0; j + 1 < w; ++j) if (cnt[i][j] != 0) {
        int area = (comp_y[i + 1] - comp_y[i]) * (comp_x[j + 1] - comp_x[j]);
        int val = (a[i][j] + cnt[i][j] - 1) / cnt[i][j];
        stat[val] += area;
      }
    }
    cout << (int) (ranges::max_element(stat) - begin(stat)) << " \n"[c == 2];
  }

  return 0;
}
