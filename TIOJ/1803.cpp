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

const int kN = 1000001;
const int M = 1e9 + 7;

int fac[kN], tot;

ll mpow(ll x, int e){
	ll r = 1;
	while(e) (e&1) && (r = r * x % M), x = x * x % M, e >>= 1;
	return r;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, k;
	fac[0] = 1;
	while(cin >> n >> k){
		int g = __gcd(n, k);
		if(g == 1){ cout << 0 << '\n'; continue; }
		while(tot < n) ++tot, fac[tot] = 1ll * fac[tot - 1] * tot % M;
		int eek = 0;
		for(int i = 2; i <= g; ++i) if(g % i == 0)
			eek = (eek + mpow(mpow(i, n / i) * fac[n / i] % M, M - 2)) % M;
		cout << 1ll * fac[n] * eek % M << '\n';
	}
	return 0;
}
