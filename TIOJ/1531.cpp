#pragma Ofast
#pragma loop-opt(on)
#pragma GCC target("avx2")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#include<cstdio>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0, c = readchar();
	while(c<'0') c=readchar();
	while(c>='0') ans=(ans*10)+(c^'0'), c=readchar();
	return ans;
}
const int N = 5e6 + 10;
int n, k, p[N], ans;
char s[N], c;
int main(){
	k = R();
	p[0] = 0;
	s[0] = readchar();
	c = readchar();
	for(int i = 1; c != EOF; ++i, c = readchar()){
		s[i] = c;
		p[i] = p[i-1];
		while(s[i] != s[p[i]]){
			if(p[i] == 0){ p[i] = -1; break;}
			p[i] = p[p[i] - 1];
		}
		++p[i];
		if((i + 1) % (i - p[i] + 1) == 0 and (i + 1) / (i - p[i] + 1) % k == 0)
			ans = (i + 1) / k;
	}
	printf("%d\n", ans);
}