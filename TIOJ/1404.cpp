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

const int N = 100100, INF = 1e9 + 7;
int m, n, t;
ll  x[N], h[N], b[N];
int lid[N], rid[N];

void init(){
	x[0] = -INF, x[m+1] = INF; h[0] = h[m+1] = -INF;
	for(int i = 1; i <= m; ++i) cin >> x[i] >> h[i];
	cin >> n >> t;
	for(int i = 1; i <= n; ++i) cin >> b[i];
}

bool lcmp(int i, int j, int k){
	// slope ik <= slope jk
	return 1ll * (h[k] - h[i]) * (x[k] - x[j])
		<= 1ll * (h[k] - h[j]) * (x[k] - x[i]);
}
bool rcmp(int i, int j, int k){
	// slope ik >= slope jk
	return 1ll * (h[k] - h[i]) * (x[k] - x[j])
		>= 1ll * (h[k] - h[j]) * (x[k] - x[i]);
}
int lpos(int i){
	if(lid[i] == 0 or h[i] >= h[lid[i]]) return 1;
	int l = 1, r = n + 1;
	while(l < r){
		int mid = (l + r) / 2;
		if(1ll * (h[i] - t) * (x[i] - x[lid[i]]) >=
			1ll * (h[i] - h[lid[i]]) * (x[i] - b[mid])) l = mid + 1;
		else r = mid;
	}
	return l;
}
int rpos(int i){
	if(rid[i] == m + 1 or h[i] >= h[rid[i]]) return n + 1;
	int l = 1, r = n + 1;
	while(l < r){
		int mid = (l + r) / 2;
		if(1ll * (t - h[i]) * (x[rid[i]] - x[i]) >
			1ll * (h[rid[i]] - h[i]) * (b[mid] - x[i])) l = mid + 1;
		else r = mid;
	}
	return l;
}
void solve(){
	init();

	// make segments and check
	// ->
	vector<int> stk; stk.pb(0);
	for(int i = 1; i <= m; ++i){
		while(stk.size() >= 2 and lcmp(end(stk)[-2], end(stk)[-1], i)) stk.pop_back();
		lid[i] = stk.back();
		stk.pb(i);
	}
	stk.clear(); stk.pb(m + 1);
	for(int i = m; i >= 1; --i){
		while(stk.size() >= 2 and rcmp(end(stk)[-2], end(stk)[-1], i)) stk.pop_back();
		rid[i] = stk.back();
		stk.pb(i);
	}

	vector<pii> seg;
	for(int i = 1; i <= m; ++i){
		int lp = lpos(i);
		int rp = rpos(i);
		debug(i, lid[i], rid[i], lp, rp);
		if(lp >= rp){
			cout << "you need more bulbs!\n";
			return;
		}
		seg.pb(lp, rp-1);
	}
	
	// greedy solve
	sort(AI(seg), [](pii a, pii b){ return a.ss < b.ss;});
	int lst = -INF;
	int ans = 0;
	for(auto [l, r]: seg){
		if(l <= lst and lst <= r) continue;
		++ans;
		lst = r;
	}
	cout << ans << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	while(cin >> m) solve();
	return 0;
}
