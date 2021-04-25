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
	int ans = 0, c = readchar(), minus = false;
	while((c<'0'||c>'9')&&c!='-'&&c!=EOF) c=readchar();
	if(c=='-') minus = true, c = readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return minus ? -ans : ans;
}

#include<vector>
#include<algorithm>
int n, m, a, now = 1, p;
std::vector<int> station;

int main(){
	n = R(); m = R();
	FOR(i,n){
		a = R();
		while(now <= a) station.push_back(now++);
		auto it = std::find(station.begin(), station.end(), a);
		p = station.end() - it;
		if(p > m + 1){
			puts("no");
			return 0;
		}
		station.erase(it);
	}
	puts("yes");
	return 0;
}