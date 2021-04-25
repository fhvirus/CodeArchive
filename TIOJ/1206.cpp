#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int RS(char s[]){
	while((s[0] = readchar()) < '0' and s[0] != EOF);
	if(s[0] == EOF) return 0;
	int len = 1;
	while((s[len] = readchar()) >= '0') ++len;
	return len;
}
inline int min(int a, int b){
	return a < b ? a : b;
}
const int N = 2e5 + 1;
int z[N], ss;
char s[N];
int main(){
	while((ss = RS(s)) != 0){
		int ans = 0;
		int l = 0, r = 0, cnt = 0;
		for(int i = 1; i < ss; ++i){
			cnt = (i > r) ? 0 : min(r - i + 1, z[i-l]);
			while(i + cnt < ss and s[ss - cnt - 1] == s[ss - (i + cnt) - 1]) ++cnt;
			z[i] = cnt--;
			if(i + cnt > r) l = i, r = i + cnt;
			if(z[i] >= i) ans = i;
		}
		printf("%d\n", ans);
	}
}