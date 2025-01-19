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
 
typedef uint32_t uint;
typedef uint64_t ull;
typedef __uint128_t u128;
 
const int kN = 1 << 19;
const ull MOD = 9097271247288401921ull;
const ull INV = 9351220758157713293ull;
const ull   G = 6;
 
constexpr ull mul(ull a, ull b) {
  u128 v = (u128)a * b;
  ull x = v >> 62;
  ull q = ((u128)x * INV) >> 64;
 
  ull ans = (ull)v - q * MOD;
	ans -= MOD; ans += MOD & ((ll) ans >> 63);
  return ans;
}
inline ull mow(ull x, ull e){
	ull r = 1;
	for(; e; e >>= 1){
		if(e & 1) r = mul(r, x);
		x = mul(x, x);
	}
	return r;
}
 
ull W[kN];
int rev[kN];
void build(int n) {
	W[0] = 1; ull w = mow(G, (MOD-1) / n);
	for (int i = 1; i < n; ++i) W[i] = mul(W[i-1], w);
 
	rev[0] = 0;
	for (int i = 1, h = -1, l = 31 - __builtin_clz(n); i < n; ++i) {
		if ((i & (i - 1)) == 0) ++h;
		rev[i] = rev[i ^ (1 << h)] | (1 << (l - h - 1));
	}
}
void NTT(int n, ull a[]) {
	for (int i = 0; i < n; ++i)
		if (i < rev[i]) swap(a[i], a[rev[i]]);
 
	for (int l = 0; (1 << l) < n; ++l)
		for (int g = 0; g < n; g += 1 << (l + 1))
			for (int i = 0; i < (1 << l); ++i) {
				ull x = a[g + i];
				ull y = mul(a[g + i + (1 << l)], W[(n >> (l + 1)) * i]);
				a[g + i] = x + y - MOD; a[g + i] += (MOD & ((ll) a[g + i] >> 63));
				a[g + i + (1 << l)] = x - y; a[g + i + (1 << l)] += (MOD & ((ll) a[g + i + (1 << l)] >> 63));
			}
}
 
int k, n, m, tk;
ull a[kN], b[kN], c[kN];
 
signed main() {
	ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
 
	cin >> k >> n >> m;
	tk = k;
	k = 2 << (31 - __builtin_clz(k * 2));
 
	for (int v, i = 0; i < n; ++i) {
		cin >> v;
		++a[v];
	}
	for (int v, i = 0; i < m; ++i) {
		cin >> v;
		++b[v];
	}
 
	build(k);
	NTT(k, a);
	NTT(k, b);
	for (int i = 0; i < k; ++i)
		c[i] = mul(a[i], b[i]);
	reverse(W + 1, W + k);
	NTT(k, c);
 
	ull R = mow(k, MOD - 2);
	for (int i = 0; i < k; ++i)
		c[i] = mul(c[i], R);
 
	for (int i = 2; i <= 2 * tk; ++i)
		cout << c[i] << " \n"[i == 2 * tk];
 
	return 0;
}
