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

const int kN = 300003;
constexpr int id(int l, int r){ return (l + r) | (l != r); } 

int n, q;
ll a[kN];
ll val[kN * 2];
bool tag[kN * 2]; 

void merge(int i, int l, int r){
	val[i] = val[l] + val[r];
	tag[i] = tag[l] and tag[r];
}
void build(int l, int r){
	int i = id(l, r);
	if(l == r){ val[i] = a[l]; tag[i] = (val[i] == 1); return; }
	int m = (l + r) / 2;
	build(l, m); build(m+1, r);
	merge(i, id(l, m), id(m+1, r));
}
ll que(int l, int r, int ql, int qr){
	int i = id(l, r);
	if(ql <= l and r <= qr) return val[i];
	int m = (l + r) / 2;
	return (ql <= m ? que(l, m, ql, qr) : 0)
		+ (m+1 <= qr ? que(m+1, r, ql, qr) : 0);
}
void mod(int l, int r, int ql, int qr){
	int i = id(l, r);
	if(tag[i]) return;
	if(l == r){ val[i] = sqrt(val[i]); tag[i] = (val[i] == 1); return; }

	int m = (l + r) / 2;
	if(ql <= m) mod(l, m, ql, qr);
	if(m+1 <= qr) mod(m+1, r, ql, qr);
	merge(i, id(l, m), id(m+1, r));
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> q;
	for(int i = 1; i <= n; ++i) cin >> a[i];
	build(1, n);
	for(int cmd, l, r; q; --q){
		cin >> cmd >> l >> r;
		if(cmd == 0) cout << que(1, n, l, r) << '\n';
		else mod(1, n, l, r);
	}
	return 0;
}
