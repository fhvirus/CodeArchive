#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

struct SuffixArray {
  vi sa, lcp, rank;
  SuffixArray(const string& s, int lim=256) {
    int n = sz(s) + 1, k = 0, a, b;
    vi x(all(s)), y(n), ws(max(n, lim));
    x.push_back(0), sa = lcp = rank = y, iota(all(sa), 0);
    for (int j = 0, p = 0; p < n; j = max(1, j * 2), lim = p) {
      p = j, iota(all(y), n - j);
      rep(i,0,n) if (sa[i] >= j) y[p++] = sa[i] - j;
      fill(all(ws), 0);
      rep(i,0,n) ws[x[i]]++;
      rep(i,1,lim) ws[i] += ws[i - 1];
      for (int i = n; i--;) sa[--ws[x[y[i]]]] = y[i];
      swap(x, y), p = 1, x[sa[0]] = 0;
      rep(i,1,n) a = sa[i - 1], b = sa[i], x[b] =
        (y[a] == y[b] && y[a + j] == y[b + j]) ? p - 1 : p++;
    }
    rep(i,1,n) rank[sa[i]] = i;
    for (int i = 0, j; i < n - 1; lcp[rank[i++]] = k)
      for (k && k--, j = sa[rank[i] - 1];
          s[i + k] == s[j + k]; k++);
  }
};

struct DSU {
  vi f;
  DSU(int n) : f(n, -1) {}
  int find(int u) { return f[u] <= 0 ? u : f[u] = find(f[u]); }
  int size(int u) { return -f[find(u)]; }
  void merge(int u, int v) {
    u = find(u), v = find(v);
    if (u == v) return;
    f[u] += exchange(f[v], u);
  }
};

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  string S, T;
  cin >> S >> T;

  SuffixArray sa(S + '$' + T);

  vector<vector<pii>> qs(sz(T) + 1);
  int q;
  cin >> q;
  for (int a, b, i = 0; i < q; ++i) {
    cin >> a >> b;
    qs[b - a + 1].emplace_back(sz(S) + 1 + a - 1, i);
  }
  
  vector<vi> ms(sz(sa.sa));
  rep (i, 1, sz(sa.sa))
    ms[sa.lcp[i]].push_back(i);

  DSU dsu(sz(sa.sa));
  rep (i, 0, sz(sa.sa))
    dsu.f[i] = -(sa.sa[i] < sz(S));

  vi ans(q);
  for (int len = sz(T); len >= 1; --len) {
    for (int m : ms[len]) dsu.merge(m - 1, m);
    for (auto [pos, id] : qs[len])
      ans[id] = dsu.size(sa.rank[pos]);
  }

  for (int i : ans)
    cout << i << '\n';

  return 0;
}
