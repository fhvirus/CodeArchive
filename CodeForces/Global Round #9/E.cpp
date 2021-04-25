#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
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

#include<algorithm>
using namespace std;
int n, a[1000], tmp[1000];
struct p{
	int a, b;
} s[1000];
int ptr;

int main(){
	n = R();
	FOR(i,n) a[i] = R();
	for(int i = 0; i < n-1; ++i){
		int mn = min_element(a+i+1, a+n) - a;
		if(a[mn] < a[i]){
			s[ptr++] = (p){i+1, mn+1};
			swap(a[i], a[mn]);
		}
	}
	printf("%d\n", ptr);
	FOR(i,ptr){
		printf("%d %d\n", s[i].a, s[i].b);
	}
	return 0;
}