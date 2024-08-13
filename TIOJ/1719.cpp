#include <bits/stdc++.h>
using namespace std;
#define rep(i, a, b) for(int i = a; i < (b); ++i)
#define all(x) begin(x), end(x)
#define sz(x) (int)(x).size()
typedef long long ll;
typedef pair<int, int> pii;
typedef vector<int> vi;

bool can(vi &box, vi &item, int i, int st) {
  if (i < 0) return true;
  bool ans = false;
  rep (j, st, sz(box)) {
    if (item[i] > box[j]) continue;
    box[j] -= item[i];
    ans |= can(box, item, i - 1, i > 0 and item[i - 1] == item[i] ? j : 0);
    box[j] += item[i];
    if (ans) break;
  }
  return ans;
}

int main() {
  cin.tie(0)->sync_with_stdio(0);
  cin.exceptions(cin.failbit);

  int M, N;
  cin >> M >> N;

  vi box(M), item(N);
  for (int &i : box) cin >> i;
  for (int &i : item) cin >> i;
  sort(all(item));

  int box_sum = accumulate(all(box), 0), ans = 0;
  for (int i = 0, item_sum = 0; i < N; ++i) {
    item_sum += item[i];
    if (item_sum > box_sum or not can(box, item, i, 0)) break;
    ans = i + 1;
  }

  cout << ans << '\n';

  return 0;
}
