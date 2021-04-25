#pragma GCC optimize("Ofast")
#include<cstdio>
#define min(a,b) (a < b ? a : b)
const int N = 14;
#define INF 8e7
int n, a[N], dp[1<<N][N];
int main(){
    scanf("%d", &n);
    for(int i = 0; i < n; ++i) scanf("%d", &a[i]);

#ifdef fhvirus
    int u = 0, v = 0;
	for(int i = 0; i < n; ++i)
		if(a[i] > a[u]) u = i;
	bool yas = true;
	for(int i = 0; i < n; ++i)
		if(a[u] - a[i] < (i > u ? u - i : i - u)) yas = false;
	if(yas){
		printf("%d", a[u]);
		return 0;
	}
#endif


    for(int i = 0; i < n; ++i) dp[1<<i][i] = (i / a[i] + 1) * a[i];

	char sc[N], ptr;
    for(int d = 1; d < 1<<n; ++d){
        if((d & (d - 1)) == 0) continue;
        ptr = 0;
        for(int i = 0; i < n; ++i)
            if(d & (1<<i)) sc[ptr++] = i;
        for(int i = 0; i < ptr; ++i){
            dp[d][sc[i]] = INF;
            for(int j = 0; j < ptr; ++j){
                if(j != i)
                dp[d][sc[i]] = min(
                    dp[d][sc[i]],
                    ((dp[d^(1<<sc[i])][sc[j]] + (i > j ? sc[i] - sc[j] : sc[j] - sc[i]) - 1) / a[sc[i]] + 1) * a[sc[i]]
                );
            }
        }
    }
    int ans = INF;
    for(int i = 0; i < n; ++i)
        ans = min(ans, dp[(1<<n)-1][i]);
    printf("%d",ans);
    return 0;
}
