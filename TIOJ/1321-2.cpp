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

const int P = 131, I = 190839696;
const int MOD = 1e9+7;
inline int mad(int u, int v){
	u += v - MOD;
	u += MOD & (u >> 31);
	return u;
}
inline int mul(int u, int v){
	return (ll) u * v % MOD;
}
inline int mow(int x, int e){
	int r = 1;
	while(e){
		if(e & 1) r = mul(r, x);
		x = mul(x, x);
		e >>= 1;
	}
	return r;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	string s; getline(cin, s);
	int n = s.size();

	int hls = s[0]; for(int i = 1; i < n; ++i) hls = mad(mul(hls, P), s[i]);
	int hrs = s[n-1]; for(int i = n-2; ~i; --i) hrs = mad(mul(hrs, P), s[i]);
	int ul = 0, vr = hrs;
	int pl = 1, pr = mow(P, n);

	vector<int> ans;
	if(hls == hrs) ans.pb(0);
	for(int i = 0; i < n-1; ++i){
		ul = mad(mul(ul, P), s[i]);
		vr = mul(mad(vr, MOD-s[i]), I);
		pl = mul(pl, P);
		pr = mul(pr, I);

		int ur = mad(hls, MOD-mul(ul, pr));
		int vl = mad(hrs, MOD-mul(vr, pl));
		int u = mad(ul, mul(ur, pl));
		int v = mad(vr, mul(vl, pr));
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
