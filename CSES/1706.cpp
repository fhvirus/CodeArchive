#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct DSU {
  vi f;
  DSU (int n) : f(n, -1) {}
  int find(int u) { return f[u] < 0 ? u : f[u] = find(f[u]); }
  void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    if (f[u] > f[v]) swap(u, v);
    f[u] += exchange(f[v], u);
    return;
  }
  int size(int u) { return -f[find(u)]; }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int n, m;
  cin >> n >> m;

  DSU dsu(n);
  for (int a, b, i = 0; i < m; ++i) {
    cin >> a >> b;
    dsu.merge(a - 1, b - 1);
  }

  bitset<100001> bs;
  bs[0] = 1;
  for (int i = 0; i < n; ++i)
    if (dsu.find(i) == i)
      bs = bs | (bs << (dsu.size(i)));

  auto str = bs.to_string();
  reverse(all(str));
  cout << str.substr(1, n) << '\n';

  return 0;
}
