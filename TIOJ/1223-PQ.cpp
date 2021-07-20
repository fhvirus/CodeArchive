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
	int M, Q;
	vector<pii> mdf, que;
	cin >> M;
	for(int p, a, b, i = 0; i < M; ++i){
		cin >> p >> a >> b;
		mdf.pb(a, -p);
		mdf.pb(b, p);
	}
	cin >> Q;
	for(int t, i = 0; i < Q; ++i){
		cin >> t;
		que.pb(t, i);
	}

	sort(AI(mdf), greater<pii>());
	sort(AI(que), greater<pii>());
	vector<int> cnt(N+1, 0), cur(N+1, T);
	vector<pii> ans(Q, pii(-1, 0));

	priority_queue<pii, vector<pii>> pq;
	for(int i = 1; i <= N; ++i) pq.emplace(T, -i);

	int ptr = 0;
	for(auto [t, i]: que){
		while(ptr < mdf.size() and mdf[ptr].ff > t){
			auto [a, p] = mdf[ptr]; ++ptr;
			if(p > 0) ++cnt[p];
			if(p < 0) --cnt[-p], p = -p;
			if(cnt[p] == 0) pq.emplace(a, -p), cur[p] = a;
			else cur[p] = -1;
		}
		while(!pq.empty()){
			auto [a, p] = pq.top(); p = -p;
			if(cur[p] == a) break;
			pq.pop();
		}
		if(pq.empty()){ continue; }
		auto [a, p] = pq.top(); p = -p;
		ans[i] = pii(p, a - t);
	}

	for(pii i: ans){
		if(i.ff == -1) cout << "Oh, no!\n";
		else cout << i.ff << ' ' << i.ss << '\n';
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int N, T;
	while(cin >> N >> T and N and T) solve(N, T);
	return 0;
}
