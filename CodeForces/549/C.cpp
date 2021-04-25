#pragma GCC optimize("Ofast")
#pragma loop_opt(on)
#include<cstdio>
#define FOR(i,n) for(int i=0;i<n;++i)
const int S = 1<<16;
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
const int N = 2e5;
int n, k, left, a, odd, even;

int main(){
	n = R(); left = R(); k = n - left;
	FOR(i, n) a = R(), odd += (a & 1), even += 1 - (a & 1);
	if(left == n){
		puts(odd % 2 ? "Stannis" : "Daenerys");
		return 0;
	}
	if(left % 2 == 1){
		if(k % 2 == 1){
			puts(odd > k / 2 ? "Stannis" : "Daenerys");
		} else {
			puts(even <= k / 2 ? "Stannis" : "Daenerys");
		}
	} else {
		if(k % 2 == 1){
			puts(odd > k / 2 and even > k / 2 ? "Stannis" : "Daenerys");
		} else {
			puts("Daenerys");
		}
	}
	// if(odd > k / 2 and !((n - k) % 2 == 0 and even <= k / 2)) puts("Stannis");
	// else puts("Daenerys");
}