#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

void swap(int &a, int &b){
	int tmp = a;
	a = b;
	b = tmp;
}

int n, a[100], q, eek;
int main(){
	while((n = R()) != 0){
		if(eek > 0) puts("");
		++eek;
		for(int i = 0; i < n; ++i) a[i] = R();
		q = R();
		for(int i, j; q; --q)
			i = R(), j = R(), a[i] ^= a[j] ^= a[i] ^= a[j];
		printf("%d", a[0]);
		for(int i = 1; i < n; ++i)
			printf(" %d", a[i]);
	}
}