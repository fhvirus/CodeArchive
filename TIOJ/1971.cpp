#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#include<bitset>
#include<algorithm>
using namespace std;

typedef long long ll;
ll m, ans, cycle, cur, t;
int n, a[20];

bool dp[100000001];
ll vis[1ll<<20];

int main(){
	scanf("%lld%d", &m, &n);
	for(int i = 0; i < n; ++i) scanf("%d", &a[i]);
	sort(a, a + n);
	if(m <= 100000000){
		for(int i = 0; i <= m; ++i){
			if(dp[i]) ++ans;
			else for(int j = 0; j < n; ++j){
				if(i + a[j] > m){ n = j; break;}
				dp[i + a[j]] = true;
			}
		}
		printf("%lld\n", ans);
	} else {
		cycle = 1ll<<a[n-1], cur = 0;
		int i = 0;
		for(; i < a[n-1]; ++i){
			cur = cur<<1 | dp[i];
			if(!dp[i]) for(int j = 0; j < n; ++j) dp[i + a[j]] = true;
		}
		for(vis[cur] = 0, t = 1; ; ++i, ++t){
			cur = (cur<<1 | dp[i]) & ~cycle;
			if(~vis[cur]) break;
			if(dp[i]) ++ans;
			else for(int j = 0; j < n; ++j) dp[i + a[j]] = true;
			vis[cur] = t;
		}

	}
}