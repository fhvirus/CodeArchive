#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int, int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I> bool chmax(I &a, I b){ return a<b ? (a=b, true) : false; }
template<class I> bool chmin(I &a, I b){ return a>b ? (a=b, true) : false; }
#ifdef OWO
#define debug(args...) LKJ("\033[1;32m[ " + string(#args) + " ]\033[0m", args)
template<class I> void LKJ(I&&x){ cerr << x << endl; }
template<class I, class...T> void LKJ(I&&x, T&&...t){ cerr << x << ", "; LKJ(t...); }
template<class I> void OI(I a, I b){ while(a < b) cerr << *a << " \n"[next(a) == b], ++a; }
#else
#define debug(...) 0
#define OI(...) 0
#endif

#pragma GCC optimize("Ofast")

const int kN = 505;
const ll INF = 1e18;
int N, a[kN], g[kN][kN];

void upd(ll &u, ll v, int i, int j){
	if(v <= -INF) return;
	if(g[i][j] == 1) return;
	u = max(u, v + g[i][j]);
}
void upd(ll &u, ll v, int i, int j, int k){
	if(g[i][j] == 1 or g[i][k] == 1 or g[j][k] == 1) return;
	if(v <= -INF) return;
	u = max(u, v + g[i][j] + g[j][k]);
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N;
	if(N == 1){ cout << -1 << endl; return 0; }

	for(int i = 1; i <= N; ++i) cin >> a[i];
	for(int i = 1; i <= N; ++i)
		for(int j = i+1; j <= N; ++j)
			g[i][j] = __gcd(a[i], a[j]);

	vector<vector<ll>> dp(N+1, vector<ll>(N+1, -INF));
	for(int i = 1; i <= N; ++i) dp[i][i-1] = 0;
	for(int r = 2; r <= N; ++r){
		for(int l = r-1; l >= 1; --l){
			ll cur = -INF;
			upd(cur, dp[l+1][r-1], l, r);
			if(l+2 <= r){
				for(int k = l+1; k <= r-1; ++k)
					upd(cur, dp[l+1][k-1] + dp[k+1][r-1], l, k, r);
			}
			for(int k = l+1; k <= r-1; ++k)
				cur = max(cur, dp[l][k] + dp[k+1][r]);
			dp[l][r] = cur;
		}
	}

	cout << max(-1ll, dp[1][N]) << endl;

	return 0;
}

