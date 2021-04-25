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
const int maxn = 1e5 + 225;
int n, c, r, k[maxn], s[maxn], e[maxn];
int GetBestPosition(int N, int C, int R, int *K, int *S, int *E);
int32_t main(){
	ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0);
	cin >> n >> c >> r;
	for(int i = 0; i < n - 1; ++i) cin >> k[i];
	for(int i = 0; i < c; ++i) cin >> s[i] >> e[i];
	cout << GetBestPosition(n, c, r, k, s, e) << endl;
	return 0;
}
#endif

int GetBestPosition(int N, int C, int R, int *K, int *S, int *E){
	vector<int> k(N - 1);
	FOR(i,N - 1) k[i] = K[i];
	auto kill = [](vector<int> & v, int l, int r){
		int mx = *max_element(v.begin() + l, v.begin() + r + 1);
		v.erase(v.begin() + l, v.begin() + r + 1);
		v.insert(v.begin() + l, mx);
	};
	int ans = 0, pos = 0;
	for(int i = 0; i < N; ++i){
		//debug(i);
		vector<int> v = k;
		int rid = i, cur = 0;
		v.insert(v.begin() + i, R);
		//	for(auto t: v) cout << t << ' ';
		//	cout << endl;
		for(int j = 0; j < C; ++j){
			int s = S[j], e = E[j];
			if(rid < s or e < rid){
				kill(v, s, e);
				if(e < rid) rid -= e - s;
				continue;
			}
			if(R < *max_element(v.begin() + s, v.begin() + e + 1)) break;
			kill(v, s, e);
			rid = s;
			++cur;
		//	for(auto t: v) cout << t << ' ';
		//	cout << endl;
		}
		//debug(i, cur);
		if(chmax(ans, cur)) pos = i;
	}
	return pos;
}
