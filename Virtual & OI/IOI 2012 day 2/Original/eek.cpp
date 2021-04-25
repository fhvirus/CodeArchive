//Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define FOO(i,a,b) for(int i = (a); i <= (b); ++i)
#define AI(x) (x).begin(),(x).end()
template<typename I> bool chmax(I &a, I b){ return a < b ? (a = b, true) : false;}
template<typename I> bool chmin(I &a, I b){ return a > b ? (a = b, true) : false;}
#ifdef OWO
#define debug(args...) LKJ("[ " + string(#args) + " ]", args)
void LKJ(){ cerr << endl;}
template<typename I, typename...T> void LKJ(I&&x, T&&...t){ cerr<<x<<", ", LKJ(t...);}
template<typename I> void DE(I a, I b){ while(a < b) cerr << *a << " \n"[next(a) == b], ++a;}
#else
#define debug(...) 0
#define DE(...) 0
#endif
#ifdef OWO
int DistanceSum(int N, int *X, int *Y);
const int N = 1e5 + 225;
int x[N], y[N];
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	FOR(i,n) cin >> x[i] >> y[i];
	cout << DistanceSum(n, x, y) << endl;
	return 0;
}
#endif
const int M = 1000000000;
int DistanceSum(int n, int *x, int *y){
	const int dx[4] = {1, -1, 0, 0};
	const int dy[4] = {0, 0, 1, -1};
	vector<vector<int>> dp(n, vector<int>(n, M));
	for(int i = 0; i < n; ++i) dp[i][i] = 0;
	for(int i = 0; i < n; ++i){
		for(int j = i + 1; j < n; ++j){
			for(int d = 0; d < 4; ++d){
				if(x[i] + dx[d] == x[j] and y[i] + dy[d] == y[j])
					dp[i][j] = dp[j][i] = 1;
			}
		}
	}
	for(int k = 0; k < n; ++k){
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				if(dp[i][k] != M and dp[k][j] != M)
					chmin(dp[i][j], dp[i][k] + dp[k][j]);
				
	}
	ll ans = 0;
	for(int i = 0; i < n; ++i)
		for(int j = i + 1; j < n; ++j)
			ans += dp[i][j];
	return ans % M;
}
