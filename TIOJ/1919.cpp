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

struct BIT {
	int n; vector<ll> val;
	BIT (int nn = 0) : n(nn), val(nn+1, 0) {}
	void modify(int p, int v){
		for(; p <= n; p += p&-p)
			val[p] += v;
	}
	ll query(int p){
		ll r = 0;
		for(; p > 0; p -= p&-p)
			r += val[p];
		return r;
	}
} bit;

const int kN = 100004;
int n, m, Q, a[kN], V[kN];
int L[kN], R[kN], C[kN];

void input() {
	cin >> n >> m >> Q;
	for(int i = 1; i <= m; ++i) cin >> a[i];
	for(int i = 1; i <= n; ++i) cin >> V[i];
	for(int i = 1; i <= Q; ++i)
		cin >> L[i] >> R[i] >> C[i];
}

vector<int> emp[kN];
int nxt[kN];
int ans[kN];

vector<tuple<int, int, int>> ms;
vector<int> qs;
ll tmp[kN];

void wbs(vector<int> &ids, int lb, int rb) { 
	if(lb == rb){
		for(int &i: ids)
			ans[i] = lb;
		return;
	}

	int mid = (lb+rb) / 2;

	ms.clear();
	for(int i = lb + (lb == 0); i <= mid; ++i){
		ms.pb(L[i], R[i]+1, C[i]);
		ms.pb(R[i]+1, R[i]+1, -C[i]);
	}
	sort(AI(ms));
	int mp = 0, mn = ms.size();

	qs.clear();
	for(int &i: ids)
		for(int &j: emp[i])
			qs.pb(j);
	sort(AI(qs));

	for(int i: qs){
		while(mp < mn){
			auto &[x, y, v] = ms[mp];
			if(x > i) break;
			bit.modify(y, v);
			++mp;
		}
		tmp[a[i]] += bit.query(nxt[i]);
	}

	vector<int> gl, gr;
	for(int &i: ids){
		if(tmp[i] < V[i]){
			V[i] -= tmp[i];
			gr.pb(i);
		} else gl.pb(i);
		tmp[i] = 0;
	}

	while(mp < mn){
		auto &[x, y, v] = ms[mp];
		bit.modify(y, v);
		++mp;
	}

	if(!gl.empty()) wbs(gl, lb, mid);
	if(!gr.empty()) wbs(gr, mid+1, rb);
}

void solve() {
	vector<int> cnt(n+1, 0);
	vector<int> ids;
	for(int i = 1; i <= m; ++i) ++cnt[a[i]];
	for(int i = 1; i <= n; ++i){
		if(V[i] == 0) ans[i] = 0;
		else if(cnt[i] == 0) ans[i] = -1;
		else ids.pb(i);
	}
	if(ids.empty()) return;

	for(int i = 1; i <= m; ++i){
		if(!emp[a[i]].empty())
			nxt[emp[a[i]].back()] = i;
		emp[a[i]].pb(i);
	}
	for(int i = 1; i <= n; ++i)
		if(!emp[a[i]].empty())
			nxt[emp[a[i]].back()] = m+1;

	// search for the min# of queries
	// such that one can suffice the condition
	bit = BIT(m+1);
	wbs(ids, 0, Q+1);

	for(int i = 1; i <= n; ++i)
		if(ans[i] == Q+1) ans[i] = -1;
}

void ouput() {
	for(int i = 1; i <= n; ++i)
		cout << ans[i] << '\n';
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	input();
	solve();
	ouput();
	return 0;
}
