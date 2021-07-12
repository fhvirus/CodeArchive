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

const int kN = 10;
int in[kN], ou[kN], adj[kN][kN];
bool nid[kN];
vector<int> ans;

void euler(int u){
	//debug(u);
	nid[u] = 0;
	for(int v = 0; v < 10; ++v)
		if(adj[u][v] > 0){
			--ou[u], --in[v];
			--adj[u][v];
			euler(v);
		}
	ans.pb(u);
}

void solve(int n, int m){
	if(m < 10){
		for(int i = n; i <= m; ++i) cout << i;
		cout << '\n';
		return;
	}

	for(int i = 0; i < 10; ++i) in[i] = ou[i] = 0;
	for(int i = 0; i < 10; ++i) for(int j = 0; j < 10; ++j) adj[i][j] = 0;
	for(int i = 0; i < 10; ++i) nid[i] = false;
	ans.clear();

	for(int i = n; i <= m; ++i){
		if(i >= 10){
			int u = i / 10, v = i % 10;
			++ou[u], ++in[v];
			++adj[u][v];
		} else nid[i] = true;
	}

	// connect it
	while(true){
		int odd = 0, eek = 0;
		for(int i = 0; i < 10; ++i){
			if(abs(in[i] - ou[i]) >= 2) ++eek;
			else if((in[i] + ou[i]) & 1) ++odd;
		}

		if(eek == 0 and odd <= 2) break;

		bool has = false;
		for(int i = 0; i < 10 and !has; ++i) if(in[i] > ou[i])
			for(int j = 0; j < 10; ++j) if(in[j] < ou[j]){
				++ou[i], ++in[j], ++adj[i][j];
				has = true; break;
			}
	} 

	int s = -1;
	for(int i = 0; i < 10; ++i) if(in[i] or ou[i]) s = i;
	for(int i = 0; i < 10; ++i) if(in[i] < ou[i]) s = i;
	euler(s);
	reverse(AI(ans));
	
	for(int i = 0; i < 10; ++i) if(nid[i]) ans.pb(i);

	for(int i: ans) cout << i;
	cout << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, m;
	while(cin >> n >> m) solve(n, m);
	return 0;
}
