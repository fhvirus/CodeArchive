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

const int MOD = 1e9 + 7;
int mad(int u, int v){
	u += v - MOD;
	u += MOD & (u>>31);
	return u;
}
int mul(int u, int v){
	return (ll) u * v % MOD;
}

const int kN = 64;
int n; ll t;
int a[kN], c[kN];
int b[kN][kN][kN], d[kN][kN];

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> t; a[0] = 1;
	for(int i = 1; i <= n; ++i) cin >> a[i];

	for(int i = 0; i <= n; ++i) b[0][i][i] = 1;
	b[0][1][0] = 1;
	for(int l = 1; (1ll<<l) <= t; ++l){
		auto x = b[l-1];
		auto y = b[l];
		auto z = d;
		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= n; ++j)
				for(int k = 0; k <= n; ++k)
					y[i][j] = mad(y[i][j], mul(x[i][k], x[k][j]));

		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= n; ++j)
				z[i][j] = y[i][j];
		for(int j = 0; j <= n; ++j)
			z[l][j] = mad(z[l][j], MOD-y[l-1][j]);

		for(int i = 0; i <= n; ++i)
			for(int j = 0; j <= n; ++j)
				y[i][j] = z[i][j];
		for(int j = 0; j <= n; ++j)
			y[l+1][j] = mad(y[l+1][j], z[l][j]);
	}

	for(int l = 63 - __builtin_clzll(t); l >= 0; --l)
		if((t>>l) & 1){
			for(int i = 0; i <= n; ++i) c[i] = 0;
			for(int i = 0; i <= n; ++i)
				for(int j = 0; j <= n; ++j)
					c[i] = mad(c[i], mul(b[l][i][j], a[j]));
			for(int i = 0; i <= n; ++i) a[i] = c[i];
		}

	for(int i = 1; i <= n; ++i)
		cout << a[i] << ' ';
	return 0;
}
