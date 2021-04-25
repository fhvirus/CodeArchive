#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
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
bool eek(int a, int b, int c){
	return a > 0 and b > 0 and c > 0 and
		   (a*a == b*b+c*c or
			b*b == a*a+c*c or
			c*c == a*a+b*b);
}

int main(){
	int n, a, b, c;
	n = R();
	for(; n; --n){
		a = R(), b = R(), c = R();
		puts(eek(a, b, c) ? "yes" : "no");
	}
}