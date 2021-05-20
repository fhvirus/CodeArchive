// Knapsack DP is harder than FFT.
#pragma GCC optimize("Ofast")
#include<cstdio>
#include<algorithm>
using namespace std;
template<class I>bool chmax(I&a,I b){return a<b?(a=b,true):false;}
template<class I>bool chmin(I&a,I b){return b<a?(a=b,true):false;} 

const int N = 10005;
int n, m, len;
char a[N], b[N], ans[N];

int f[N][2], g[N][2];

void hirchberg(int l, int r, int u, int d){
	if(r < l or d < u) return;
	if(l == r or u == d){
		for(int i = l; i <= r; ++i)
			for(int j = u; j <= d; ++j)
				if(a[i] == b[j]){
					ans[len++] = a[i];
					return;
				}
		return;
	}

	int p = (l + r) / 2;
	for(int i = u - 1; i <= d + 1; ++i){
		f[i][0] = f[i][1] = 0;
		g[i][0] = g[i][1] = 0;
	}

	for(int i = l, k = (i & 1); i <= p; ++i, k = 1 - k){
		for(int j = u; j <= d; ++j)
			f[j][k] = max({ f[j-1][1-k] + (a[i] == b[j]), f[j][1-k], f[j-1][k] });
	}
	for(int i = r, k = (i & 1); i > p; --i, k = 1 - k){
		for(int j = d; j >= u; --j)
			g[j][k] = max({ g[j+1][1-k] + (a[i] == b[j]), g[j][1-k], g[j+1][k] });
	}

	int mxp = u - 1, mxv = f[u - 1][p & 1] + g[u][(p + 1) & 1];
	for(int i = u; i <= d; ++i)
		if(chmax(mxv, f[i][p & 1] + g[i + 1][(p + 1) & 1]))
			mxp = i;

	hirchberg(l, p, u, mxp);
	hirchberg(p + 1, r, mxp + 1, d);
}

void solve(){
	scanf("%d%d%s%s", &n, &m, a + 1, b + 1);
	len = 0;
	hirchberg(1, n, 1, m);
	if(len == 0) printf("*\n");
	else ans[len] = '\0', printf("%s\n", ans);
}

signed main(){
	int t; scanf("%d", &t);
	for(; t; --t) solve();
	return 0;
}
