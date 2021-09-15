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

vector<int> factor(int x){
	vector<int> f;
	while((x & 1) == 0) x >>= 1, f.pb(2);
	for(int i = 3; i * i <= x; i += 2){
		int q = x / i;
		if(q * i == x){
			f.pb(i), x = q;
			while((q = x / i) * i == x) f.pb(i), x = q;
		}
	}
	if(x > 1) f.pb(x);
	return f;
}

void solve(){
	int x, y; cin >> x >> y;
	if(x == y){ cout << "Zisk\n"; return; }
	if(x < y) swap(x, y);
	vector<int> fx = factor(x), fy = factor(y);
	for(int q, i = 0; ; ++i){
		q = x / fx[i];
		if(q >= y){ cout << "Danb\n"; return; }
		else x = q;
		q = y / fy[i];
		if(q >= x){ cout << "Zisk\n"; return; }
		else y = q;
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int t; cin >> t;
	for(; t; --t) solve();
	return 0;
}
