// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#pragma GCC optimize("Ofast")
#define debug(...) ((void)0)
#endif

const int kC = 100000000;

vector<int> getFactor(int x){
	vector<int> f;
	for(int i = 1; i * i <= x; ++i){
		if(x % i == 0){
			f.pb(i);
			if(i * i != x)
				f.pb(x / i);
		}
	}
	sort(AI(f));
	return f;
}
vector<vector<int>> getFF(vector<int> &f){
	vector<vector<int>> ff(f.size(), vector<int>());
	for(int i = 0, n = (int) f.size(); i < n; ++i){
		for(int j = 0; j < i; ++j)
			if(f[i] % f[j] == 0) ff[i].pb(j);
	}
	return ff;
}

bool solve(){
	int x, y;
	cin >> x >> y;
	if(x == y) return 0;
	if(x == 1 or y == 1) return 1;

	vector<int> fx = getFactor(x);
	vector<int> fy = getFactor(y);
	vector<vector<int>> ffx = getFF(fx);
	vector<vector<int>> ffy = getFF(fy);
	debug(fx, ffx);
	debug(fy, ffy);

	int n = fx.size();
	int m = fy.size();
	vector<vector<int>> dp(n, vector<int>(m, 0));
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < m; ++j){
			if(i == 0 and j == 0) continue;
			if(fx[i] == fy[j]) continue;
			if(fx[i] > fy[j])
				for(int k: ffx[i]) dp[i][j] = dp[i][j] or !dp[k][j];
			else
				for(int k: ffy[j]) dp[i][j] = dp[i][j] or !dp[i][k];
		}
	}
	return dp[n-1][m-1];
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t;
	assert(cin >> t);
	assert(1 <= t and t <= 10);
	for(; t; --t){
		bool ans = solve();
		cout << (ans ? "Danb\n" : "Zisk\n");
	}
	return 0;
}

