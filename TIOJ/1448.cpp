#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#define N 500000
int n, k, dsu[N*3+1], ans;
int Find(int a){
	return a == dsu[a] ? a : dsu[a] = Find(dsu[a]);
}
inline void Union(int a, int b){
	(Find(a) != Find(b)) && (dsu[dsu[b]] = dsu[a]);
}

int main(){
	n = R(), k = R();
	for(int i = 1; i <= n; ++i) dsu[i] = i, dsu[N + i] = N + i, dsu[N * 2 + i] = N * 2 + i;
	for(int cmd, a, b; k; --k){
		cmd = R(), a = R(), b = R();
		if(a > n or b > n){ ++ans; continue;}
		if(cmd == 1){
			if(Find(a) == Find(b + N) or Find(a) == Find(b + N*2))
				++ans;
			else
				Union(a, b), Union(a + N, b + N), Union(a + N*2, b + N*2);
		} else {
			if(Find(a) == Find(b) or Find(a) == Find(b + N*2))
				++ans;
			else
				Union(a, b + N), Union(a + N, b + N*2), Union(a + N*2, b);
		}
	}
	printf("%d\n", ans);
}