//Knapsack DP is harder than FFT.
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define ff first
#define ss second
#define pb emplace_back
#define FOR(i,n) for(int i = 0; i < (n); ++i)
#define FOO(i,a,b) for(int i = (a); i <= (b); ++i)
#define AI(x) (x).begin(),(x).end()
template<typename I> bool chmax(I &a, I b){ return a < b ? (a = b, true) : false;}
template<typename I> bool chmin(I &a, I b){ return a > b ? (a = b, true) : false;}
#ifdef OWO
#define debug(args...) LKJ("[ " + string(#args) + " ]", args)
void LKJ(){ cerr << endl;}
template<typename I, typename...T> void LKJ(I&&x, T&&...t){ cerr<<x<<", ", LKJ(t...);}
template<typename I> void DE(I a, I b){ while(a < b) cerr << *a << " \n"[next(a) == b], ++a;}
#else
#define debug(...) 0
#define DE(...) 0
#endif
#ifdef OWO
void ComputeAdvice(int *C, int N, int K, int M); void WriteAdvice(unsigned char a);
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, m, k;
	cin >> n >> k >> m;
	int *c = new int[n];
	for(int i = 0; i < n; ++i) cin >> c[i];
	ComputeAdvice(c, n, k, m);
	return 0;
}
void WriteAdvice(unsigned char a){
	putchar(a + '0');
	putchar(' ');
}
#else
#include "advisor.h"
#endif
const int maxn = 1e5 + 225;
queue<int> app[maxn];
struct BIT{
	int val[maxn];
	void modify(int p, int v){
		++p;
		for(; p <= maxn; p += p & -p) val[p] += v;
	}
	void insert(int p){ modify(p, 1);}
	void erase(int p){ modify(p, -1);}
	int query(int p){
		++p;
		int ans = 0;
		for(; p > 0; p -= p & -p) ans += val[p];
		return ans;
	}
	int count(int p){
		return query(p) - query(p - 1);
	}
	int find(int p){
		return query(p);
	}
} s;
void ComputeAdvice(int *C, int N, int K, int M){
	int L = __lg(K - 1);
	
	for(int i = 0; i < N; ++i) app[C[i]].emplace(i);
	for(int i = 0; i < N; ++i) app[i].emplace(8e7);

	priority_queue<pii> pq;
	for(int i = 0; i < K; ++i) s.insert(i);
	for(int i = 0; i < K; ++i) pq.emplace(app[i].front(), i);

	auto wn = [&L](int a){
		for(int i = L; i >= 0; --i){
			WriteAdvice((a >> i & 1));
		}
	};
	for(int i = 0; i < N; ++i){
		int c = C[i]; app[c].pop();
		if(s.count(c) != 0){
			WriteAdvice(0);
			pq.emplace(app[c].front(), c);
			continue;
		}
		int eek;
		pii tp;
		do{
			tp = pq.top(); pq.pop();
			eek = tp.ss;
		} while(s.count(eek) == 0);
		int q = s.query(eek);
		debug(eek, q);
		WriteAdvice(1);
		wn(q - 1);
		s.erase(eek);
		s.insert(c);
		pq.emplace(app[c].front(), c);
	}
}

