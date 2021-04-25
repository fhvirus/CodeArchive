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

#include<algorithm>
#include<utility>
using namespace std;

typedef pair<int, int> pii;

pii ed[1005];

bool cmp(pii a, pii b){
	return a.second < b.second;
}

int main(){
	int n, m, curTime;
	bool can;
	n = R();
	for(;n;--n){
		m = R();
		for(int i = 0; i < m; i++){
			ed[i] = {R(), R()};
		}
		sort(ed, ed + m, cmp);
		can = true;
		curTime = 0;
		for(int i = 0; i < m; i++){
			curTime += ed[i].first;
			if(curTime > ed[i].second){
				can = false;
				break;
			}
		}
		puts(can ? "schedulable" : "unschedulable");
	}
	return 0;
}