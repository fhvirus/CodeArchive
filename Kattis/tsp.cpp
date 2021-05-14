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

typedef pair<double, double> pdd;
double dis(pdd a, pdd b){
	return sqrt((b.ff - a.ff) * (b.ff - a.ff) + (b.ss - a.ss) * (b.ss - a.ss));
}

vector<int> greedyTour(int n, vector<pdd> &pos){
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	mt19937 mt(seed);

	vector<bool> vis(n, 0);
	vector<int> ans(n, 0);
	int u = mt() % n;
	for(int i = 1; i < n; ++i){
		vis[u] = true;
		int v = -1;
		double cur = 1e18;
		for(int j = 0; j < n; ++j)
			if(!vis[j] and chmin(cur, dis(pos[u], pos[j])))
				v = j;
		ans[v] = i;
		u = v;
	}

	return ans;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n; cin >> n;
	vector<pdd> pos(n);
	for(auto &[x, y]: pos) cin >> x >> y;
	vector<int> ans = greedyTour(n, pos);
	for(int i: ans) cout << i << '\n';
	return 0;
}
