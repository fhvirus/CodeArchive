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

void solve(int N, int T){
	vector<vector<int>> a(N, vector<int>(T+1, 0));
	int M; cin >> M;
	for(int p, l, r, i = 0; i < M; ++i){
		cin >> p >> l >> r; --p;
		++a[p][l]; --a[p][r];
	}
	vector<pii> ans(T+1, pii(0, 0));
	for(int p = 0; p < N; ++p){
		auto &v = a[p];
		for(int i = 1; i < T; ++i)
			v[i] += v[i-1];
		int cur = 0;
		for(int i = T-1; i >= 0; --i){
			if(v[i] > 0) cur = 0;
			else ++cur;
			ans[i] = max(ans[i], pii(cur, -p));
		}
	}
	int Q; cin >> Q;
	for(int t, i = 0; i < Q; ++i){
		cin >> t;
		if(ans[t].ff == 0) cout << "Oh, no!\n";
		else cout << -ans[t].ss+1 << ' ' << ans[t].ff << '\n';
	}
	return;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	for(int N, T; cin >> N >> T and N * T != 0; solve(N, T));
	return 0;
}
