#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma loop_opt(on)
#include<cstdio>
const int S = 1<<20;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) ? EOF : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0' and c != EOF) c=readchar();
	while(c>='0') ans=ans*10+(c^'0'), c=readchar();
	return ans;
}
int n, a, max;
long long sum;
int main(){
	while((n = R()) != 0){
		sum = 0, max = 0;
		for(int i = 0; i < n; ++i) a = R(), sum += a, max = max < a ? a : max;
		puts(max<<1 < sum ? "YES" : "NO");
	}
}