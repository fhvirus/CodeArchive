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
void Assist(unsigned char *A, int N, int K, int R); void PutBack(int T);
int GetRequest();
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	int n, k, r; cin >> n >> k >> r;
	unsigned char * a = new unsigned char[r];
	for(int i = 0; i < r; ++i) cin >> a[i], a[i] -= '0';
	Assist(a, n, k, r);
	return 0;
}
int GetRequest(){
	const int a[4] = {2, 0, 3, 0};
	static int p = 0;
	return a[p++];
}
void PutBack(int T){
	cout << T << ' ';
}
#else
#include "assistant.h"
#endif
const int maxn = 1e5 + 225;
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
	int findk(int k){
		int l = 0, r = maxn - 1, m;
		while(l < r){
			m = (l + r) / 2;
			//debug(l, r, m, query(m));
			if(query(m) >= k) r = m;
			else l = m + 1;
		}
		return l;
	}
} s;
void Assist(unsigned char *A, int N, int K, int R){
	int L = __lg(K - 1);
	auto GC = [&](){
		static int p = 0;
		return (int)A[p++];
	};

	for(int i = 0; i < K; ++i) s.insert(i);
	for(int i = 0; i < N; ++i){
		int c = GetRequest();
		auto cmd = GC();
		//debug((int) cmd);
		if(cmd == 0) continue;
		int ans = 0;
		for(int i = 0; i <= L; ++i){
			ans = (ans << 1) | (GC());
		}
		++ans;
		int q = s.findk(ans);
		PutBack(q);
		s.erase(q);
		s.insert(c);
	} 
}
