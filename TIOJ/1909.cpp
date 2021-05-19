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

const int N = 1000001;
int n;
vector<int> adj[N];
ll ans[N];

int dfs(int u, int p){
	int s = 1;
	for(int v: adj[u]) if(v != p){
		int cs = dfs(v, u);
		ans[u] += 1ll * s * cs;
		s += cs;
	}
	ans[u] += 1ll * s * (n - s);
	return s;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	vector<int> a(n + 2); a[0] = a[n + 1] = INT_MAX;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	
	vector<int> l(n + 2, 0), r(n + 2, 0);
	vector<int> stk;
	stk.pb(0);
	for(int i = 1; i <= n; ++i){
		while(a[stk.back()] < a[i]) stk.pop_back();
		l[i] = stk.back();
		stk.pb(i);
	}
	stk.clear(); stk.pb(n + 1);
	for(int i = n; i >= 1; --i){
		while(a[stk.back()] < a[i]) stk.pop_back();
		r[i] = stk.back();
		stk.pb(i);
	}

	for(int i = 1; i <= n; ++i){
		int u = (a[l[i]] < a[r[i]] ? l[i] : r[i]);
		if(u == 0 or u == n + 1) continue;
		adj[u].pb(i); adj[i].pb(u);
	}

	dfs(1, 0);

	ll ansv = 0, ansi = 0;
	for(int i = 1; i <= n; ++i) if(chmax(ansv, ans[i])) ansi = i;
	cout << ansv * 2 << ' ' << ansi;
	return 0;
}
