// Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll; typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define AI(x) begin(x),end(x)
#ifdef OWO
#define debug(args...) SDF(#args, args)
#define OIU(args...) ostream& operator<<(ostream&O,args)
#define LKJ(S,B,E,F) template<class...T>OIU(S<T...>s){O<<B;int c=0;for(auto i:s)O<<(c++?", ":"")<<F;return O<<E;}
LKJ(vector,'[',']',i)LKJ(deque,'[',']',i)LKJ(set,'{','}',i)LKJ(multiset,'{','}',i)LKJ(unordered_set,'{','}',i)LKJ(map,'{','}',i.ff<<':'<<i.ss)LKJ(unordered_map,'{','}',i.ff<<':'<<i.ss)
template<class...T>void SDF(const char* s,T...a){int c=sizeof...(T);if(!c){cerr<<"\033[1;32mvoid\033[0m\n";return;}(cerr<<"\033[1;32m("<<s<<") = (",...,(cerr<<a<<(--c?", ":")\033[0m\n")));}
template<class T,size_t N>OIU(array<T,N>a){return O<<vector<T>(AI(a));}template<class...T>OIU(pair<T...>p){return O<<'('<<p.ff<<','<<p.ss<<')';}template<class...T>OIU(tuple<T...>t){return O<<'(',apply([&O](T...s){int c=0;(...,(O<<(c++?", ":"")<<s));},t),O<<')';}
#else
#define debug(...) ((void)0)
#endif

struct DSU {
	int n; vector<int> f;
	DSU (int _n = 0): n(_n), f(n + 1) { iota(AI(f), 0); }
	int F(int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	int operator () (int u) { return u == f[u] ? u : f[u] = F(f[u]); }
	bool M(int u, int v) {
		u = F(u); v = F(v);
		if (u == v) return true;
		f[v] = u;
		return false;
	}
};

signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

	int N; cin >> N;
	vector<int> out(N + 1);
	for (int i = 1; i <= N; ++i)
		cin >> out[i];

	int Q; cin >> Q;
	vector<pii> qs(Q);
	vector<bool> del(N + 1, false);
	for (auto &[t, x]: qs) {
		cin >> t >> x;
		if (t == 2)
			del[x] = true;
	}

	DSU dsu(N);
	vector<bool> cyc(N + 1, false);
	for (int i = 1; i <= N; ++i)
		if (!del[i] and out[i] != 0) {
			if (dsu.M(out[i], i))
				cyc[dsu(i)] = true;
		}

	reverse(AI(qs));
	vector<int> ans;
	for (auto &[t, x]: qs) {
		if (t == 1) {
			x = dsu(x);
			ans.pb(cyc[x] ? -1 : x);
		} else {
			if (out[x] != 0 and dsu.M(out[x], x))
				cyc[dsu(x)] = true;
		}
	}

	reverse(AI(ans));
	for (int &i: ans) {
		if (i == -1) cout << "CIKLUS\n";
		else cout << i << '\n';
	}

	return 0;
}
