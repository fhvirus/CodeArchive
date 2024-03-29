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

const int N = 1010, C = 127;
char a[N], b[N], ans[N];
int n, m, len;

short dp[N][N];
short pa[N][C], pb[N][C];

void LCS(){
	for(int i = 1; i <= n; ++i){
		for(int j = 1; j <= m; ++j){
			if(a[i] == b[j]) dp[i][j] = dp[i-1][j-1] + 1;
			else dp[i][j] = max(dp[i-1][j], dp[i][j-1]);
		}
	}
}

void BT(){
	if(dp[n][m] == 0){
		len = 0;
		return;
	}

	for(int i = 1; i <= n; ++i)
		for(int c = 33; c < C; ++c)
			pa[i][c] = (a[i] == c ? i : pa[i-1][c]);
	for(int i = 1; i <= m; ++i)
		for(int c = 33; c < C; ++c)
			pb[i][c] = (b[i] == c ? i : pb[i-1][c]);

	len = 0;
	int i = n, j = m;
	for(int k = 0; k < dp[n][m]; ++k){
		for(int c = 33; c < C; ++c){
			if(pa[i][c] > 0 and pb[j][c] > 0 and
					dp[pa[i][c]-1][pb[j][c]-1] == dp[i][j] - 1){
				ans[len++] = c;
				i = pa[i][c] - 1, j = pb[j][c] - 1;
				break;
			}
		}
	}
}

void solve(){
	scanf("%s%s", a, b);
	n = strlen(a); a[n] = 0;
	m = strlen(b); b[m] = 0;
	if(n == m and strcmp(a, b) == 0){
		puts(a);
		return;
	}
	reverse(a, a + n + 1);
	reverse(b, b + m + 1);

	LCS();
	BT();

	if(len == 0) puts("妹萌えこそ正義なのさ！");
	else ans[len] = 0, puts(ans);
}

signed main(){
	int t; scanf("%d", &t);
	for(; t; --t) solve();
	return 0;
}
