#include <bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int, int> pii;
#define ff first
#define ss second
#define AI(x) begin(x),end(x)
#define pb emplace_back
#ifdef OWO
#define debug(args...) LKJ("\033[1;32m[ " + string(#args) + " ]\033[0m", args)
template<class I> void LKJ(I&&x) { cerr << x << endl; }
template<class I, class...T> void LKJ(I&&x, T&&...t) { cerr << x << ", "; LKJ(t...); }
template<class I> void OI(I a, I b) { while (a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define OI(...) 0
#endif
 
int no[8];
int dfs(int row, int l, int m, int r) {
	if (row == 8) return 1;
	int p = (l | m | r | no[row]);
	int ans = 0;
	for (int i = 1; i < (1 << 8); i <<= 1) {
		if (p & i) continue;
		ans += dfs(row + 1, (l | i) << 1, m | i, (r | i) >> 1);
	}
	return ans;
}
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
	for (int i = 0; i < 8; ++i)
		for (int j = 0; j < 8; ++j) {
			char c; cin >> c;
			no[i] |= ((c == '*') << j);
		}
 
	cout << dfs(0, 0, 0, 0) << '\n';
 
	return 0;
}
