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

const int kN = 1000001;
const int kP = 80000; // 78498
const int kL = 20;
const int MOD = 1e9 + 7;

inline int mul(int u, int v){ return (ll) u * v % MOD; }
inline int mow(int x, int e){
	int r = 1;
	while(e){
		if(e&1) r = mul(r, x);
		x = mul(x, x);
		e >>= 1;
	}
	return r;
}
int N, Q, C;
int c[kN], ans[kN];
vector<pii> qs[kN];

int prime[kP], primeNum;
int minPrimeFactor[kN];
int invPrime[kP];
void sieve(){
	prime[++primeNum] = 2;
	for(int i = 2; i <= C; i += 2)
		minPrimeFactor[i] = 1;
	for(int i = 3; i <= C; i += 2){
		if(minPrimeFactor[i]) continue;
		prime[++primeNum] = i;
		minPrimeFactor[i] = primeNum;
		if(i > 10000) continue;
		for(int j = i * i; j <= C; j += i)
			if(minPrimeFactor[j] == 0)
				minPrimeFactor[j] = primeNum;
	}
	for(int p = 1; p <= primeNum; ++p)
		invPrime[p] = mow(prime[p], MOD - 2);
}

int bit[kN];
void modify(int p, int v){
	for(; p <= N; p += p & -p)
		bit[p] = mul(bit[p], v);
}
int query(int p){
	int r = 1;
	for(; p; p -= p & -p)
		r = mul(r, bit[p]);
	return r;
}

// pos, power
vector<pii> mono[kP];
void putIn(int pos, int val){
	while(val > 1){
		int curPrime = minPrimeFactor[val];
		int power = 0;
		while(minPrimeFactor[val] == curPrime){
			val /= prime[curPrime];
			++power;
		}
		auto &stk = mono[curPrime];
		int lst = 0;
		while(!stk.empty() and stk.back().ss <= power){
			modify(stk.back().ff, mow(invPrime[curPrime], stk.back().ss - lst));
			lst = stk.back().ss;
			stk.pop_back();
		}
		if(!stk.empty()) modify(stk.back().ff, mow(invPrime[curPrime], power - lst));
		stk.pb(pos, power);
	}
}

signed main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> N >> Q;
	for(int i = 1; i <= N; ++i){
		cin >> c[i];
		C = max(C, c[i]);
	}
	for(int l, r, i = 0; i < Q; ++i){
		cin >> l >> r;
		qs[r].pb(l, i);
	}

	sieve();
	for(int i = 0; i <= N; ++i) bit[i] = 1;

	for(int i = 1; i <= N; ++i){
		putIn(i, c[i]);
		modify(i, c[i]);
		int ansr = query(i);
		for(auto [l, id]: qs[i])
			ans[id] = mul(ansr, mow(query(l-1), MOD-2));
	}

	for(int i = 0; i < Q; ++i)
		cout << ans[i] << '\n';
	return 0;
}
