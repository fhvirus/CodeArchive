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

const int kN = 130031;

inline uint32_t ran(){
	static uint32_t x = 131;
	return ++(x *= 0xdefaced);
}
struct NODE {
	int val, siz, tag;
	uint32_t pri;
	int lc, rc;
	NODE(int v = 0): val(v), siz(1), tag(false), pri(ran()), lc(0), rc(0) {}
};

int N, M;
NODE nds[kN];

constexpr int Siz(int i){ return i ? nds[i].siz : 0; }
inline void push(int i){
	if(!nds[i].tag) return;
	nds[nds[i].lc].tag ^= 1;
	nds[nds[i].rc].tag ^= 1;
	swap(nds[i].lc, nds[i].rc);
	nds[i].tag = 0;
}
inline void pull(int i){
	nds[i].siz = Siz(nds[i].lc) + Siz(nds[i].rc) + 1;
}
int merge(int u, int v){
	push(u); push(v);
	if(!u or !v) return u ? u : v;
	if(nds[u].pri >= nds[v].pri){
		nds[u].rc = merge(nds[u].rc, v);
		pull(u);
		return u;
	}
	nds[v].lc = merge(u, nds[v].lc);
	pull(v);
	return v;
}
void split(int rt, int &u, int &v, int s){
	push(rt);
	if(!rt){
		u = v = 0;
		return;
	}
	if(Siz(nds[rt].lc) + 1 <= s){
		u = rt;
		split(nds[rt].rc, nds[u].rc, v, s - Siz(nds[rt].lc) - 1);
		pull(u);
		return;
	}
	v = rt;
	split(nds[rt].lc, u, nds[v].lc, s);
	pull(v);
}
void dfsSiz(int u){
	if(nds[u].lc) dfsSiz(nds[u].lc);
	if(nds[u].rc) dfsSiz(nds[u].rc);
	pull(u);
}
void dfs(int u){
	push(u);
	if(nds[u].lc) dfs(nds[u].lc);
	cout << nds[u].val << ' ';
	if(nds[u].rc) dfs(nds[u].rc);
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> M;
	nds[0].siz = 0;
	for(int i = 1; i <= N; ++i) nds[i] = NODE(i);
	
	// build
	vector<int> stk(N, 0); int top = 0;
	for(int i = 1; i <= N; ++i){
		int k = top;
		while(k >= 0 and nds[stk[k]].pri < nds[i].pri) --k;
		if(k >= 0) nds[stk[k]].rc = i;
		if(k < top) nds[i].lc = stk[k+1];
		stk[++k] = i;
		top = k;
	}
	int root = stk[0];
	dfsSiz(root);

	string t;
	for(int a, b, c, d, i = 0; i < M; ++i){
		cin >> t;
		if(t[0] == 'R'){
			cin >> a >> b;
			int t1, t2, t3, tr;
			split(root, tr, t3, b);
			split(tr, t1, t2, a-1);
			nds[t2].tag ^= 1;
			root = merge(merge(t1, t2), t3);
		} else {
			cin >> a >> b >> c >> d;
			int t1, t2, t3, t4, t5, u, v;
			split(root, u, t5, d);
			split(u, v, t4, c-1);
			split(v, u, t3, b);
			split(u, t1, t2, a-1);
			root = merge(t1, merge(merge(t4, t3), merge(t2, t5)));
		}
	}

	dfs(root);
	return 0;
}
