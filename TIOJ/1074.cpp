#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
#define FOR(i,n) for(int i=0;i<n;++i)
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

int n, a[20], sum;
bool appear[500];

int main(){
	while((n = R()) != 0){
		sum = 0;
		memset(appear, 0, sizeof(appear));
		FOR(i,n) a[i] = R() + (i == 0 ? 0 : a[i-1]);
		if(a[n-1] == n){
			puts("NO");
			continue;
		}
		for(int i = 0; i < n; ++i)
			for(int j = i; j < n; ++j)
				appear[a[j] - (i == 0 ? 0 : a[i-1])] = true;
		bool flag = true;
		for(int i = 1; i <= a[n-1]; ++i)
			if(!appear[i]){
				flag = false;
				break;
			}
		puts(flag ? "YES" : "NO");
	}
}