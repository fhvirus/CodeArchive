#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline int R(){
	int ans = 0; char c = getchar_unlocked();
	while(c<'0') c = getchar_unlocked();
	while(c>='0') ans=(ans*10)+(c^'0'), c = getchar_unlocked();
	return ans;
}

inline int max(int a, int b){
	return a > b ? a : b;
}

const int N = 2e5 + 1;
int n, m;
int l[N], r[N];
int a[N];

signed main(){
	n = R(); m = R();
	for(int i = 0; i < m; ++i) l[i] = R()-1, r[i] = R()-1;
	for(int i = 0; i < n; ++i) a[i] = R();
	for(int q = 0; q < m; ++q) if(l[q] == r[q]) l[q] = a[l[q]], r[q] = -1;
	for(int len = 1; (1<<len) <= n; ++len){
		for(int i = 0; i + (1<<len) <= n; ++i)
			a[i] = max(a[i], a[i+(1<<(len-1))]);
		for(int q = 0; q < m; ++q)
			if(r[q] != -1 && 31 - __builtin_clz(r[q] - l[q] + 1) == len)
				l[q] = max(a[l[q]], a[r[q] - (1<<len) + 1]), r[q] = -1;
	}
	for(int q = 0; q < m; ++q) printf("%d\n", l[q]);
	return 0;
}