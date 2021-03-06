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

const int P = 131;
const int MOD = 1e9+9;
inline int mad(int u, int v){
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
inline int mul(int u, int v){
	return (ll) u * v % MOD;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string s; getline(cin, s);
	int n = s.size();
	vector<int> p(n), hl(n), hr(n);
	p[0] = 1; for(int i = 1; i < n; ++i) p[i] = mul(p[i-1], P);
	hl[0] = s[0]; for(int i = 1; i < n; ++i) hl[i] = mad(mul(hl[i-1], P), s[i]);
	hr[n-1] = s[n-1]; for(int i = n-2; ~i; --i) hr[i] = mad(mul(hr[i+1], P), s[i]);

	vector<int> ans;
	if(hl[n-1] == hr[0]) ans.pb(0);
	for(int i = 0; i < n-1; ++i){
		int ul = hl[i], ur = mad(hl[n-1], MOD-mul(hl[i], p[n-i-1]));
		int vl = mad(hr[0], MOD-mul(hr[i+1], p[i+1])), vr = hr[i+1];
		int u = mad(ul, mul(ur, p[i+1]));
		int v = mad(vr, mul(vl, p[n-i-1]));
		if(u == v) ans.pb(i+1);
	}

	if(ans.size() == 0){
		cout << "none\n";
	} else {
		cout << ans.size() << ": ";
		for(int i: ans) cout << i << ' ';
	}

	return 0;
}
