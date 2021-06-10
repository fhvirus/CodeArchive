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

const int N = 100001, C = 1000000, INF = 8e7;
int n, b, a[N];

inline int cdiv(int a, int b){ return (a + b - 1) / b;}
int calc(int x, int t){
	if(x <= t) return 0;
	if(t == 0) return INF;
	int maxLayer = __lg(x) + 1;
	if(maxLayer > t or (maxLayer == t and x > (1 << (t - 1)))) return INF;
	for(int h = 1; h <= t && h <= 20; ++h)
		if(((t - h) << h) > x)
			return cdiv(x - (1 << h), t - h - 1) - 1;
	return INF;
}

bool check(int m){
	int cnt = 0;
	for(int i = 0; i < n; ++i){
		cnt += calc(a[i], m);
		if(cnt > b) return false;
	}
	return true;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> b;
	for(int i = 0; i < n; ++i) cin >> a[i];

	int l = 1, r = *max_element(a, a + n), m;
	while(l < r){
		m = (l + r) / 2;
		if(check(m)) r = m;
		else l = m + 1;
	}

	cout << l;
	return 0;
}

