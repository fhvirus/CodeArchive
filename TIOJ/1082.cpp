#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<18;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

#define INF 2147483647
long long sum;
int n, b, w, jizz;
bool ab, aw;

int main(){
	while((n = R()) != 0){
		if(n == 1){ b = R(), w = R(), puts(b > 0 and w > 0 ? "-1" : "0"); continue;}
		ab = aw = true, sum = 0, jizz = INF;
		FOR(i, n) ((b = R()) < (w = R())) ? (aw = false, sum += b, jizz = jizz < w - b ? jizz : w - b) : (ab = false, sum += w, jizz = jizz < b - w ? jizz : b - w);
		printf("%lld\n", (ab || aw) ? sum + jizz : sum);
	}
}