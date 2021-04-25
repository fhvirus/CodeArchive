#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
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

const int N = 1e5;
int n, k, des[N<<1], e, covered[N<<1];

// struct asteroid{
// 	int l, r;
// 	bool operator<(const asteroid &rhs) const{
// 		return l == rhs.l ? r < rhs.r : l < rhs.l;
// 	}
// } a[N];
#include<utility>
pair<int, int> a[N];
#define l first
#define r second

#include<cstring>
priority_queue<int> pq;
bool check(int p){
	// fill(covered, covered+e, 0);
	memset(covered, 0, e<<2);
	pq = {};
	int cntK = k, cntP = 0, id = 0, over;
	for(int i = 0; i < e; ++i){
		while(id < n and a[id].l == i){
			cntP++;
			covered[a[id].r]++;
			pq.push(a[id].r);
			++id;
		}
		cntP -= covered[i], over = cntP - p;
		if(over > 0){
			cntK -= over;
			if(cntK < 0) return false;
			cntP = p;
			while(over--){
				covered[pq.top()]--;
				pq.pop();
			}
		}
	}
	return true;
}

int main(){
	n = R(); k = R();
	if(k >= n){
		puts("0");
		return 0;
	}
	if(k == n-1){
		puts("1");
		return 0;
	}
	FOR(i,n) a[i].l = R(), a[i].r = R(), des[e++] = a[i].l, des[e++] = a[i].r;
	sort(des, des + e);
	sort(a, a + n);
	e = unique(des, des + e) - des;
	FOR(i,n){
		a[i].l = lower_bound(des, des + e, a[i].l) - des;
		a[i].r = lower_bound(des, des + e, a[i].r) - des;
	}

	int l = 0, r = n + 1 - k, m;
	while(r > l){
		m = (l + r)>>1;
		if(check(m)) r = m;
		else l = m + 1;
	}
	printf("%d", l);
}