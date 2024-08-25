// keyword: Warnsdorff's rule/algorithm
#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int di[8] = {2, 2, 1, -1, -2, -2, -1, 1};
const int dj[8] = {1, -1, -2, -2, -1, 1, 2, 2};

int vis[8][8];
bool ok(int i, int j) { return 0 <= i and i < 8 and 0 <= j and j < 8 and (not vis[i][j]); }
int get_deg(int i, int j) {
  int res = 0;
  rep (d, 0, 8) res += ok(i + di[d], j + dj[d]);
  return res;
}

bool dfs(int i, int j, int t) {
  int ord[8] = {0, 1, 2, 3, 4, 5, 6, 7}, deg[8];
  vis[i][j] = t;
  if (t == 8 * 8) return true;
  rep (d, 0, 8) deg[d] = get_deg(i + di[d], j + dj[d]);
  sort(ord, ord + 8, [&](int u, int v) { return deg[u] < deg[v]; });
  rep (d, 0, 8) if (ok(i + di[ord[d]], j + dj[ord[d]]))
    if (dfs(i + di[ord[d]], j + dj[ord[d]], t + 1)) return true;
  vis[i][j] = 0;
  return false;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);
  int x, y;
  cin >> x >> y;
  assert(dfs(y - 1, x - 1, 1));
  rep (i, 0, 8) rep (j, 0, 8)
    cout << vis[i][j] << " \n"[j == 7];
}
