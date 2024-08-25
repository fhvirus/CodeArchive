#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

const int kN = 15;
int n;
bool vis[1 << kN];
void dfs(int u) {
  vis[u] = true;
  int v = (u << 1) & ((1 << n) - 1);
  if (not vis[v]) {
    dfs(v);
    cout << '0';
  }
  if (not vis[v | 1]) {
    dfs(v | 1);
    cout << '1';
  }
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  cin >> n;

  dfs(0);
  for (int i = 0; i < n; ++i)
    cout << '0';
  cout << '\n';

  return 0;
}
