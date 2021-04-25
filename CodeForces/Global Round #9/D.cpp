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

int T, n, a[1000];
int appear[1001];
inline int mex(){
	for(int i = 0;;++i){
		if(appear[i] == 0) return i;
	}
}
inline int unfixed(){
	FOR(i,n) if(a[i] != i) return i;
	return n;
}

#include<algorithm>
using namespace std;
int moves[2000], cnt, u, m;
int main(){
	T = R();
	for(;T;--T){
		n = R();
		cnt = 0;
		memset(appear, 0, sizeof(appear));
		FOR(i,n) a[i] = R(), appear[a[i]]++;
		while((u=unfixed()) != n){
			if((m=mex()) == n){
				appear[a[u]]--;
				appear[m]++;
				a[u] = m;
				moves[cnt++] = u;
			}
			else{
				appear[a[m]]--;
				appear[m]++;
				a[m] = m;
				moves[cnt++] = m;
			}
		}
		printf("%d\n", cnt);
		FOR(i,cnt) printf("%d ", moves[i]+1);
		printf("\n");
	}
}