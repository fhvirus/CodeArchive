#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
const int N = 1e5;
int k, len, ans;
char s[N];
int eek[N];

int main(){
	while(scanf("%d", &k) != EOF){
		fgets(s+1, N, stdin);
		fgets(s+1, N, stdin);
		len = strlen(s+1), ans = 0;
		for(int i = 1; i <= len; ++i)
			eek[i] = eek[i-1] + (i + k <= len and s[i] == s[i + k]),
			ans += (i >= k and eek[i] - eek[i-k] == k);
		printf("%d\n", ans);
	}
}