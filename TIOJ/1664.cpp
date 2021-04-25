#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#pragma loop_opt(on)
#include<unistd.h>
const int S = 1<<16;
inline char readchar(){
	static char buf[S], *p = buf, *q = buf;
	return (p==q&&(q=(p=buf)+read(0,buf,S))==buf) ? -1 : *p++;
}
inline int R(){
	int ans = 0; char c = readchar();
	while(c<'0'&&c!=-1) c=readchar();
	if(c == -1) return -1;
	while(c>='0') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}
const char eek[7][10] = {
	"Friday",
	"Saturday",
	"Sunday",
	"Monday",
	"Tuesday",
	"Wednesday",
	"Thursday"
};
#include<cstdio>
int n;
int main(){
	while((n = R()) != -1)
		puts(eek[n%7]);
}