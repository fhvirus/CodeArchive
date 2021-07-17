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

const int kN = 505;
const int INF = 1e9 + 7;

int n, g[kN][kN];

int mch[kN];
int lx[kN], ly[kN], slk[kN];
int vx[kN], vy[kN], tot;

bool dfs(int u, bool ok){
	if(vx[u] == tot) return false;
	vx[u] = tot;

	for(int v = 0; v < n; ++v){
		if(vy[v] == tot) continue;
		int d = lx[u] + ly[v] - g[u][v];
		if(d == 0){
			vy[v] = tot;
			if(mch[v] == -1 or dfs(mch[v], ok)){
				if(ok) mch[v] = u;
				return true;
			}
		} else chmin(slk[v], d);
	}
	return false;
}
bool aug(){
	for(int j = 0; j < n; ++j){
		if(vy[j] != tot and slk[j] == 0){
			vy[j] = tot;
			if(mch[j] == -1 or dfs(mch[j], false))
				return true;
		}
	}
	return false;
}
void rel(){
	int del = INF;
	for(int j = 0; j < n; ++j) if(vy[j] != tot) chmin(del, slk[j]);
	for(int i = 0; i < n; ++i) if(vx[i] == tot) lx[i] -= del;
	for(int j = 0; j < n; ++j){
		if(vy[j] == tot) ly[j] += del;
		else slk[j] -= del;
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n;
	for(int i = 0; i < n; ++i)
		for(int j = 0; j < n; ++j){
			cin >> g[i][j];
			chmax(lx[i], g[i][j]);
		} 

	fill(mch, mch + n, -1);

	for(int i = 0; i < n; ++i){
		++tot;
		fill(slk, slk + n, INF);

		if(dfs(i, true)) continue;
		while(!aug()) rel();

		++tot;
		dfs(i, true);
	}

	cout << accumulate(lx, lx + n, 0) + accumulate(ly, ly + n, 0) << '\n';
	for(int i = 0; i < n; ++i) cout << lx[i] << " \n"[i == n-1];
	for(int i = 0; i < n; ++i) cout << ly[i] << " \n"[i == n-1];

	return 0;
}
