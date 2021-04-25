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
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

int m, n, wrong[101], ACtime, ACcnt, t, w, g;
bool hadAC[101];

int main(){
	while(true){
		m = R(); n = R();
		if(m == 0 and n == 0) break;
		ACtime = ACcnt = 0;
		for(int i = 1; i <= m; ++i) wrong[i] = 0, hadAC[i] = false;
		FOR(i,n){
			t = R(); w = R(); g = R();
			if(g == 1){
				if(!hadAC[w])
					ACtime += t + wrong[w] * 20, ++ACcnt, hadAC[w] = true;
			} else {
				wrong[w]++;
			}
		}
		printf("%d %d\n", ACtime, ACcnt);
	}
	return 0;
}