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

const int inf = INT_MAX;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	vector<pii> seg(n), noi;
	for(int i = 0; i < n; ++i) cin >> seg[i].ff >> seg[i].ss;
	
	noi = seg;
	sort(AI(noi), [](pii a, pii b){ return a.ss != b.ss ? a.ss < b.ss : a.ff > b.ff; });
	int m = 0;
	for(int i = 1; i < n; ++i)
		if(noi[i].ff > noi[m].ff) noi[++m] = noi[i]; 
	++m;
	noi.erase(begin(noi) + m, end(noi));
	int lg = __lg(m) + 1;

	// nxt[i][j] is the (1<<i)th seg of i
	// in the noi (noi means no seg is fully in another)
	vector<vector<int>> nxt(m, vector<int>(lg + 1, 0));
	for(int i = 0, j = 0; i < m; ++i){
		while(j < m and noi[j].ff <= noi[i].ss) ++j;
		if(j >= m) break;
		nxt[i][0] = j;
	}
	for(int j = 1; j <= lg; ++j)
		for(int i = 0; i < m; ++i)
			if(nxt[i][j-1]) nxt[i][j] = nxt[nxt[i][j-1]][j-1];

	auto sol = [&](int l, int r){ 
		int i = lower_bound(AI(noi), pii(l, -1)) - begin(noi);
		if(i == m or r < noi[i].ss) return 0;
		int ans = 1;
		for(int k = lg; k >= 0; --k)
			if(nxt[i][k] != 0 and noi[nxt[i][k]].ss <= r){
				ans += (1<<k);
				i = nxt[i][k];
			}
		return ans;
	};
	cout << sol(-inf, inf) << '\n';

	set<pii> ans;
	ans.emplace(-inf, -inf);
	ans.emplace(inf, inf);
	for(int i = 0; i < n; ++i){
		auto ri = ans.lower_bound(seg[i]), li = prev(ri);
		auto [l, r] = seg[i];
		if(li->ss >= l or r >= ri->ff) continue;
		if(sol(li->ss + 1, ri->ff - 1) ==
				sol(li->ss + 1, l-1) + 1 + sol(r+1, ri->ff - 1)){
			cout << i + 1 << ' ';
			ans.emplace(l, r);
		}
	}
	return 0;
}

