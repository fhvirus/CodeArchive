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
inline int readint(){
	int ans = 0, c = readchar();
	while((c<'0'||c>'9')&&c!=EOF) c=readchar();
	while(c>='0'&&c<='9') ans=(ans<<3)+(ans<<1)+(c^'0'), c=readchar();
	return ans;
}

const int N = 1e5;
int k, m, S[N], R[N], id[N];

long long merge(int l, int r){
	if(r - l <= 1) return 0ll;
	int m = (l + r) >> 1;
	long long ans = merge(l, m) + merge(m, r);

	int lptr = l, rptr = m, ptr = l;
	long long rcnt = 0;
	while(lptr < m or rptr < r){
		if(lptr < m and (rptr == r or S[lptr] <= S[rptr])){
			R[ptr++] = S[lptr++];
			ans += rcnt;
		} else {
			R[ptr++] = S[rptr++];
			++rcnt;
		}
	}
	for(int i = l; i < r; ++i)
		S[i] = R[i];
	return ans;
}

#include<algorithm>

int main(){
	k = readint(), m = readint();
	FOR(i,k) S[i] = readint();
	FOR(i,k) R[i] = readint(), id[i] = i;
	std::sort(id, id+k, [](int i, int j){
		return S[i] < S[j];
	});
	FOR(i,k) S[i] = R[id[i]];
	printf("%lld\n", merge(0, k));
}