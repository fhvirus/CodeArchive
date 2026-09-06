#include <bits/stdc++.h>
using namespace std;

template<class T>
struct Point3D {
  typedef Point3D P;
  T x, y, z;
  explicit Point3D(T _x = 0, T _y = 0, T _z = 0) : x(_x), y(_y), z(_z) {}
  auto operator <=> (const P& o) const = default;
  P operator+(P p) const { return P(x+p.x, y+p.y, z+p.z); }
  P operator-(P p) const { return P(x-p.x, y-p.y, z-p.z); }
  T dist2() const { return x*x + y*y + z*z; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  typedef double T;
  typedef Point3D<T> P;

  int N;
  cin >> N;

  vector<P> p(N);
  for (auto &[x, y, z] : p) cin >> x >> y >> z;

  T len, ans2 = 3 * pow(2, 33 * 2);
  {
    mt19937 mt(7122);
    for (int i = 0; i < 4 * N; ++i) {
      auto u = mt() % N, v = mt() % N;
      while (v == u) v = mt() % N;
      ans2 = min(ans2, (p[u] - p[v]).dist2());
    }
    len = ceil(sqrt(ans2));
  }

  typedef Point3D<int64_t> Pi;
  vector<Pi> box(N);
  for (int i = 0; i < N; ++i) {
    auto [x, y, z] = p[i];
    box[i] = Pi(floor(x / len), floor(y / len), floor(z / len));
  }

  auto bkt = box;
  ranges::sort(bkt);

  vector<int> content(N), bkt_size(N);
  for (int i = 0; i < N; ++i) {
    int id = (int) (ranges::lower_bound(bkt, box[i]) - begin(bkt));
    content[id + bkt_size[id]] = i;
    ++bkt_size[id];
  }

  int ansi = -1, ansj = -1;
  for (int i = 0; i < (int)size(bkt); ++i) if (bkt_size[i] > 0) {
    Pi b = bkt[i];
    for (int dx : {-1, 0, 1}) for (int dy : {-1, 0, 1}) for (int dz : {-1, 0, 1}) {
      Pi ob(b.x + dx, b.y + dy, b.z + dz);
      int j = (int) (ranges::lower_bound(bkt, ob) - begin(bkt));
      if (j == (int)size(bkt) or bkt[j] != ob) continue;
      for (int di = 0; di < bkt_size[i]; ++di)
        for (int dj = 0; dj < bkt_size[j]; ++dj) if (i + di != j + dj) {
          int pi = content[i + di], pj = content[j + dj];
          auto d2 = (p[pi] - p[pj]).dist2();
          if (d2 <= ans2)
            ans2 = d2, ansi = pi, ansj = pj;
        }
    }
  }

  if (ansi > ansj) swap(ansi, ansj);
  printf("WARNING: galaxy%d and galaxy%d in %.06Lf Uu\n", ansi + 1, ansj + 1, sqrt((long double)ans2));

  return 0;
}
