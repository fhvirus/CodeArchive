#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
inline char readchar(){
	const int S = 1<<20;
	static char buf[S], *p = buf, *q = buf;
	if(p==q&&(q=(p=buf)+fread(buf,1,S,stdin))==buf) return EOF;
	return *p++;
}
inline short R(){
	short ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

short a, b, c;
int main(){
	while(true){
		a = R(); b = R(); c = R();
		if(a == 0) break;
		puts((a+b==c or a+c==b or b+c==a) ? "Good Pair" : "Not Good Pair");
	}
	return 0;
}