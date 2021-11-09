// Knapsack DP is harder than FFT.
#include <iostream>
#include <algorithm>
#include <vector>
#include <utility>
using namespace std;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 

const int INF = 1e9+7;

vector<pii> input(int &N, bool canMerge){
	vector<pii> v(N+1);
	for(int i = 1; i <= N; ++i)
		cin >> v[i].ff >> v[i].ss;
	sort(AI(v));
	if(canMerge){
		int p = 1;
		for(int i = 1; i <= N; ++i){
			while(p > 1 and v[p-1].ss <= v[i].ss) --p;
			v[p++] = v[i];
		}
		N = p-1;
		v.erase(begin(v)+p, end(v));
	}
	// For I don't have too check if i < N in DP phase.
	v.pb(0, 0);
	return v;
}

void solve(){
	int N, M; cin >> N >> M;
	vector<pii> pro = input(N, 1);
	vector<pii> stu = input(M, 1);

	vector<vector<pii>> dp(N+2, vector<pii>(M+2, pii(INF, INF)));
	dp[0][0] = pii(0, 0);
	for(int i = 0; i <= N; ++i){
		for(int j = 0; j <= M; ++j){
			auto &[p, s] = dp[i][j];
			chmax(p, pro[i].ff + pro[i].ss);
			chmax(s, stu[j].ff + stu[j].ss);
			chmin(dp[i+1][j].ff, min(p, s + pro[i+1].ss));
			chmin(dp[i][j+1].ss, min(p + stu[j+1].ss, s));
		}
	}

	cout << min(dp[N][M].ff, dp[N][M].ss) << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T; cin >> T;
	for(; T; --T) solve();
	return 0;
}

