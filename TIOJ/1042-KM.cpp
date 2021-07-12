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

const int kN = 100;
const int inf = 1e9 + 7;

struct HGY {
	int n;
	vector<vector<int>> adj;
	vector<int> mch;
	vector<int> lbl, lbr, slk;
	vector<int> vil, vir;
	HGY(int n = kN): n(n), adj(n, vector<int>(n)), mch(n, -1),
		lbl(n, 0), lbr(n, 0), slk(n, inf), vil(n, 0), vir(n, 0) {}
	vector<int>& operator[] (int i) { return adj[i]; }

	void init(int nn){ n = nn; }
	bool dfs(int u, bool eek){
		if(vil[u]) return false;
		vil[u] = true;
		for(int v = 0; v < n; ++v){
			if(vir[v]) continue;
			int d = lbl[u] + lbr[v] - adj[u][v];
			if(d == 0){
				vir[v] = true;
				if(mch[v] == -1 or dfs(mch[v], eek)){
					if(eek) mch[v] = u;
					return true;
				}
			} else chmin(slk[v], d);
		}
		return false;
	}
	bool aug(){
		for(int j = 0; j < n; ++j)
			if(!vir[j] and slk[j] == 0){
				vir[j] = true;
				if(mch[j] == -1 or dfs(mch[j], false))
					return true;
			}
		return false;
	}
	void rel(){
		int del = inf;
		for(int j = 0; j < n; ++j) if(!vir[j]) chmin(del, slk[j]);

		for(int i = 0; i < n; ++i) if(vil[i]) lbl[i] -= del;
		for(int j = 0; j < n; ++j){
			if(vir[j]) lbr[j] += del;
			else slk[j] -= del;
		}
	}
	int solve(){
		fill(AI(lbl), 0);
		fill(AI(lbr), 0);
		fill(AI(mch), -1);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				chmax(lbl[i], adj[i][j]);

		for(int i = 0; i < n; ++i){
			fill(AI(slk), inf);
			fill(AI(vil), false);
			fill(AI(vir), false);

			if(dfs(i, true)) continue;
			while(!aug()) rel();

			fill(AI(vil), false);
			fill(AI(vir), false);
			dfs(i, true);
		}

		int ans = 0;
		for(int j = 0; j < n; ++j)
			if(mch[j] != -1) ans += adj[mch[j]][j];
		return ans;
	}
} hgy;

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n;
	while(cin >> n && n){ 
		hgy.init(n);
		for(int i = 0; i < n; ++i)
			for(int j = 0; j < n; ++j)
				cin >> hgy[i][j], chmax(hgy[i][j], 0);
		cout << hgy.solve() << '\n';
	}
	return 0;
}
