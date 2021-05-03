// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<bits/stdc++.h>
using namespace std;
typedef int64_t ll;
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}

void solve(int T, int n){
	vector<int> f(n + 1), d(n + 1), t(n + 1);
	for(int i = 1; i <= n; ++i) cin >> f[i];
	for(int i = 1; i <= n; ++i) cin >> d[i];
	for(int i = 1; i <= n; ++i) cin >> t[i];
	ll ans = 0, sum = 0;
	vector<int> cur;
	for(int i = 1; i <= n; ++i){
		T -= t[i];
		if(T <= 0) break;
		
		vector<int> tmp;
		for(int j = 0, v = f[i]; ; ++j, v -= d[i]){
			if(j >= T) break;
			if(v <= 0) break;
			tmp.pb(v);
			sum += v;
		}
		vector<int> nv;
		merge(AI(cur), AI(tmp), back_inserter(nv), greater<int>());
		while(nv.size() > T){
			sum -= nv.back();
			nv.pop_back();
		}

		nv.swap(cur);
		chmax(ans, sum);
	}
	cout << ans << '\n';
}

int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int T, n;
	while(cin >> T >> n) solve(T, n);
	return 0;
}