#include <bits/stdc++.h>
using namespace std;

const int kN = 20, kM = 9;
typedef bitset<kN * kN> bs;

int N, M, K, h[kM * 4], w[kM * 4], shift[kM * 4], id[kM * 4];
bs ps[kM * 4];

auto rot90(int n, int m, const vector<string>& a) {
  vector b(m, string(n, ' '));
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      b[m - 1 - j][i] = a[i][j];
  return b;
}
auto to_bs(int n, int m, const vector<string>& a) {
  bs b;
  for (int i = 0; i < n; ++i)
    for (int j = 0; j < m; ++j)
      b[i * N + j] = (a[i][j] != '0');
  return b;
}

bool dfs(int i, int j, bs has, auto& used, auto& pos) {
  if (i == N) return true;
  for (int k = 0; k < K; ++k) if (not used[id[k]]) {
    if (i + h[k] > N or j + w[k] - shift[k] > N or j - shift[k] < 0) continue;
    auto p = ps[k] << (i * N + j - shift[k]);
    if ((has & p).any()) continue;
    used[id[k]] = true;
    pos[k] = {i, j};
    p |= has;
    int npos = (int) (~p)._Find_next(i * N + j);
    if (dfs(npos / N, npos % N, p, used, pos)) return true;
    pos[k] = {-1, -1};
    used[id[k]] = false;
  }
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  while (cin >> N >> M, N != 0) {
    K = 0;
    for (int i = 0; i < M; ++i) {
      int x, y;
      cin >> x >> y;
      vector<string> a(x);
      for (auto &s : a) cin >> s;

      h[K] = x, w[K] = y, id[K] = i;
      ps[K++] = to_bs(x, y, a);

      auto b = a;
      for (int d = 1; d < 4; ++d) {
        b = rot90(x, y, b);
        swap(x, y);
        if (b == a) break;
        h[K] = x, w[K] = y, id[K] = i;
        ps[K++] = to_bs(x, y, b);
      }
    }
    for (int k = 0; k < K; ++k)
      shift[k] = (int) ps[k]._Find_first();

    vector<bool> used(M, false);
    vector pos(K, pair(-1, -1));
    dfs(0, 0, bs(), used, pos);

    vector ans(N, string(N, ' '));
    for (int k = 0; k < K; ++k) if (pos[k] != pair(-1, -1)) {
      auto [si, sj] = pos[k];
      for (int i = 0; i < h[k]; ++i)
        for (int j = 0; j < w[k]; ++j)
          if (ps[k][i * N + j]) ans[si + i][sj + j - shift[k]] = char('1' + id[k]);
    }
    auto b = ans;
    for (int d = 1; d < 4; ++d) {
      b = rot90(N, N, b);
      if (b < ans) ans = b;
    }
    for (auto &s : ans) cout << s << '\n';
    cout << '\n';
  }

  return 0;
}
