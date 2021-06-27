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

const int kN = 1001, kQ = 2002, kW = 2002, kL = 11;
int N, W, Q;
int w[kN], v[kN], c[kN];
int x[kQ], d[kQ];
int mem[kL][kW];
double ans[kQ];

double chk(int w, int v, int c, int dp[kW]){
	double res = dp[W];
	if(w <= W) chmax(res, double(dp[W - w] + v));
	for(int i = 1; i < w and i <= W; ++i)
		chmax(res, dp[W - i] + v * i / double(w) - c);
	return res;
}

void lst(int p, int dp[kW]){
	double cur = chk(w[p], v[p], c[p], dp);
	for(int i = 0; i <= Q; ++i){
		if(x[i] == p)
			cur = chk(w[p], v[p], d[i], dp);
		chmax(ans[i], cur);
	}
}

void put(int l, int r, int sc[kW], int dp[kW]){
	for(int i = 0; i <= W; ++i) dp[i] = sc[i];
	for(int i = l; i <= r; ++i){
		for(int j = W; j >= w[i]; --j)
			chmax(dp[j], dp[j - w[i]] + v[i]);
	}
}

void gem(int l, int r, int k = 1){
	int *dp = mem[k], *sc = mem[k-1];

	if(l == r){ 
		lst(l, sc);
		return;
	}

	int m = (l + r) / 2;

	put(l, m, sc, dp);
	gem(m+1, r, k + 1);

	put(m+1, r, sc, dp);
	gem(l, m, k + 1);
}

void solve(){
	cin >> N >> W;
	for(int i = 1; i <= N; ++i) cin >> w[i] >> v[i] >> c[i];
	cin >> Q;
	for(int i = 1; i <= Q; ++i) cin >> x[i] >> d[i];

	fill(ans, ans + Q + 1, 0);

	gem(1, N);

	for(int i = 0; i <= Q; ++i) cout << ans[i] << '\n';
	return;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	cout << setprecision(8) << fixed;
	for(; t; --t) solve();
	return 0;
}
