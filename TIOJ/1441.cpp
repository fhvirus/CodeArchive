#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}

int main(){
	int n = R(), h, jizz = -1, ans = 0;
	bool idx = false;
	for(; n; --n){
		h = R();
		if(h != jizz and (idx ^ (h > jizz)))
			++ans, idx = !idx;
		jizz = h;
	}
	if(!idx) --ans;
	printf("%d\n", ans);
}