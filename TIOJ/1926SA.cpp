// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii; typedef pair<ll,ll> pll;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i=0;i<(n);++i)
#define FOO(i,a,b) for(int i=(a);i<=int(b);++i)
#define OOF(i,a,b) for(int i=(a);i>=int(b);--i)
#define AI(x) begin(x),end(x)
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 
inline ll cdiv(ll x,ll m){return x/m+(x%m?(x<0)^(m>0):0);}
#ifdef OWO
#define safe cerr<<"\033[1;32m"<<__PRETTY_FUNCTION__<<" - "<<__LINE__<<" JIZZ\033[0m\n"
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
#else
#pragma GCC optimize("Ofast")
#define safe ((void)0)
#define debug(...) ((void)0)
#endif
const ll inf = 1e9, INF = 4e18;
#include "lib1926.h"
ll n, m;
ll sx, sy;
ll x, y;
bool go(ll x1, ll y1, ll x2, ll y2){
	if(x2 < 0 or x2 >= n or y2 < 0 or y2 >= m) return false;
	return Oshietekudasai(x2, y2, x1, y1);
}
bool walk(){
	static const int dxs[4] = {-1, 0, 0, 1};
	static const int dys[4] = {0, -1, 1, 0};
	for(int d = 0, dx, dy; d < 4; ++d){
		dx = dxs[d], dy = dys[d];
		if(go(x, y, x + dx * sx, y + dy * sy)){
			x += dx * sx, y += dy * sy;
			return true;
		}
	}
	return false;
}
int32_t main(){
	Init(&n, &m);
	x = y = 0;
	sx = n, sy = m;
	while(true){
		while(walk());
		if(sx == 1 and sy == 1) break;
		sx = max(sx >> 1, 1ll);
		sy = max(sy >> 1, 1ll);
	}
	Report(x, y);
	return 0;
}
