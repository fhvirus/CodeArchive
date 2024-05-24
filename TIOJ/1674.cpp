#include <cstdio>
#include <cstdint>
#include <algorithm>
#include <utility>
#include <vector>

const int kN = 200002;
const int64_t INF = 1e18;
int N;
int64_t K;
std::vector<std::pair<int, int>> adj[kN];
bool used[kN];
int size[kN];

int dfs_size(int u, int p) {
  size[u] = 1;
  for (auto [v, w] : adj[u]) if (!used[v] and v != p)
    size[u] += dfs_size(v, u);
  return size[u];
}

int find_centroid(int r) {
  int tot = dfs_size(r, r), p = r;
  bool found = false;
  while (not found) {
    found = true;
    for (auto [v, w] : adj[r]) if (!used[v] and v != p and size[v] * 2 > tot) {
      found = false;
      p = r, r = v;
      break;
    }
  }
  return r;
}

void get_d(int u, int64_t d, int64_t max_pre, int64_t cur_sub, int64_t max_sub, int p, std::vector<int64_t> &cd) {
  max_pre = std::max(max_pre, d);
  max_sub = std::max(max_sub, cur_sub);
  cd.push_back(max_sub >= K ? INF : max_pre);
  for (auto [v, w] : adj[u]) if (!used[v] and v != p)
    get_d(v, d + w, max_pre, std::max(cur_sub, 0l) + w, max_sub, u, cd);
}

int64_t calc(std::vector<int64_t> &ds) {
  int n = (int) ds.size();
  int64_t ans = 0;
  for (int i = 0, j = n; i < n; ++i) {
    while (j > 0 and ds[i] + ds[j - 1] >= K) --j;
    ans += n - j;
  }
  return ans;
}

int64_t solve(int r) {
  int c = find_centroid(r);
  used[c] = true;

  int64_t ans = 0;
  std::vector<int64_t> ds, cd;

  ds.push_back(0);
  for (auto [v, w] : adj[c]) if (!used[v]) {
    get_d(v, w, 0, w, 0, v, cd);
    sort(cd.begin(), cd.end());
    ans -= calc(cd);
    ds.insert(ds.end(), cd.begin(), cd.end());
    cd.clear();
  }

  sort(ds.begin(), ds.end());
  ans += calc(ds);
  ans /= 2;

  for (auto [v, w] : adj[c]) if (!used[v])
    ans += solve(v);
  return ans;
}

int main() {
  scanf("%d%ld", &N, &K);
  for (int A, B, C, i = 1; i < N; ++i) {
    scanf("%d%d%d", &A, &B, &C);
    adj[A].emplace_back(B, C);
    adj[B].emplace_back(A, C);
  }

  printf("%ld\n", solve(1));

  return 0;
}
