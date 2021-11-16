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

const int kN = 100001;
const int kL = 17;
int N, anc[kL][kN], dep[kN];

int getLCA(int u, int v){
	if(dep[u] < dep[v]) swap(u, v);
	for(int d = dep[u] - dep[v], l = 0; l < kL; ++l)
		if(d >> l & 1) u = anc[l][u];
	if(u == v) return u;
	for(int l = kL-1; l >= 0; --l)
		if(anc[l][u] != anc[l][v]){
			u = anc[l][u];
			v = anc[l][v];
		}
	return anc[0][u];
}
int dis(int u, int v){
	return dep[u] + dep[v] - 2 * dep[getLCA(u, v)];
}
int one(int u, int v){
	// go from u, one step to v
	int lca = getLCA(u, v);
	if(lca != v) return anc[0][v];
	int d = dep[u] - dep[v] - 1;
	for(int l = kL-1; l >= 0; --l)
		if(d >> l & 1) u = anc[l][u];
	return u;
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N; auto p = anc[0]; p[1] = 1;
	for(int i = 2; i <= N; ++i) cin >> p[i];
	for(int i = 2; i <= N; ++i) dep[i] = dep[p[i]] + 1;
	for(int l = 1; l < kL; ++l)
		for(int i = 1; i <= N; ++i)
			anc[l][i] = anc[l-1][anc[l-1][i]];

	cout << 1 << '\n';

	// 0: vertex
	// 1: edge
	bool mode = 0;
	int cen = 1, rad = 0, sum = 1;
	unordered_map<int, int> cnt;

	int cu, cntu;
	int cv, cntv;

	ll ans = 0;
	for(int i = 2; i <= N; ++i){
		if(mode == 0){
			int d = dis(cen, i);
			if(d == rad){
				int u = one(i, cen);
				int &c = cnt[u];
				ans += sum - c;
				++c; ++sum;
			} else if(d > rad) {
				mode = !mode;
				int u = one(i, cen);
				cu = cen; cntu = sum - cnt[u];
				cv = u; cntv = 1;
				ans = (ll) cntu * cntv;
				cnt.clear();
			}
		} else {
			int du = dis(cu, i);
			int dv = dis(cv, i);
			if(du > dv){ swap(cu, cv); swap(cntu, cntv); swap(du, dv); }
			if(du == rad){
				++cntu;
				ans = (ll) cntu * cntv;
			} else if (du > rad) {
				mode = !mode;
				int u = one(i, cu);
				cen = cu; cnt[cv] = cntv;
				cnt[u] = 1;
				++rad; sum = cntv+1;
				ans = cntv;
			}
		}
		debug(mode);
		if(mode == 0){
			debug(cnt);
		} else {
			debug(cu, cntu);
			debug(cv, cntv);
		}
		cout << ans << '\n';
	}

	return 0;
}

