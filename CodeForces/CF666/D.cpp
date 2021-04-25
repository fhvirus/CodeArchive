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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<queue>
using namespace std;
priority_queue<int> pq;
int t, n, a[100], last;
bool turn, nf;

int main(){
	t = R();
	for(; t; --t){
		n = R(); pq = {}; turn = false; nf = false;
		FOR(i, n) pq.push(R());
		while(!pq.empty()){
			int jizz = pq.top(); pq.pop();
			if(nf and last > 0) pq.push(last);
			nf = true;
			last = jizz - 1;
			turn = !turn;
		}
		puts(turn ? "T" : "HL");
	}
}